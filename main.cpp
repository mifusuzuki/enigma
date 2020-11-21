#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "enigma.h"

int main(int argc, char* argv[]) {

    /* check no less than 4 arguments */                                                       
    if (argc < 4) {
        print_error_message(INSUFFICIENT_NUMBER_OF_PARAMETERS);
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

    /* save rotor paths into an array */
    std::vector<std::string> rot_files;
    for (int i = 3; i < argc - 1; i++) {
        rot_files.push_back(argv[i]);
    }

    /* create an enigma */
    Enigma enigma;
    
    /* setup plugboard */ 
    if (int error_code = enigma.m_setup_plugboard(argv[1]))
    {
        return error_code;
    }
   
    /* set up rotor */
    if (int error_code = enigma.m_setup_rotors(rot_files, argv[argc - 1]))
    {
        return error_code;
    }
    
    /* set up reflector */ 
    if (int error_code = enigma.m_setup_reflector(argv[2]))
    {
        return error_code;
    } 

    /* encrypt or decrypt message */
    std::string str;
    while (std::cin >> str)
    {
        if (int error_code = enigma.m_encrypt_message(str))
        {
            return error_code;
        } 
        std::cout << str;
    } 
    return NO_ERROR;
}

