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
/*
Object readObject(ifstream& instream) {
    string tempkey = getNextKey(instream);
    string tempval = "";
    ElementType type;
    Object* returnobj = new Object;
    while (tempkey != "}"){
        type = getToNextValue(instream);
        if (type == PROPERTY){
            tempval = readWord(instream);
            returnobj.setKey(tempkey);
            Property prop;
            prop
            returnobj.getElements().push_back()
        }
        tempkey = getNextKey();
    }
}*/

class Element{
protected:
    string m_key;
public:
    Element();
    string getKey();
    void setKey(string);
    virtual void printToStream(ofstream&) {}
};

Element::Element():
m_key("") {
    #ifdef TEST
    cout << "Creating \"Element\" object..." << endl;
    #endif
}

string Element::getKey(){
    return m_key;
}

void Element::setKey(string name){
    m_key = name;
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
    Object& operator++();
    Object operator++(int);
    int getCount();
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
