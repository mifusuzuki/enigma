/* Rotor Header */
#ifndef ROTOR_H
#define ROTOR_H

#include <string>
#include <vector>

#include "component.h"


class Rotor : public Component
{
public:
    Rotor(int init_pos);
    int m_load_config() override;
    void m_print_notches();
    int m_get_displacement() {return m_displacement;} 
    bool m_has_notch();
    void m_turn_rotor();
private:
    int m_displacement;
    std::array<int, 26> m_notches; 
    int m_check_num_of_param(int count);
    int m_check_index_already_configured(int val);
    int m_check_all_indexes_configured();
};

#endif
