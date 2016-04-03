#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include "Element.hpp"

class Object : public Element{
protected:
    std::vector<Element*> m_elements;
    int m_count;
public:
    Object();
    Object& operator++();   //Adds 1 to m_count
    Object operator++(int); //-''-
    int getCount();
    void setCount(int);
    Element& getElement(int);
    void addElement(Element*);
};

#endif // OBJECT_H
