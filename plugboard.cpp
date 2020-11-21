/* Plugboard Implementation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "plugboard.h"
#include "component.h"

int PlugBoard::m_check_odd_num_of_param(int index)
{
    /* check for odd number of parameter inputs */
    if (index%2)
    {
      /* there is odd number of elements */
      print_error_message(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    return NO_ERROR;
}

int PlugBoard::m_check_index_already_configured(int prev_val, int val)
{
    //std::cout << "m_check_index_already_configured called" <<std::endl;
    if (prev_val == val)
    {
        /* value already configured */
        print_error_message(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
    for (unsigned int i=0; i<m_config.size(); i++)
    {
        if (m_config[i] == val)
        {
            /* value already configured */
            print_error_message(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
    }
    return NO_ERROR;
}

int PlugBoard::m_load_config()
{
    int prev = -1; 
    unsigned int index = 0;
    for (; index < m_raw_data.size(); index++)
    {
        /* check no greater than 26 inputs */
        if (index > 25)
        {
            print_error_message(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        }
        /* check no non-numeric input */
        if (check_non_numeric(m_raw_data[index]) == NON_NUMERIC_CHARACTER) 
        {
            return NON_NUMERIC_CHARACTER;
        }
        /* convert string to int */
        int number = stoi(m_raw_data[index]);
        /* check no invalid index */
        if (check_invalid_index(number) == INVALID_INDEX)
        {
            return INVALID_INDEX;
        }
        /* check index not already configured */
        if (m_check_index_already_configured(prev, number) == IMPOSSIBLE_PLUGBOARD_CONFIGURATION)
        {
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
        /* first element of pair */
        if (index%2 == 0)
        {
            prev = number;
            continue;
        }
        /* second element of pair */
        int cur = number;
        /* save pair */
        m_config[prev] = cur;
        m_config[cur] = prev;
    }
    /* check no odd number of parameters */
    if (m_check_odd_num_of_param(index) == INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS)
    {
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    return NO_ERROR;
}             
