/* Enigma Implementation*/
#include "enigma.h"

#include "errors.h"
#include "helper.h"

#include <fstream>
#include <iostream>
#include <vector>

Enigma::Enigma()
{
    /* enigma has no rotors default unless specified otherwise */
    m_has_rotor = false;
}

int Enigma::m_setup_plugboard(const std::string& pb_file)
{
    /* read plugboard file */
    if (int error_code = m_plugboard.m_read_file(pb_file))
    {
        return error_code;
    }
    /* load plugboard config */
    if (int error_code = m_plugboard.m_load_config())
    {   
        return error_code;
    }   
    return NO_ERROR;
}

int Enigma::m_setup_rotors(const std::vector<std::string>& rot_file, const std::string& pos_file)
{
    /* array to temporary store initial positions of each rotor */
    std::vector<int> rot_init_pos;

    /* open position file */
    std::ifstream file;
    file.open(pos_file);
    /* check issue opening position file */
    if (file.fail())
    {
        print_error_message(ERROR_OPENING_CONFIGURATION_FILE);
        return ERROR_OPENING_CONFIGURATION_FILE; 
    }
    /* read position file */
    std::string str;
    while (file >> str) 
    {
        /* check there is no non-numeric value in position file */
        if (check_non_numeric(str) == NON_NUMERIC_CHARACTER) 
        {
            return NON_NUMERIC_CHARACTER;
        }
        /* convert string to int */
        int number = stoi(str);
        /* check there is no invalid index in file */
        if (check_invalid_index(number) == INVALID_INDEX)
        {
            return INVALID_INDEX;
        }
        /* temporarily save the position */
        rot_init_pos.push_back(number);
    }
    file.close();
    
    /* check there is enough positions specified for the number of rotors present */
    if (rot_init_pos.size() < rot_file.size())
    {
        print_error_message(NO_ROTOR_STARTING_POSITION);
        return NO_ROTOR_STARTING_POSITION; 
    }
  
    /* set up rotors */
    for (unsigned int i=0; i<rot_file.size(); i++)
    {
        /* create a rotor with given initial position and store it in rotor array i.e. m_rotors */
        m_rotors.push_back(Rotor(rot_init_pos[i])); 
        /* read rotor file */
        if (int error_code = m_rotors[i].m_read_file(rot_file[i]))
        {
            return error_code;
        }
        /* load rotor configuration */
        if (int error_code = m_rotors[i].m_load_config())
        {   
            return error_code;
        }
    }
    return NO_ERROR;
}

int Enigma::m_setup_reflector(const std::string& rf_file)
{
    /* read reflector file */
    if (int error_code = m_reflector.m_read_file(rf_file))
    {
        return error_code;
    }
    /* load reflector configuration */
    if (int error_code = m_reflector.m_load_config())
    {   
        return error_code;
    }  
    return NO_ERROR;
}

void Enigma::m_stabilise_rotors(int last_rot)
{
    /* base case - stabilised all rotors */
    if (last_rot == 0)
    {
        return;
    }
    /* check if the rotor has notch at the top */
    if (m_rotors[last_rot].m_has_notch())
    {
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
    /* adjust rotors according to the notches and stabilise them */
    m_stabilise_rotors(m_rotors.size()-1);
    /* turn the right most rotor */
    m_rotors[m_rotors.size()-1].m_turn_rotor();
    /* adjust rotors according to the notches and stabilise them */
    m_stabilise_rotors(m_rotors.size()-1);
    /* go through rotors from right to left */
    int character;
    for (int rot=m_rotors.size()-1; rot>=0; rot--)
    {
        /* find current position of the rotor */
        int displacement = m_rotors[rot].m_get_displacement();
        /* update the index to a shifted one */
        int index = (index + displacement) % 26;
        /* find the character at the index */
        character = m_rotors[rot].m_get_char(index);
        /* update the character to a shifted one */
        character = (character - displacement + 26) % 26;
    }
    return index;
}

int Enigma::m_post_reflector_rotor_mechanism(int character)
{
    /* go through rotors from left to right */
    int index;
    for (unsigned int rot=0; rot<m_rotors.size(); rot++)
    {
        /* find current position of the rotor */
        int displacement = m_rotors[rot].m_get_displacement();
        /* update the character to a shifted one */
        character = (character + displacement) % 26;
        /* find the updated character's position*/
        index = m_rotors[rot].m_get_position(character);
        /* update the index to a shifted one */
        index = (index - displacement + 26) % 26;
    }
    return index;
}

int Enigma::m_encrypt_message(char& character)
{
    /* check no invalid character */
    if (check_invalid_input_character(character) == INVALID_INPUT_CHARACTER)
    {
        return INVALID_INPUT_CHARACTER;
    }
    /* convert character to int */
    int index = (int)character-65;

    /* PLUGBOARD ENCRYPTION */
    index = m_plugboard.m_get_char(index);

    /* ROTOR ENCRYPTION */
    if (m_has_one_or_more_rotors())
    {
        index = m_pre_reflector_rotor_mechanism(index);
    }

    /* REFLECTOR ENCRYPTION */
    index = m_reflector.m_get_char(index);

    /* ROTOR ENCRYPTION */
    if (m_has_one_or_more_rotors())
    {
        index = m_post_reflector_rotor_mechanism(index);
    }

    /* PLUGBOARD ENCRYPTION */
    index = m_plugboard.m_get_char(index);

    /* update the character to the encrypted one */
    character = (char)(index+65);
    return NO_ERROR;
}
