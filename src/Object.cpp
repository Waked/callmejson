#include <fstream>
#include <iostream>

#include "../include/Object.hpp"

Object::Object() :
m_count(0) {
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

Element& Object::getElement(int n){
    return m_elements.at(n);
}

void Object::addElement(Element target){
    m_elements.push_back(target);
}
