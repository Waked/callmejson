#include <string>

#include "../include/Element.hpp"

Element::Element():
m_key(""), m_embedlevel(0) {
    #ifdef TEST
    cout << "Creating \"Element\" object..." << endl;
    #endif
}

std::string Element::getKey(){
    return m_key;
}

int Element::getEmbedLevel(){
    return m_embedlevel;
}

void Element::setKey(std::string name){
    m_key = name;
}

void Element::setEmbedLevel(int lvl){
    m_embedlevel = lvl;
}
