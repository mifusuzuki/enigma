/* Plugboard Implementation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "plugboard.h"
#include "component.h"

int PlugBoard::m_check_num_of_param(int index)
{
    /* check even num of parameter and less than 13 pairs */
    if ((index)%2 || index > 26)
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
    for (int i=0; i<m_config.size(); i++)
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
    int index = 0;
    for (; index < m_raw_data.size(); index++)
    {
        //std::cout << "checking " << m_raw_data[index] << std::endl;
        if (check_non_numeric(m_raw_data[index]) == NON_NUMERIC_CHARACTER) 
        {
            return NON_NUMERIC_CHARACTER;
        }
        /* convert string to int */
        int number = stoi(m_raw_data[index]);
        if (check_invalid_index(number) == INVALID_INDEX)
        {
            return INVALID_INDEX;
        }
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
    if (m_check_num_of_param(index) == INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS)
    {
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    return NO_ERROR;
}             
