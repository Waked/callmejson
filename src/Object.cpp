#include <fstream>
#include <iostream>

#include "../include/Object.hpp"

extern int g_indentlevel;
void indent(std::ofstream&, int);

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

void Object::setElemType(ElementType targettype){
    m_type = targettype;
}

ElementType Object::getElemType(){
    return m_type;
}

std::vector<Element>& Object::getElements(){
    return m_elements;
}

void Object::printToStream(std::ofstream& outstream){
    indent(outstream, g_indentlevel);
    outstream << "<" << this->getKey() << ">\n";
    g_indentlevel++;
    for (int i = 0; i < getCount(); i++){
        m_elements[i].printToStream(outstream);
    }
    g_indentlevel--;
    indent(outstream, g_indentlevel);
    outstream << "</" << this->getKey() << ">\n";
}
