#include <fstream>
#include <string>
#include <iostream>
#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_out.h"

#define TAB "  "

using namespace std;

void insertWhitespace(ofstream& outstream, string what, int howmany){
    while (howmany > 0){
        outstream << what;
        howmany--;
    }
}

void printElement(ofstream& targetstream, Element& element, int indentlevel){
    switch (element.getElemType()){
    case PROPERTY:
        cout << "Lel at property" << endl;
        insertWhitespace(targetstream, TAB, indentlevel);
        targetstream << "<" << element.getKey() << ">"
                     << dynamic_cast<Property&>(element).getValue()
                     << "</" << element.getKey() << ">\n";
        break;
    case OBJECT:
        insertWhitespace(targetstream, TAB, indentlevel);
        targetstream << "<" << element.getKey() << ">\n";
        for (int i = 0; i < dynamic_cast<Object&>(element).getCount()-1; i++){
            printElement(targetstream, dynamic_cast<Object&>(element).elements().at(i), indentlevel+1);
        }
        targetstream << "\n";
        insertWhitespace(targetstream, TAB, indentlevel);
        targetstream << "</" << element.getKey() << ">\n";
        break;
    case ARRAY:
        for (int i = 0; i < dynamic_cast<Object&>(element).getCount(); i++){
        insertWhitespace(targetstream, TAB, indentlevel);
        targetstream << "</" << element.getKey() << ">\n";
        printElement(targetstream, dynamic_cast<Object&>(element).elements()[i], indentlevel+1);
        insertWhitespace(targetstream, TAB, indentlevel);
        targetstream << "\n";
        }
        break;
    }
}
