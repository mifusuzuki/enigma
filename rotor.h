/* Rotor Header */
#ifndef ROTOR_H
#define ROTOR_H

#include "component.h"

#include <string>
#include <vector>

class Rotor : public Component
{
public:
    Rotor(int init_pos); // set displacement of the rotor to given initial position
    int m_load_config() override; // carry out checks in m_raw_data and load it into m_config and m_notches
    void m_print_notches(); // print notch array
    int m_get_displacement() {return m_displacement;} // get displacement of the rotor
    bool m_has_notch(); // check if the rotor, at current displacement, has a notch at the top
    void m_turn_rotor(); // turn rotor 
private:
    int m_displacement; // displacement of the rotor from the global reference
    std::array<int, 26> m_notches; // array showing where the notches are (m_notches[index] = 1 meas there is a notch at "index")
    int m_check_index_already_configured(int val); // check no already-configued index is being loaded 
    int m_check_all_indexes_configured(); // check no yet-to=be configured index
};

#endif
