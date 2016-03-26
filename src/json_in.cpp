#include <iostream>
#include <fstream>
#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_in.h"

using namespace std;

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

///Reads the stream up to next parenthesis, then
///extracts the word inside them. Returns closing
///brace or bracket upon reaching one.
string readKey(ifstream& instream){
    char tempc;
    string tempstr = "";
    instream >> tempc;
    while (!instream.eof() && tempc != '"' && tempc != '}' && tempc != ']')
        instream >> tempc;
    if (tempc == '}' || tempc == ']'){
        if (!instream.eof())
            tempstr += tempc;
        return tempstr;
    }
    return readWord(instream);
}

ElementType nextValue(ifstream& stream){
    char tempc;
    stream >> tempc;
    ElementType ret_val;
    while (tempc != '"' && tempc != '{' && tempc != '[')
        stream >> tempc;
    switch (tempc) {
    case '"':
        ret_val = PROPERTY;
        break;
    case '{':
        ret_val = OBJECT;
        break;
    case '[':
        ret_val = ARRAY;
        break;
    }
    return ret_val;
}

///Reads contents of a JS object and pushes them to
///passed object
void readObject(ifstream& instream, Object& thisobj){
    string tempkey;
    ElementType type;
    Element* pushed_elem;
    if (thisobj.getElemType() == ARRAY)
        isarray = 1;

    tempkey = nextKey(instream, isarray);
    while ( tempkey != "}" && tempkey != "]" ){
        if (!isarray)
            type = nextValue(instream);
        else {
            if (tempkey == "\"")
                type = PROPERTY;
            if (tempkey == "{")
                type = OBJECT;
            if (tempkey == "[")
                type = ARRAY;
        }
        if (type == PROPERTY){
            pushed_elem = new Property;
            if (!isarray)
                pushed_elem->setKey(tempkey);
            else
                pushed_elem->setKey("");
            dynamic_cast<Property*>(pushed_elem)->setValue(readWord(instream));
        } else {
            pushed_elem = new Object;
            if (!isarray)
                pushed_elem->setKey(tempkey);
            else
                pushed_elem->setKey("");
            readObject(instream, *( dynamic_cast<Object*>(pushed_elem) ));
        }
        pushed_elem->setElemType(type);
        cout << "Set " << pushed_elem->getKey() << " to type " << pushed_elem->getElemType() << endl;
        thisobj.elements().push_back(*pushed_elem);
        thisobj++;
        tempkey = nextKey(instream, isarray);
        delete pushed_elem;
    }
}

///Loads JSON document from file input stream into
///target root object of type Object, returns true
///on succes and false on failure
bool loadJSON(ifstream& input_stream, Object& target){
    char tempchar;
    input_stream >> tempchar;
    if (tempchar != '{')
        return false;
    target.setKey(nextKey(input_stream));
    target.setElemType(nextValue(input_stream));
    readObject(input_stream, target);
    return true;
}

void toNextValue(ifstream& instream){
    char tmpchar = '\0';
    while (tmpchar != '"' && tmpchar != '{' && tmpchar != '[')
        instream >> tmpchar;
    instream.putback(tmpchar);
}

ElementType checkTypeOf(char ch){
    if (ch == '"')
        return PROPERTY;
    if (ch == '{')
        return OBJECT;
    if (ch == '[')
        return ARRAY;
}

Element readValue(ifstream& instream){
    toNextValue(instream);
    ElementType type = checkType(instream);
    if (type == PROPERTY){
        Property returnobject;
        returnobject.setValue(readWord(instream));
        return returnobject;
    } else if (type == OBJECT){
        Object returnobject;

    }
}

///Returns a key-value pair as an Element
Element& readKVPair(ifstream& instream){
    Element* outputelement = new Element;
    string keytoassign;
    keytoassign = readKey();
    *outputelement = readValue();
    outputelement->setKey(keytoassign);
    return *outputelement;
}
