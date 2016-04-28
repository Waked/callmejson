#ifndef JSON_IN_H
#define JSON_IN_H

#include <fstream>

using namespace std;

Object* readSquares(ifstream& in);
Object* readBracket(ifstream& in);
Object* readJSON(ifstream& in);

#endif // JSON_IN_H
