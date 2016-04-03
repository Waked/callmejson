#include <fstream>
#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_in.h"

using namespace std;

/// ------------------------ ONCE AGAIN --------------------------

///Reads characters up to next parenthesis and stores
///them in a string variable, then returns the string
string readWord(ifstream& instream){
    string tempstr = "";
    char tempc;
    instream >> tempc;
    while (tempc != '"'){
        tempstr += tempc;
        instream >> tempc;
    }
    return tempstr;
}

///Returns a string containing the next parenthesed
///word in stream
string readKey(ifstream& instream){
    char tempchar = 0;
    string tempstr = "";
    while (tempchar != '"')
        instream >> tempchar;
    return readWord(instream);
}

///Reads through characters (mainly whitespaces and
///doubledots) up to next character indicating a value
void toNextValue(ifstream& instream){
    char tmpchar = '\0';
    while (tmpchar != '"' && tmpchar != '{' && tmpchar != '[')
        instream >> tmpchar;
    instream.putback(tmpchar);
}

///Returns the type of value that starts with
///given character
ElementType checkTypeOf(char ch){
    if (ch == '"')
        return PROPERTY;
    if (ch == '{')
        return OBJECT;
    if (ch == '[')
        return ARRAY;
}

///Reads the stream through whitespaces and returns
///whether it's the object-closing character or not
bool isAtObjectEnd(ifstream& instream){
    char tmpchar = ' ';
    while (tmpchar == ' ')
        instream >> tmpchar;
    if (tmpchar == '}' || tmpchar == ']')
        return true;
    else {
        instream.putback(tmpchar);
        return false;
    }
}

///Checks next value-opening character and allocates
///appropriate object in memory, populates the object
///with data, then returns a pointer to the object
Element* readValueFrom(ifstream& instream){
    char openingchar;
    ElementType valuetype;
    Element* kvpair;
    toNextValue(instream);
    instream >> openingchar;
    valuetype = checkTypeOf(openingchar);
    if (valuetype == PROPERTY){
        Property* returnobject = new Property;
        returnobject->setElemType(valuetype);
        returnobject->setValue(readWord(instream));
        return returnobject;
    } else {
        Object* returnobject = new Object;
        returnobject->setElemType(valuetype);
        while (!isAtObjectEnd(instream)){
            kvpair = readKVPair(instream, (valuetype == ARRAY));
            returnobject->addElement(kvpair);
            (*returnobject)++;
        }
        return returnobject;
    }
}

///Returns an address to allocated Element with key and value
Element* readKVPair(ifstream& instream, bool without_key){
    Element* outputelement;
    string key = "";
    if (!without_key)
        key = readKey(instream);
    outputelement = readValueFrom(instream);
    outputelement->setKey(key);
    return outputelement;
}

///Loads JSON document from file input stream into
///target root object of type Object, returns true
///on succes and false on failure
void loadJSON(ifstream& instream, Object& target){
    char tempchar;
    Element* mainkvpair;
    instream >> tempchar;
    mainkvpair = readKVPair(instream, 0);
    target = *(dynamic_cast<Object*>(mainkvpair));
    delete mainkvpair;
}
