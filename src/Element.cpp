#include <string>

#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"

Element::Element():
m_key("") {
}

std::string Element::getKey(){
    return m_key;
}

void Element::setKey(std::string name){
    m_key = name;
}

void Element::setElemType(ElementType targettype){
    m_type = targettype;
}

ElementType Element::getElemType(){
    return m_type;
}

Element* Element::newLikeThis(){
    Element* returnobj;
    if (this->getElemType() == PROPERTY){
        returnobj = new Property;
    } else {
        returnobj = new Object;
    }
    return returnobj;
}
