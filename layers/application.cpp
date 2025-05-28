#include <iostream>
#include <string>
#include "application.h"

using std::string;

string application_layer::send(string messageBody, map<string, string> headerData) {
   
}

string parseMessage(string ) {

}

/*
    This function simulates the application layer
    encapsulation for an HTTP request.
*/
string application_layer::encapsulate(string body, int method) {
    string methodString = returnMethod(method);
    
    return "";
}

string application_layer::decapsulate(string message) {
    return "";
}

void application_layer::removeField(string fieldName) {
    defaultFields.erase(fieldName);
}

/* 
    This helper function encapsulates a switch case to return
    the string value of an HTTP method corresponding to a 
    particular int. This just keeps encapsulate less cluttered.
*/
std::string application_layer::returnMethod(int method) {
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
            break;
   }
}
