#include <fstream>
#include <iostream>

#define TAB " "

#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_out.h"

using namespace std;

void printJProperty(ofstream& outputstr, Property& target_prop, int level){
    for (int i = 0; i < level; i++)
        outputstr << TAB;
    if (target_prop.getKey() != "")
        outputstr << "\"" << target_prop.getKey() << "\": ";

    outputstr << "\"" << target_prop.getValue() << "\"";
}

void printJObject(ofstream& outputstr, Object& target_obj, int level){
    for (int i = 0; i < level; i++)
        outputstr << TAB;
    if (target_obj.getKey() != "")
        outputstr << "\"" << target_obj.getKey() << "\": ";

    switch (target_obj.getElemType()){
    case OBJECT:
        outputstr << "{" << endl;
        break;
    case ARRAY:
        outputstr << "[" << endl;
    }

    for (int i = 0; i < target_obj.getCount(); i++){
        ElementType type = target_obj.getElement(i).getElemType();

        switch (type){
            case PROPERTY: {
                Property& temp_prop = static_cast<Property&>(target_obj.getElement(i));
                printJProperty(outputstr, temp_prop, level+1);
                break;
            }
            case ARRAY:
            case OBJECT: {
                Object& temp_obj = static_cast<Object&>(target_obj.getElement(i));
                printJObject(outputstr, temp_obj, level+1);
                break;
            }
        }
        if (i < target_obj.getCount()-1)
            outputstr << ",";
        outputstr << endl;
    }

    for (int i = 0; i < level; i++)
        outputstr << TAB;
    switch (target_obj.getElemType()){
    case OBJECT:
        outputstr << "}";
        break;
    case ARRAY:
        outputstr << "]";
    }
}

void saveJSON(ofstream& outputstr, Object& document){
    outputstr << "{" << endl;
    Object& mainobj = static_cast<Object&>(document.getElement(0));
    printJObject(outputstr, mainobj, 1);
    outputstr << endl << "}" << endl;
}
