#include "../include/Engine.hpp"

using namespace std;
using namespace boost;

Engine::~Engine(){
    if (document)
        delete document;
    ifile.close();
    ofile.close();
}

bool Engine::readfile(string path){
    path_in = path;
    ifile.open(path_in, fstream::in);
    if (!ifile.is_open()){
        cout << "[ERROR] Cannot open input file!" << endl;
        return false;
    }
    document = readJSON(ifile);
    cout << "File read to document variable" << endl;
    return true;
}

bool Engine::writefile(string path){
    path_out = path;
    ofile.open(path_out, fstream::out);
    if (!ofile.is_open()){
        cout << "[ERROR] Cannot open output file!" << endl;
        return false;
    }

    switch (type_out){
    case JSON:
        saveJSON(ofile, *document);
        cout << "Successfully stored \"document\" in JSON output file" << endl;
        break;
    case XML:
        saveXML(ofile, *document);
        cout << "Successfully stored \"document\" in XML output file" << endl;
        break;
    }
    return true;
}

bool Engine::getconvtype(int type){
    type_in = JSON;
    if (type == 0){
        type_out = JSON;
    } else {
        type_out = XML;
    }
    return 1;
}
