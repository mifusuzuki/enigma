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
    Enigma();
    void m_confirm_enigma_has_rotor() {m_has_rotor = true;}
    bool m_has_one_or_more_rotors() {return m_has_rotor;}
    int m_setup_plugboard(const std::string& pb_file);
    int m_setup_reflector(const std::string& rf_file);
    int m_setup_rotors(const std::vector<std::string>& rot_file, const std::string& pos_file);
    void m_stabilise_rotors(int last_rot);
    int m_pre_reflector_rotor_mechanism(int index);
    int m_post_reflector_rotor_mechanism(int character);
    int m_encrypt_message(char& character);
private:
    bool m_has_rotor;
    PlugBoard m_plugboard;
    Reflector m_reflector;
    std::vector<Rotor> m_rotors;
};

#endif
