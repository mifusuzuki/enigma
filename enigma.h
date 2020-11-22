/* Enigma Header */
#ifndef ENIGMA_H
#define ENIGMA_H

#include "errors.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"

#include <string>
#include <vector>

class Enigma 
{
public:
    Enigma(); 
    void m_confirm_enigma_has_rotor() {m_has_rotor = true;} // set m_has_rotor to bool true 
    bool m_has_one_or_more_rotors() {return m_has_rotor;} // check enigma has at least one rotor
    int m_setup_plugboard(const std::string& pb_file); // set up plugboard 
    int m_setup_reflector(const std::string& rf_file); // set up reflector
    int m_setup_rotors(const std::vector<std::string>& rot_file, const std::string& pos_file); // set up rotors
    void m_stabilise_rotors(int last_rot); // recursive function called on the right most rotor to stabilise the positions after one rotation
    int m_pre_reflector_rotor_mechanism(int index); // rotor mechanism on the way to reflector
    int m_post_reflector_rotor_mechanism(int character); // rotor mechanism on the way from reflector
    int m_encrypt_message(char& character); // base function to encrypt specified character
private:
    bool m_has_rotor; // set to false by default but is set to true if one or more rotors found in device
    PlugBoard m_plugboard; // plugboard for this enigma
    Reflector m_reflector; // reflector for this enigma
    std::vector<Rotor> m_rotors; // array that stores series of rotors for this enigma
};

#endif
