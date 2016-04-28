#ifndef XML_OUT_H
#define XML_OUT_H

#include "Element.hpp"
#include "Object.hpp"

using namespace std;

void printProperty(ofstream& outputstr, Object& target_obj, int level = 0);
void printObject(ofstream& outputstr, Object& target_obj, int level = 0);
void printArray(ofstream& outputstr, Object& target_obj, int level = 0);
void saveXML(ofstream& outputstr, Object& target_doc);

#endif
