#ifndef XML_OUT_H
#define XML_OUT_H

#include "Element.hpp"
#include "Object.hpp"

void tag(std::ofstream&, std::string, bool);
Element* newOfType(Element&);
Element* cloneElement(Element&);
void printElement(std::ofstream&, Element&);
void printXML(std::ofstream&, Object&);

#endif
