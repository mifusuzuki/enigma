/* Reflector Header */
#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "component.h"

#include <string>
#include <vector>

class Reflector : public Component
{
public:
    int m_load_config() override; // carry out checks in m_raw_data and load it into m_config 
private:
    int m_check_index_already_configured(int prev_val, int val); // check no already-configued index is being loaded 
};                                           

#endif
