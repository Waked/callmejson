#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <fstream>

enum ElementType {
    PROPERTY,
    OBJECT,
    ARRAY
};

class Element{
protected:
    std::string m_key;
    ElementType m_type;
public:
    Element();
    virtual ~Element() {}
    std::string getKey();
    void setKey(std::string);
    ElementType getElemType();
    void setElemType(ElementType);
    Element* newLikeThis();
};

#endif
