/* Rotor Implementation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "helper.h"
#include "errors.h"
#include "rotor.h"
#include "component.h"

Rotor::Rotor(int init_pos) : Component()
{   
    /* set the rotor's default config */
    m_displacement = init_pos;

    /* default notch array */
    m_notches.fill(-1);
}

int Rotor::m_check_index_already_configured(int val)
{
    //std::cout << "m_check_index_already_configured called" <<std::endl;
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
    //std::cout << "m_check_all_indexes_configured called" <<std::endl;
    for (int i=0; i<26; i++)
    {
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
    unsigned int index = 0;
    for (; index < m_raw_data.size(); index++)
    {
        /* first 26 elements - config */
        
        if (index < m_config.size())
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
            if (m_check_index_already_configured(number) == INVALID_ROTOR_MAPPING)
            {
                return INVALID_ROTOR_MAPPING;
            }
            /* save in m_config */
            m_config[index] = number;
            continue;
        }

        /* remainder after the first 26 elements - notches */

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
    if (m_notches[m_displacement] == 1)
    {
        /* there is a notch */
        return true;
    }
    return false;
}

void Rotor::m_turn_rotor()
{
    m_displacement--;
    if (m_displacement == -1)
    {
        m_displacement = 25;
    }

}
