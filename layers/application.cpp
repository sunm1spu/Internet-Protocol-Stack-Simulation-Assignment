#include <iostream>
#include <string>
#include "application.h"

using std::string;

ApplicationLayer::ApplicationLayer() {
    
}

ApplicationLayer::ApplicationLayer(int method) {
    ApplicationLayer::method = returnMethod(method);
}

/*
    URL, CLIENT, METHOD
*/


/*
    This function simulates the application layer
    encapsulation for an HTTP request.
*/
string ApplicationLayer::encapsulate() {
    string encapsulatedMessage = method;
    map<string, string>::iterator iterator;

    encapsulatedMessage += iterator->first;
    encapsulatedMessage+= " " + iterator->second;
    iterator++;

    for (; iterator != fields.end(); iterator++) {
        encapsulatedMessage += "\n" + iterator->first;
        encapsulatedMessage += " " + iterator->second;
    }
    return encapsulatedMessage;
}

string ApplicationLayer::decapsulate(string message) {
    return "";
}

void ApplicationLayer::removeField(string fieldName) {
    fields.erase(fieldName);
}

void ApplicationLayer::setHeaderField(string fieldName, string fieldValue)  {
    fields.insert(fieldName, fieldValue);
}

/* 
    This helper function encapsulates a switch case to return
    the string value of an HTTP method corresponding to a 
    particular int. This just keeps encapsulate less cluttered.
*/
std::string ApplicationLayer::returnMethod(int method) {
   switch(method) {
        case 0:
            return "GET";
            break;
        case 1:
            return "POST";
            break;
        case 2:
            return "HEAD";
            break;
        case 3:
            return "PUT";
            break;
        case 4:
            return "DELETE";
            break;
        default:
            return "";
            break;
   }
}
