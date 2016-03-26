#ifndef JSON_OUT_H
#define JSON_OUT_H

#include "Element.hpp"

void insertWhitespace(std::ofstream&, std::string what, int howmany);
void printElement(std::ofstream&, Element& element, int indentlevel);

#endif // JSON_OUT_H
