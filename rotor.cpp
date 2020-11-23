/* Rotor Implementation*/
#include "rotor.h"

#include "component.h"
#include "errors.h"
#include "helper.h"

#include<algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Rotor::Rotor(int init_pos) : Component()
{   
    /* set rotor's starting position */
    m_displacement = init_pos;

    /* default notch array */
    m_notches.fill(-1);
}

int Rotor::m_check_index_already_configured(int val)
{
     /* check if index maps to more than one other index */
    for (unsigned int i=0; i<m_config.size(); i++)
    {
        if (m_config[i] == val)
        {
            /* value already configured */
            print_error_message(INVALID_ROTOR_MAPPING);
            return INVALID_ROTOR_MAPPING;
        }
    }
    return NO_ERROR;
}

int Rotor::m_check_all_indexes_configured()
{
    /* check there is no yet-to-be configured indexes */
    for (int i=0; i<26; i++)
    {
        /* go through m_ config from start to end and check all 0-25 indexes are found */
        if (std::find(m_config.begin(), m_config.end(), i) == m_config.end())
        {
            /* found index not yet configured */
            print_error_message(INVALID_ROTOR_MAPPING);
            return INVALID_ROTOR_MAPPING;
        }
    }
    return NO_ERROR;
}

int Rotor::m_load_config()
{
    /* go through m_raw_data and carry out necessary checks one by one and store it in m_config */
    unsigned int index = 0;
    for (; index < m_raw_data.size(); index++)
    {
        /* first 26 elements - encryption mapping */
        
        if (index < m_config.size())
        {
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
            if (m_check_index_already_configured(number) == INVALID_ROTOR_MAPPING)
            {
                return INVALID_ROTOR_MAPPING;
            }
            /* save in m_config */
            m_config[index] = number;
            continue;
        }

        /* remainder after the first 26 elements - notches */

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
        /* save in m_notch */
        m_notches[number] = 1; // update from default value of -1 (no notch) to 1 (has notch)
    }    

    /* make sure all indexes have been configured */
    if (m_check_all_indexes_configured() == INVALID_ROTOR_MAPPING)
    {
        return INVALID_ROTOR_MAPPING;
    }
    return NO_ERROR;
}             

void Rotor::m_print_notches()
{
    std::cout << "[";
    for (int x : m_notches) 
    {
        std::cout << x << " ";
    }
    std::cout << "]";
    std::cout << std::endl;
}

bool Rotor::m_has_notch()
{
    /* check if there is a notch */
    if (m_notches[m_displacement] == 1)
    {
        /* there is a notch */
        return true;
    }
    return false;
}

void Rotor::m_turn_rotor()
{
    m_displacement = (m_displacement + 1) % 26;
}
