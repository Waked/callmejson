/**
 *  Created by Kamil Dzierzanowski and
 *  published under GNU GPL v.3.0 license.
 *
 *  Claiming authorship to this project
 *  is forbidden for the duration of
 *  the course it is made for.
 **/

#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

#define TEST

#include "include/Element.hpp"
#include "include/Object.hpp"
#include "include/Property.hpp"
#include "include/json_in.h"
#include "include/json_out.h"
#include "include/xml_out.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream ifile;
    ofstream ofile;

    string path_in, path_out;

    if (argc < 2){
        cout << "Sourcefile path (relative): ";
        cin >> path_in;
    } else {
        path_in = argv[1];
    }

    ifile.open(path_in, fstream::in);
    if (!ifile.is_open()){
        cout << "[ERROR] Cannot open input file!" << endl;
        return 0;
    }

    if (argc < 3){
        cout << "Output path (relative): ";
        cin >> path_out;
    } else {
        path_out = argv[2];
    }

    ofile.open(path_out, fstream::out);
    if (!ofile.is_open()){
        cout << "[ERROR] Cannot open output file!" << endl;
        return 0;
    }

    Object* document;
    document = readJSON(ifile);
    cout << "Successfully loaded a JSON document into \"document\" object" << endl;

    saveJSON(ofile, *document);
    cout << "Successfully stored \"document\" in output file" << endl;

    ifile.close();
    ofile.close();

    return 0;
}
