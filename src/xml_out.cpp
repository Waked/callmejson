#include <fstream>
#include <typeinfo>
#include "../include/xml_out.h"
#include "../include/Element.hpp"
#include "../include/Property.hpp"
#include "../include/Object.hpp"

#define TAB "  "

#include <iostream>

using namespace std;

///---------------------- FIRST ATTEMPT ----------------------------

enum {
    OPENING, CLOSING
};

void indent(ofstream& outstream, int level){
    for (int i = 0; i < level; i++)
        outstream << TAB;
}

///Prints a markup tag to given stream containing given name,
///last parameter defines whether it's an opening or closing tag
void tag(ofstream& outstream, string name, bool openclose){
    string outputstr = "<";
    if (openclose)
        outputstr += "/";
    outputstr += name;
    outputstr += ">";
    outstream << outputstr;
}

///Returns a newly allocated Element of the same
///type like given object
Element* newOfType(Element& source){
    Element* returnptr;
    switch(source.getElemType()){
    case PROPERTY:
        returnptr = new Property;
        break;
    case ARRAY:
    case OBJECT:
        returnptr = new Object;
        break;
    }
    return returnptr;
}

Element* cloneElement(Element& source) {
    ElementType type = source.getElemType();
    Element* returnobj;
    if (type == PROPERTY){
        returnobj = new Property;
        *returnobj = source;
    } else {
        returnobj = new Object;
        *returnobj = source;
    }
    return returnobj;
}

///Prints an opening tag with $target's key name, then outputs
///$target's content, then prints a corresponding closing tag
void printElement(ofstream& outstream, Element& target){
    static int indentlevel = 0;
    ElementType type = target.getElemType();
    cout << "Type name: " << typeid(target).name() << endl;
    if (type == PROPERTY){
        indent(outstream, indentlevel);
        tag(outstream, target.getKey(), OPENING);
        Property temp = dynamic_cast<Property&>(target);
        cout << "Fine here" << endl;
        outstream << temp.getValue();
        tag(outstream, target.getKey(), CLOSING);
        outstream << "\n";
    } else if (type == OBJECT){
        Object temp = dynamic_cast<Object&>(target);
        indent(outstream, indentlevel);
        tag(outstream, temp.getKey(), OPENING);
        indentlevel += 1;
        for (int i = 0; i < temp.getCount(); i++){
            outstream << "\n";
            printElement(outstream, temp.getElement(i));
        }
        indentlevel -= 1;
        outstream << "\n";
        indent(outstream, indentlevel);
        tag(outstream, target.getKey(), CLOSING);
        outstream << "\n";
    } else if (type == ARRAY) {
        Object temp = dynamic_cast<Object&>(target);
        for (int i = 0; i < temp.getCount(); i++){
            Element* clone = cloneElement(temp.getElement(i));
            clone->setKey(temp.getKey());
            printElement(outstream, *clone);
            delete clone;
            outstream << "\n";
        }
    }
}

///Prints given Object to given file output stream -
///the object ought to be the main structure of the
///document, although there's no restriction here
void printXML(ofstream& outstream, Object& printed_obj){
    printElement(outstream, printed_obj);
}
