#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <fstream>

class Element{
protected:
    std::string m_key;
    int m_embedlevel;
public:
    Element();
    std::string getKey();
    int getEmbedLevel();
    void setKey(std::string);
    void setEmbedLevel(int);
    virtual void printToStream(std::ofstream&) {}
};

#endif
