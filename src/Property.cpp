#include <string>
#include <fstream>
#include <iostream>

#include "../include/Property.hpp"

extern int g_indentlevel;
void indent(std::ofstream&, int);

std::string Property::getValue(){
    return m_value;
}

void Property::setValue(std::string val){
    m_value = val;
}

void Property::printToStream(std::ofstream& outstream){
    indent(outstream, g_indentlevel);
    outstream << "<" << getKey() << ">" << getValue() << "</" << getKey() << ">\n";
}
