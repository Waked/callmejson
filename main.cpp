/**
 *  Created by Kamil Dzierzanowski and
 *  published under GNU GPL v.3.0 license.
 *
 *  Claiming authorship to this project
 *  is forbidden during the course it
 *  refers to.
 **/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//#define TEST

#define TAB "  "

using namespace std;

int g_indentlevel = 0;

enum ElementType {
    PROPERTY,
    OBJECT,
    ARRAY
};

void indent(ofstream& outstream, int howmany) {
    while (howmany >= 0){
        outstream << TAB;
        howmany--;
    }
}

ElementType getToNextValue(ifstream& stream){
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
string getNextKey(ifstream& instream){
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

///Reads contents of a JS object and pushes them to
///passed object
void readObject(ifstream& instream, Object& thisobj){
    string tempkey;
    ElementType type;
    Element* objtopush;

    tempkey = getNextKey(instream);
    while (tempkey != "}"){
        type = getToNextValue(instream);
        if (type == PROPERTY){
            objtopush = new Property;
            tempval = readWord(instream);
            returnobj.setKey(tempkey);
            Property prop;
            prop
        } else {
            objtopush = new Object;
            switch (type){
            case OBJECT:
                objtopush.
            }
        }

        thisobj.getElements().push_back()
        tempkey = getNextKey();
    }
}

class Element{
protected:
    string m_key;
    int m_embedlevel;
public:
    Element();
    string getKey();
    int getEmbedLevel();
    void setKey(string);
    void setEmbedLevel(int);
    virtual void printToStream(ofstream&) {}
};

Element::Element():
m_key(""), m_embedlevel(0) {
    #ifdef TEST
    cout << "Creating \"Element\" object..." << endl;
    #endif
}

string Element::getKey(){
    return m_key;
}

int Element::getEmbedLevel(){
    return m_embedlevel;
}

void Element::setKey(string name){
    m_key = name;
}

void Element::setEmbedLevel(int lvl){
    m_embedlevel = lvl;
}

class Property : public Element{
private:
    string m_value;
public:
    string getValue();
    void setValue(string);
    void printToStream(ofstream&);
};

string Property::getValue(){
    return m_value;
}

void Property::setValue(string val){
    m_value = val;
}

void Property::printToStream(ofstream& outstream){
    indent(outstream, g_indentlevel);
    outstream << "<" << getKey() << ">" << getValue() << "</" << getKey() << ">" << endl;
}

class Object : public Element{
protected:
    vector<Element> m_elements;
    int m_count;
    ElementType m_type;
public:
    Object(ElementType = OBJECT);
    Object& operator++();   //Adds 1 to m_count
    Object operator++(int); //-''-
    void addCount();        //-''-
    int getCount();
    void setCount(int);
    void setType(ElementType);
    ElementType getType();
    vector<Element>& getElements();
    void printToStream(ofstream&);
};

Object::Object(ElementType t):
m_count(0), m_type(t) {
    #ifdef TEST
    cout << "Creating \"Object\" object..." << endl;
    #endif
}

Object& Object::operator++(){
    m_count++;
    return (*this);
}

Object Object::operator++(int){
    Object temp(*this);
    ++(*this);
    return temp;
}

int Object::getCount(){
    return m_count;
}

void Object::setCount(int ct){
    m_count = ct;
}

void Object::addCount(){
    m_count++;
}

void Object::setType(ElementType targettype){
    m_type = targettype;
}

ElementType Object::getType(){
    return m_type;
}

vector<Element>& Object::getElements(){
    return m_elements;
}

void Object::printToStream(ofstream& outstream){
    indent(outstream, g_indentlevel);
    outstream << "<" << this->getKey() << ">" << endl;
    g_indentlevel++;
    for (int i = 0; i < getCount(); i++){
        m_elements[i].printToStream(outstream);
    }
    g_indentlevel--;
    indent(outstream, g_indentlevel);
    outstream << "</" << this->getKey() << ">" << endl;
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
    document.setKey(getNextKey(ifile));
    getToNextValue(ifile);
    //getNextKey

    cout << "Klucz glownego obiektu: " << document.getKey() << endl;

    return 0;
}
