/* Plugboard Header */
#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <string>
#include <vector>

#include "component.h"

class PlugBoard : public Component
{
public:
    int m_load_config() override;
private:
    int m_check_odd_num_of_param(int count);
    int m_check_index_already_configured(int prev_val, int val);
};

#endif

