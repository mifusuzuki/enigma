/* Enigma Header */
#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include <vector>

#include "errors.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"


class Enigma 
{
public:
    int m_setup_plugboard(const std::string& pb_file);
    int m_setup_reflector(const std::string& rf_file);
    int m_setup_rotors(const std::vector<std::string>& rot_file, const std::string& pos_file);
    void m_stabilise_rotors(int last_rot);
    int m_pre_reflector_rotor_mechanism(int index);
    int m_post_reflector_rotor_mechanism(int character);
    int m_encrypt_message(std::string& message);
private:
    PlugBoard m_plugboard;
    Reflector m_reflector;
    std::vector<Rotor> m_rotors;
};

#endif
