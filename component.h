/* Component Header */
#ifndef COMPONENT_H
#define COMPONENT_H

#include <array>
#include <string>
#include <vector>

class Component
{
public:
    Component();
    virtual int m_load_config() = 0; // load each component configurations from raw_data in into corresponding m_config
    int m_read_file(const std::string& path);  // read files via given path and load the data into raw_data
    void m_print_config(); // print m_config
    int m_get_char(int index); // get the character element in m_config[index]
    int m_get_position(int character); // get the position of character in m_config
protected: 
    std::vector<std::string> m_raw_data; // raw data for retrieved from data file
    std::array<int, 26> m_config; // configuration (mapping) 
};

#endif
