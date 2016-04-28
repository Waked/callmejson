#include <fstream>
#include <iostream>

#include "../include/Object.hpp"

using namespace std;

Object::Object(){
    m_type = OBJECT;
    m_count = 0;
}

Object::Object(ElementType t){
    m_type = t;
    m_count = 0;
}

Object::Object(Object& rhs){
    this->m_count = rhs.getCount();
    this->m_type = rhs.getElemType();
    for (int i = 0; i < this->m_count; i++){
        Element* topush;
        topush = rhs.getElement(i).newLikeThis();
        (*topush) = rhs.getElement(i);
        this->addElement(topush);
    }
}

Object::~Object(){
    for (vector<Element*>::iterator it = m_elements.begin(); it != m_elements.end(); it++){
        delete *it;
    }
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
    return *(m_elements.at(n));
}

void Object::addElement(Element* target){
    m_elements.push_back(target);
    m_count++;
}
