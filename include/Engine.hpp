#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <boost/regex.hpp>

#define TEST

#include "Element.hpp"
#include "Object.hpp"
#include "Property.hpp"
#include "json_in.h"
#include "json_out.h"
#include "xml_out.h"

enum filetype{XML, JSON};

class Engine {
public:
    Engine(){}
    ~Engine();
    bool readfile(string);
    bool writefile(string);
    bool getconvtype(int);
private:
    ifstream ifile;
    ofstream ofile;
    string path_in, path_out;
    filetype type_in, type_out;
    Object* document;
};

#endif // ENGINE_HPP
