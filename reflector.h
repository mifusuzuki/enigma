/* Reflector Header */
#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <string>
#include <vector>

#include "component.h"


class Reflector : public Component
{
public:
    int m_load_config() override;
private:
    int m_check_index_already_configured(int prev_val, int val);
};
                                                   

#endif
