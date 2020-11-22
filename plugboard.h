/* Plugboard Header */
#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "component.h"

#include <string>
#include <vector>

class PlugBoard : public Component
{
public:
    int m_load_config() override; // carry out checks in m_raw_data and load it into m_config 
private:
    int m_check_odd_num_of_param(int count); // check no odd number of parameter loaded
    int m_check_index_already_configured(int prev_val, int val); // check no already-configued index is being loaded 
};

#endif

