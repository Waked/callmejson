#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <fstream>
#include "Element.hpp"

class Property : public Element{
private:
    std::string m_value;
public:
    std::string getValue();
    void setValue(std::string);
    void printToStream(std::ofstream&);
};

#endif // PROPERTY_H
