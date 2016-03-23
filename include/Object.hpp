#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include "Element.hpp"

enum ElementType {
    PROPERTY,
    OBJECT,
    ARRAY
};

class Object : public Element{
protected:
    std::vector<Element> m_elements;
    int m_count;
    ElementType m_type;
public:
    Object(ElementType = OBJECT);
    Object& operator++();   //Adds 1 to m_count
    Object operator++(int); //-''-
    void addCount();        //-''-
    int getCount();
    void setCount(int);
    void setElemType(ElementType);
    ElementType getElemType();
    std::vector<Element>& getElements();
    void printToStream(std::ofstream&);
};

#endif // OBJECT_H
