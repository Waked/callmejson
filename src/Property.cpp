#include <string>
#include <fstream>
#include <iostream>

#include "../include/Property.hpp"

Property::Property() {
    m_type = PROPERTY;
}

std::string Property::getValue(){
    return m_value;
}

void Property::setValue(std::string val){
    m_value = val;
}
