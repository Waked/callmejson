#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/Element.hpp"
#include "../include/Object.hpp"
#include "../include/Property.hpp"
#include "../include/json_in.h"

using namespace std;

/// ------------------------ ONCE FUCKING AGAIN --------------------------

Object* readSquares(ifstream& inputstr){

}

/// DONE
Object* readBracket(ifstream& inputstr){
    Object* returnobj = new Object;
    Element* pushelem;
    stringbuf tempstr;
    char tempchar;

    inputstr >> tempchar;
    if (tempchar != '{'){
        cout << "Trying to read nonbracket!" << endl;
        return nullptr;
    }

    inputstr >> tempchar;
    while (tempchar != '}'){
        inputstr.get(tempstr, '"');
        inputstr >> tempchar; ///kropka
        inputstr >> tempchar;

        switch (tempchar){
        case '"':
            pushelem = new Property;
            pushelem->setKey(tempstr.str());
            inputstr.get(tempstr, '"');
            pushelem->setValue(tempstr.str());
            break;
        case '{':
            inputstr.putback(tempchar);
            pushelem = readBracket(inputstr);
            pushelem.setKey(tempstr.str());
            break;
        case '[':
            inputstr.putback(tempchar);
            pushelem = readSquares(inputstr);
            pushelem.setKey("");
            break;
        }
        inputstr >> tempchar;
        if (tempchar == ',')    /// przecinek
            inputstr >> tempchar;
    }

    return returnobj;
}
