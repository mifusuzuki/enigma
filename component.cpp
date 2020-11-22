/* Component Implementation*/
#include "component.h"

#include "errors.h"
#include "helper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Component::Component()
{
    /* by default all elements in m_config are set to -1 */
    m_config.fill(-1);
}

int Component::m_read_file(const std::string& path)
{
    /* open file */
    std::ifstream file;
    file.open(path);

    /* check file opening issue */
    if (file.fail())
    {
        print_error_message(ERROR_OPENING_CONFIGURATION_FILE);
        return ERROR_OPENING_CONFIGURATION_FILE; 
    }

    /* read file */
    std::string str;
    while (file >> str) 
    {
        /* save data into m_raw_data */
        m_raw_data.push_back(str);
    }
    file.close();
    return NO_ERROR;
}          

void Component::m_print_config()
{
    std::cout << "[";
    for (int x : m_config) 
    {   
        /* print each element */
        std::cout << x << " ";
    }
    std::cout << "]";
    std::cout << std::endl;
}

int Component::m_get_char(int index) 
{
    /* check if any converion specified */
    if (m_config[index] == -1)
    {
        /* no conversion */
        return index;
    }
    /* return conversion */
    return m_config[index];
}

int Component::m_get_position(int character)
{
    /* go through the mapping and find the position of the target character */
    for (unsigned int i=0; i<m_config.size(); i++)
    {
        /* target found - returning position */
        if (m_config[i] == character)
        {
            return i;
        }
    }
    return -1;
}
