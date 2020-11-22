/* Reflector Implementation*/
#include "reflector.h"

#include "component.h"
#include "errors.h"
#include "helper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int Reflector::m_check_index_already_configured(int prev_val, int val)
{
    /* check if index maps to itself */
    if (prev_val == val)
    {
        /* value already configured */
        print_error_message(INVALID_REFLECTOR_MAPPING);
        return INVALID_REFLECTOR_MAPPING;
    }
    /* check if index maps to more than one other index */
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
    /* go through m_raw_data and carry out necessary checks one by one and store it in m_config */
    int prev = -1; 
    unsigned int index = 0;
    for (; index < m_raw_data.size(); index++)
    {
        /* check no greater than 13 pairs of parameters */
        if (index > 25)
        {
            print_error_message(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
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
        if (m_check_index_already_configured(prev, number) == INVALID_REFLECTOR_MAPPING)
        {
            return INVALID_REFLECTOR_MAPPING;
        }
        /* temporarily store first element of pair */
        if (index%2 == 0)
        {
            prev = number;
            continue;
        }
        /* temporarily store second element of pair */
        int cur = number;
        /* save pair in m_config */
        m_config[prev] = cur;
        m_config[cur] = prev;
    }
    
    /* check no no less or greater than 13 pairs of parameters */
    if (index != 26)
    {
        print_error_message(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    return NO_ERROR;
}                  
