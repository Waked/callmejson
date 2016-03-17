#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#DEFINE TEST

#define TAB "  "

using namespace std;

int g_indentlevel = 0;

const char g_keychars = {
    '{', '}', '[', ']', ':', '"'
}

enum ElementType {
    PROPERTY,
    OBJECT,
    ARRAY
};

void indent(ofstream file, int howmany) {
    while (howmany >= 0){
        file << TAB;
        lvl--;
    }
}

ElementType getToNextValue(ifstream stream){
    char tempc;
    stream >> tempc;
    while (tempc != '"' && tempc != '{' && tempc != '[')
        stream >> tempc;
    switch (tempc) {
    case '"':
        return PROPERTY;
    case '{':
        return OBJECT;
    case '[':
        return ARRAY;
    }
}

string getNextKey(ifstream stream){
    char tempc;
    string tempstr = "";
    stream >> tempc;
    while (tempc != '"')
        file >> tempc;
    stream >> tempc;
    while (tempc != '"'){
        tempstr += tempc;
        stream >> tempc;
    }
    return tempstr;
}

string readWord(ifstream stream){
    string tempstr = "";
    char tempc;
    stream >> tempc;
    while (tempc != '"'){
        tempstr += tempc;
        stream >> tempc;
    }
    return tempstr;
}

class Element{
protected:
    string m_key;
public:
    Element();
    string getKey();
    void setKey(string);
    virtual void printToStream(ofstream);
};

Element::Element()
m_name("") {
    #IFDEF TEST
    cout << "Creating \"Element\" object..." << endl;
    #ENDIF
}

string Element::getName(){
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
    void printToStream(ofstream);
};

string Property::getValue(){
    return m_value;
}

void Property::setValue(string val){
    m_value = val;
}

void Property::printToStream(ofstream outstream){
    indent(outstream, g_indentlevel);
    outstream << "<" << getKey() << ">"
              << getValue() << "</" << getKey() << ">" << endl;
}

class Object : public Element{
protected:
    vector<Element> m_elements;
    int m_count;
    ObjectType m_type;
public:
    Object(ObjectType = OBJECT);
    Object& operator++();
    Object operator++(int);
    int getCount();
    vector<Element>& getElements();
    void printToStream(ofstream);
};

Object::Object(ObjectType t):
m_elementcount(0), m_type(t) {
    #IFDEF TEST
    cout << "Creating \"Object\" object..." << endl;
    #ENDIF
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

vector<Element>& Object::GetElements(){
    return (*m_elements);
}

void Object::printToStream(ofstream outstream){
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

    if (!ifile.open("test_json.json", fstream::in)){
        cout << "[ERROR] Cannot open input file!" << endl;
        return 0;
    }
    if (!ofile.open("out_xml.xml", fstream::out)){
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
    getToNextValue();

    return 0;
}
