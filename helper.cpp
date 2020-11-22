/* Helper Implementation */

#include "errors.h"
#include "helper.h"

#include <iostream>

int print_error_message(int error_code) {

    /* return messages and error codes depending ont the input code */

    switch(error_code) {
                                                        
    case 1:
      std::cerr << "[ERROR] insufficient number of command line arguments ";
      return INSUFFICIENT_NUMBER_OF_PARAMETERS;

    case 2:
      std::cerr << "[ERROR] invalid input character (all input characters must be uppercase A-Z) ";
      return INVALID_INPUT_CHARACTER;

    case 3:
      std::cerr << "[ERROR] invalid index detected in file ";
      return INVALID_INDEX;

    case 4:
      std::cerr << "[ERROR] non-numeric character detected in file ";
      return NON_NUMERIC_CHARACTER;

    case 5:
      std::cerr << "[ERROR] impossible plugboard configuration ";
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

    case 6:
      std::cerr << "[ERROR] incorrect number of mappings in plugboard file ";
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

    case 7:
      std::cerr << "[ERROR] invalid rotor mapping detected in file ";
      return INVALID_ROTOR_MAPPING;

    case 8:
      std::cerr << "[ERROR] insufficient number of rotor starting position ";
      return NO_ROTOR_STARTING_POSITION;

    case 9:
      std::cerr << "[ERROR] invalid reflector mapping detected in file ";
      return INVALID_REFLECTOR_MAPPING;

    case 10:
      std::cerr << "[ERROR] incorrect number of mappings in reflector file ";
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

    case 11:
      std::cerr << "[ERROR] issue opening configuration file ";
      return ERROR_OPENING_CONFIGURATION_FILE;

    default:
      std::cerr << "[NO ERROR] ";
      return NO_ERROR;
  }
}

int check_non_numeric(const std::string& str)
{
    /* go through the string and check if there is any non numeric characyer */
    for (unsigned int i=0; i<str.size(); i++)
    {   
        if (!isdigit(str[i]))
        {
            /* non digit detected in string */
            print_error_message(NON_NUMERIC_CHARACTER);
            return NON_NUMERIC_CHARACTER;
        }
    }
    return NO_ERROR;
}

int check_invalid_index(int val)
{
    /* check if the given val is within 0 to 25 inclusive */
    if (!(val >= 0 && val <= 25))
    {
      /* invalid input parameter detected */
      print_error_message(INVALID_INDEX);
      return INVALID_INDEX;
    }
    return NO_ERROR;
}

int check_invalid_input_character(char character)
{
    /* check if the given val is within A to Z inclusive */
    if (!(character >= 'A' && character <= 'Z'))
    {
      /* invalid input parameter detected */
      print_error_message(INVALID_INPUT_CHARACTER);
      std::cerr << "(" << character << " is not a valid input character)" << std::endl;
      return INVALID_INPUT_CHARACTER;
    }
    return NO_ERROR;
}
