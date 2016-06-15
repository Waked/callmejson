#include <fstream>
#include <typeinfo>
#include "../include/xml_out.h"
#include "../include/Element.hpp"
#include "../include/Property.hpp"
#include "../include/Object.hpp"

#define TAB "  "

#include <iostream>

using namespace std;

void printProperty(ofstream& outputstr, Property& target_prop, int level){
    for (int i = 0; i < level; i++)
        outputstr << TAB;
    outputstr << "<" << target_prop.getKey() << ">";

    outputstr << target_prop.getValue();

    outputstr << "</" << target_prop.getKey() << ">" << endl;
}

void printObject(ofstream& outputstr, Object& target_obj, int level){
    for (int i = 0; i < level; i++)
        outputstr << TAB;
    outputstr << "<" << target_obj.getKey() << ">" << endl;

    for (int i = 0; i < target_obj.getCount(); i++){
        ElementType type = target_obj.getElement(i).getElemType();

        switch (type){
        case PROPERTY: {
            Property& temp_prop = dynamic_cast<Property&>(target_obj.getElement(i));
            printProperty(outputstr, temp_prop, level+1);
            break;
        }
        case OBJECT: {
            Object& temp_obj = dynamic_cast<Object&>(target_obj.getElement(i));
            printObject(outputstr, temp_obj, level+1);
            break;
        }
        case ARRAY: {
            Object& temp_arr = dynamic_cast<Object&>(target_obj.getElement(i));
            printArray(outputstr, temp_arr, level+1);
            break;
        }
        }
    }

    for (int i = 0; i < level; i++)
        outputstr << TAB;
    outputstr << "</" << target_obj.getKey() << ">" << endl;
}

void printArray(ofstream& outputstr, Object& target_arr, int level){
    ElementType type;
    for (int i = 0; i < target_arr.getCount(); i++){
        type = target_arr.getElement(i).getElemType();

        switch (type){
        case PROPERTY: {
            Property& temp_prop = dynamic_cast<Property&>(target_arr.getElement(i));
            temp_prop.setKey(target_arr.getKey());
            printProperty(outputstr, temp_prop, level);
            temp_prop.setKey("");
            break;
        }
        case OBJECT: {
            Object& temp_obj = dynamic_cast<Object&>(target_arr.getElement(i));
            temp_obj.setKey(target_arr.getKey());
            printObject(outputstr, temp_obj, level);
            temp_obj.setKey("");
            break;
        }
        case ARRAY:
            Object& temp_arr = dynamic_cast<Object&>(target_arr.getElement(i));
            temp_arr.setKey(target_arr.getKey());
            printArray(outputstr, temp_arr, level);
            break;
        }

    }
}

void saveXML(ofstream& outputstr, Object& target_doc){
    Object& main_obj = dynamic_cast<Object&>(target_doc.getElement(0));
    printObject(outputstr, main_obj, 0);
}
