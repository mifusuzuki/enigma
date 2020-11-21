/* Component Header */
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <array>
#include <vector>

class Component
{
public:
    Component();
    int m_read_file(const std::string& path);
    virtual int m_load_config() = 0;
    void m_print_config();
    int m_get_char(int index);
    int m_get_position(int character);
protected: 
    std::vector<std::string> m_raw_data;
    std::array<int, 26> m_config;   
};

#endif
