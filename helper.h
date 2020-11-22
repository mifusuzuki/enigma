/* Helper Header */
#ifndef HELPER_H
#define HELPER_H

#include <string>

int print_error_message(int error_code); // print error message and return error code depending on the input code
int check_non_numeric(const std::string& str); // check if given string contains any numeic character
int check_invalid_index(int val); // check if given val is valid
int check_invalid_input_character(char character); // check is given character is valid

#endif
