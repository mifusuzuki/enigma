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

    /* create an enigma */
    Enigma enigma;

    /* check if there are any rotors specified */
    if (argc > 4)
    {
        /* there are no rotors */
        enigma.m_confirm_enigma_has_rotor();
    }

    /* save rotor paths into an array if there are any */
    std::vector<std::string> rot_files;
    if (enigma.m_has_one_or_more_rotors())
    {
        for (int i = 3; i < argc - 1; i++) {
            rot_files.push_back(argv[i]);
        }
    }

    /* setup plugboard */ 
    if (int error_code = enigma.m_setup_plugboard(argv[1]))
    {
        return error_code;
    }
   
    /* set up rotor if there are any */
    if (enigma.m_has_one_or_more_rotors())
    {
        if (int error_code = enigma.m_setup_rotors(rot_files, argv[argc - 1]))
        {
            return error_code;
        }
    }
    /* set up reflector */ 
    if (int error_code = enigma.m_setup_reflector(argv[2]))
    {
        return error_code;
    } 

    /* encrypt or decrypt message */
    char character;
    while (std::cin >> character)
    {
        if (int error_code = enigma.m_encrypt_message(character))
        {
            return error_code;
        } 
        std::cout << character;
    } 
    return NO_ERROR;
    }

