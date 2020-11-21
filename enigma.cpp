/* Enigma Implementation*/
#include <iostream>
#include <fstream>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "enigma.h"

int Enigma::m_setup_plugboard(const std::string& pb_file)
{
    if (int error_code = m_plugboard.m_read_file(pb_file))
    {
        return error_code;
    }
    if (int error_code = m_plugboard.m_load_config())
    {   
        return error_code;
    }
    //std::cout << std::endl;
    //std::cout << "loaded plugboard config" << std::endl;
    //m_plugboard.m_print_config();   
    return NO_ERROR;
}

int Enigma::m_setup_rotors(const std::vector<std::string>& rot_file, const std::string& pos_file)
{
    /* get rotor positions */
    std::vector<int> rot_init_pos;
    std::ifstream file;
    file.open(pos_file);
    /* check issue opening pos_file*/
    //std::cout << "opening pos_file = " << pos_file << std::endl;
    if (file.fail())
    {
        print_error_message(ERROR_OPENING_CONFIGURATION_FILE);
        return ERROR_OPENING_CONFIGURATION_FILE; 
    }
    /* read pos_file */
    std::string str;
    while (file >> str) 
    {
      if (check_non_numeric(str) == NON_NUMERIC_CHARACTER) 
        {
            return NON_NUMERIC_CHARACTER;
        }
        /* convert string to int */
        int number = stoi(str);
        if (check_invalid_index(number) == INVALID_INDEX)
        {
            return INVALID_INDEX;
        }
        rot_init_pos.push_back(number);
    }
    file.close();
    
    /* check there is one position specified for every rotor */
    if (rot_init_pos.size() < rot_file.size())
    {
        print_error_message(NO_ROTOR_STARTING_POSITION);
        return NO_ROTOR_STARTING_POSITION; 
    }
  
    /* set up rotors */
    for (int i=0; i<rot_file.size(); i++)
    {
        m_rotors.push_back(Rotor(rot_init_pos[i])); // create a rotor
        if (int error_code = m_rotors[i].m_read_file(rot_file[i]))
        {
            return error_code;
        }
        if (int error_code = m_rotors[i].m_load_config())
        {   
            return error_code;
        }
        //std::cout << std::endl;
        //std::cout << "loaded rotor " << i+1 << " config" << std::endl;
        //std::cout << "initial position = " << m_rotors[i].m_get_displacement() << std::endl;
        //std::cout << "config = ";
        //m_rotors[i].m_print_config();   
        //std::cout << "notches = ";
        //m_rotors[i].m_print_notches();  
    }
    return NO_ERROR;
}

int Enigma::m_setup_reflector(const std::string& rf_file)
{
    if (int error_code = m_reflector.m_read_file(rf_file))
    {
        return error_code;
    }
    if (int error_code = m_reflector.m_load_config())
    {   
        return error_code;
    }
    //std::cout << std::endl;
    //std::cout << "loaded reflector config" << std::endl;
    //m_reflector.m_print_config();   
    return NO_ERROR;

}

void Enigma::m_stabilise_rotors(int last_rot)
{
    /* stabilised all rotors */
    if (last_rot == 0)
    {
        return;
    }
    /* notch found */
    if (m_rotors[last_rot].m_has_notch())
    {
        //std::cout << "there is a notch on " << last_rot+1 << " so we and turned rotor " << last_rot << std::endl;
        /* turn the rotor to its left */
        m_rotors[last_rot-1].m_turn_rotor();
        /* recursive call - stabilise again */
        m_stabilise_rotors(last_rot-1);
        return;
    }
    m_stabilise_rotors(last_rot-1);
}

int Enigma::m_pre_reflector_rotor_mechanism(int index)
{
    /* turn right most rotor */
    m_rotors[m_rotors.size()-1].m_turn_rotor();
    /* adjust rotors according to the notches */
    m_stabilise_rotors(m_rotors.size()-1);
    /* go through rotors from right to left */
    for (int rot=m_rotors.size()-1; rot>=0; rot--)
    {
        int displaced_index = (index + m_rotors[rot].m_get_displacement())%26;
        index = m_rotors[rot].m_get_char(displaced_index);
        //std::cout << "post rotor index (pre-reflector) = " << index << std::endl;
    }
    return index;
}

int Enigma::m_post_reflector_rotor_mechanism(int character)
{
    /* go through rotors from left to right */
    int displaced_index;
    for (int rot=0; rot<m_rotors.size(); rot++)
    {
        int index = m_rotors[rot].m_get_position(character);
        displaced_index = (index+(26-m_rotors[rot].m_get_displacement()))%26;
        //std::cout << "post rotor index (post-reflector) = " << displaced_index << std::endl;
        character = displaced_index;
    }
    return displaced_index;
}


int Enigma::m_encrypt_message(std::string& message)
{
    for (int chr=0; chr<message.size(); chr++)
    {
        /* check invalid input char and convert char into lookup index if ok */
        if (check_invalid_input_character(message[chr]) == INVALID_INPUT_CHARACTER)
        {
            return INVALID_INPUT_CHARACTER;
        }
        int index = (int)message[chr]-65;

        /* thorugh plugboard */
        index = m_plugboard.m_get_char(index);
        //std::cout << "post plugbpard index = " << index << std::endl;
        /* through rotors */
        index = m_pre_reflector_rotor_mechanism(index);
        /* reflected on reflector */
        index = m_reflector.m_get_char(index);
        //std::cout << "post reflector index = " << index << std::endl;
        /* back through rotors */
        index = m_post_reflector_rotor_mechanism(index);
        /* back through plugboard */
        index = m_plugboard.m_get_char(index);
        //std::cout << "post plugbpard index (post-reflector) = " << index << std::endl;
        /* update the character */
        message[chr] = (char)(index+65);
    }
    return NO_ERROR;
}
