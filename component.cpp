/* Component Implementation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "helper.h"
#include "errors.h"
#include "component.h"

Component::Component()
{
    /* by default the conversion for all 26 indexes are set to -1 */
    m_config.fill(-1);
}

int Component::m_read_file(const std::string& path)
{
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
      //std::cout << "reading..." << std::endl;
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
        std::cout << x << " ";
    }
    std::cout << "]";
    std::cout << std::endl;
}

int Component::m_get_char(int index) 
{
    if (m_config[index] == -1)
    {
        return index;
    }
    return m_config[index];
}

int Component::m_get_position(int character)
{
    for (int i=0; i<m_config.size(); i++)
    {
        if (m_config[i] == character)
        {
            //std::cout << character <<" found! at index = " << i << std::endl;
            return i;
        }
    }
}
