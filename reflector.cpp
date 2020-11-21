/* Reflector Implementation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "reflector.h"
#include "component.h"

int Reflector::m_check_num_of_param(int index)
{
    /* check exactly 13 pairs */
    if (index != 26)
    {
      /* there is odd number of elements */
      print_error_message(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    return NO_ERROR;
}

int Reflector::m_check_index_already_configured(int prev_val, int val)
{
    //std::cout << "m_check_index_already_configured called" <<std::endl;
    if (prev_val == val)
    {
        /* value already configured */
        print_error_message(INVALID_REFLECTOR_MAPPING);
        return INVALID_REFLECTOR_MAPPING;
    }
    for (unsigned int i=0; i<m_config.size(); i++)
    {
        if (m_config[i] == val)
        {
            /* value already configured */
            print_error_message(INVALID_REFLECTOR_MAPPING);
            return INVALID_REFLECTOR_MAPPING;
        }
    }
    return NO_ERROR;
}

int Reflector::m_load_config()
{
    int prev = -1; 
    unsigned int index = 0;
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
        if (m_check_index_already_configured(prev, number) == INVALID_REFLECTOR_MAPPING)
        {
            return INVALID_REFLECTOR_MAPPING;
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

    if (m_check_num_of_param(index) == INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS)
    {
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    return NO_ERROR;
}                  
