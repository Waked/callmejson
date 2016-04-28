#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_in.h"

using namespace std;

/// ------------------------ ONCE FUCKING AGAIN --------------------------

string readCustom(ifstream& inputstr, string delim){
    int delim_count = delim.length();
    string returnstr;
    bool delim_reached = false;
    char it = 0;
    while (!delim_reached){
        inputstr >> it;
        for (int i = 0; i < delim_count; i++)
            if (it == delim.at(i))
                delim_reached = true;
        if (!delim_reached)
            returnstr.push_back(it);
    }
    inputstr.putback(it);
    return returnstr;
}

///
Object* readBracket(ifstream& inputstr){
    Object* returnobj = new Object(OBJECT);
    Element* pushelem;
    char tempchar;

    inputstr >> tempchar;
    if (tempchar != '{'){
        cout << "Trying to read nonbracket!" << endl;
        return nullptr;
    }

    inputstr >> tempchar;

    while (tempchar != '}' && tempchar != 0){

        string tempstr;

        getline (inputstr, tempstr, '"');
        inputstr >> tempchar; ///kropka
        inputstr >> tempchar;

        switch (tempchar){
        case '"': {
            Property* pushelem_cast = new Property;
            pushelem_cast->setKey(tempstr);
            getline(inputstr, tempstr, '"');
            pushelem_cast->setValue(tempstr);
            pushelem = pushelem_cast;
            break;
        }
        case '{':
            inputstr.putback(tempchar);
            pushelem = readBracket(inputstr);
            pushelem->setKey(tempstr);
            break;
        case '[':
            inputstr.putback(tempchar);
            pushelem = readSquares(inputstr);
            pushelem->setKey(tempstr);
            break;
        default:
            inputstr.putback(tempchar);
            Property* pushelem_cast = new Property;
            pushelem_cast->setKey(tempstr);
            pushelem_cast->setValue(readCustom(inputstr, ",}"));
            pushelem = pushelem_cast;
            break;
        }

        returnobj->addElement(pushelem);

        inputstr >> tempchar;
        if (tempchar == ',')    /// przecinek
            inputstr >> tempchar;
    }

    return returnobj;
}

/// DONE
Object* readSquares(ifstream& inputstr){
    Object* returnobj = new Object(ARRAY);
    Element* pushelem;
    char tempchar;
    string tempstr;

    inputstr >> tempchar;
    if (tempchar != '['){
        cout << "Trying to read nonsquare!" << endl;
        return nullptr;
    }

    inputstr >> tempchar;

    while (tempchar != ']'){
        switch (tempchar){
        case '"': {
            Property* pushelem_cast = new Property;
            pushelem_cast->setKey("");
            getline(inputstr, tempstr, '"');
            pushelem_cast->setValue(tempstr);
            pushelem = pushelem_cast;
            break;
        }
        case '{':
            inputstr.putback(tempchar);
            pushelem = readBracket(inputstr);
            pushelem->setKey("");
            break;
        case '[':
            inputstr.putback(tempchar);
            pushelem = readSquares(inputstr);
            pushelem->setKey("");
            break;
        }

        returnobj->addElement(pushelem);

        inputstr >> tempchar;
        if (tempchar == ',')    /// przecinek
            inputstr >> tempchar;
    }

    return returnobj;
}

Object* readJSON(ifstream& inputstr){
    Object* returnobj;
    inputstr.seekg(0, inputstr.beg);
    returnobj = readBracket(inputstr);
    returnobj->setKey("document");
    return returnobj;
}
