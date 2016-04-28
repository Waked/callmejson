#ifndef JSON_OUT_H
#define JSON_OUT_H

#include <fstream>

#include "Object.hpp"
#include "Property.hpp"

using namespace std;

void printJProperty(ofstream& outputstr, Property& target_prop, int level);
void printJObject(ofstream& outputstr, Object& target_obj, int level);
void saveJSON(ofstream& outputstr, Object& document);

#endif // JSON_OUT_H
