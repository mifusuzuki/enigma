#ifndef HELPER_H
#define HELPER_H

#include <string>

int print_error_message(int error_code);
int check_non_numeric(const std::string& str);
int check_invalid_index(int val);
int check_invalid_input_character(char character);

#endif
