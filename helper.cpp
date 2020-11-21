/* Helper Implementation */

#include "errors.h"
#include "helper.h"
#include <iostream>

int print_error_message(int error_code) {

  switch(error_code) {
                                                        
    case 1:
      std::cerr << "[ERROR] insufficient number of parameters" << std::endl;
      return INSUFFICIENT_NUMBER_OF_PARAMETERS;

    case 2:
      std::cerr << "[ERROR] invalid input character"  << std::endl;
      return INVALID_INPUT_CHARACTER;

    case 3:
      std::cerr << "[ERROR] invalid index" << std::endl;
      return INVALID_INDEX;

    case 4:
      std::cout << "Non-numeric character in plugboard file plugboard.pb" << std::endl;
      return NON_NUMERIC_CHARACTER;

    case 5:
      std::cout << "[ERROR] impossible plugboard configuration" << std::endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

    case 6:
      std::cerr << "[ERROR] incorrect number of plugboard parameters" << std::endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

    case 7:
      std::cerr << "[ERROR] invalid rotor mapping" << std::endl;
      return INVALID_ROTOR_MAPPING;

    case 8:
      std::cerr << "[ERROR] no rotor starting position" << std::endl;
      return NO_ROTOR_STARTING_POSITION;

    case 9:
      std::cerr << "[ERROR] invalid reflector mapping" << std::endl;
      return INVALID_REFLECTOR_MAPPING;

    case 10:
      std::cerr << "[ERROR] incorrect number of reflector parameters" << std::endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

    case 11:
      std::cerr << "[ERROR] issue opening configuration file" << std::endl;
      return ERROR_OPENING_CONFIGURATION_FILE;

    default:
      std::cerr << "[NO ERROR]" << std::endl;
      return NO_ERROR;
  }
}

int check_non_numeric(const std::string& str)
{
    //std::cout << "check_non_numeric called" << std::endl;
    if (!str.find_first_not_of("-0123456789"))
    {
        /* non digit detected in string */
        print_error_message(NON_NUMERIC_CHARACTER);
        return NON_NUMERIC_CHARACTER;
    }
    return NO_ERROR;
}

int check_invalid_index(int val)
{
    //std::cout << "check_invalid_index called" << std::endl;
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
    //std::cout << "check_invalid_input_character called" << std::endl;
    if (!(character >= 'A' && character <= 'Z'))
    {
      /* invalid input parameter detected */
      print_error_message(INVALID_INPUT_CHARACTER);
      return INVALID_INPUT_CHARACTER;
    }
    return NO_ERROR;
}
