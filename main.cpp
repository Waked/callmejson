/**
 *  Created by Kamil Dzierzanowski and
 *  published under GNU GPL v.3.0 license.
 *
 *  Claiming authorship to this project
 *  is forbidden for the duration of
 *  the course it is made for.
 **/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "include/Element.hpp"
#include "include/Object.hpp"
#include "include/Property.hpp"
#include "include/indent.h"

//#define TEST

using namespace std;

int g_indentlevel = 0;

void indent(std::ofstream& outstream, int howmany) {
    while (howmany >= 0){
        outstream << TAB;
        howmany--;
    }
}

string readWord(ifstream& instream){
    string tempstr = "";
    char tempc;
    instream >> tempc;
    while (tempc != '"'){
        tempstr += tempc;
        instream >> tempc;
    }
    return tempstr;
}

///Reads the stream up to next parenthesis, then
///extracts the word inside them. Returns closing
///brace or bracket upon reaching one.
string nextKey(ifstream& instream){
    char tempc;
    string tempstr = "";
    instream >> tempc;
    while (tempc != '"' && !instream.eof() && tempc != '}' && tempc != ']')
        instream >> tempc;
    if (tempc == '}' || tempc == ']'){
        tempstr = "" + tempc;
        return tempstr;
    }
    if (instream.eof())
        return tempstr;
    return readWord(instream);
}

ElementType nextValue(ifstream& stream){
    char tempc;
    stream >> tempc;
    ElementType ret_val;
    while (tempc != '"' && tempc != '{' && tempc != '[')
        stream >> tempc;
    switch (tempc) {
    case '"':
        ret_val = PROPERTY;
        break;
    case '{':
        ret_val = OBJECT;
        break;
    case '[':
        ret_val = ARRAY;
        break;
    }
    return ret_val;
}

///Reads contents of a JS object and pushes them to
///passed object
void readObject(ifstream& instream, Object& thisobj){
    string tempkey;
    ElementType type;
    Element* pushed_elem;

    tempkey = nextKey(instream);
    while ( tempkey != "}" && tempkey != "]" ){
        type = nextValue(instream);
        if (type == PROPERTY){
            pushed_elem = new Property;
            pushed_elem->setKey(tempkey);
            dynamic_cast<Property*>(pushed_elem)->setValue(readWord(instream));
        } else {
            pushed_elem = new Object;
            pushed_elem->setKey(tempkey);
            dynamic_cast<Object*>(pushed_elem)->setElemType(type);
            readObject(instream, *( dynamic_cast<Object*>(pushed_elem) ));
        }
        thisobj.getElements().push_back(*pushed_elem);
        thisobj++;
        tempkey = nextKey(instream);
    }
}

int main()
{
    ifstream ifile;
    ofstream ofile;
    char chbuf;

    ifile.open("test_json.json", fstream::in);
    if (!ifile.is_open()){
        cout << "[ERROR] Cannot open input file!" << endl;
        return 0;
    }

    ofile.open("out_xml.xml", fstream::out);
    if (!ofile.is_open()){
        cout << "[ERROR] Cannot open output file!" << endl;
        return 0;
    }

    ifile >> chbuf;
    if (chbuf != '{'){
        cout << "Input file is not a JSON file!" << endl;
        return 0;
    }

    Object document;
    document.setKey(nextKey(ifile));
    nextValue(ifile);
    //getNextKey

    cout << "Klucz glownego obiektu: " << document.getKey() << endl;

    return 0;
}
