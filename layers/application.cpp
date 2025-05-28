#include <iostream>
#include <string>
#include "application.h"

using std::string;
using std::endl;
using std::cout;

ApplicationLayer::ApplicationLayer() {}

ApplicationLayer::ApplicationLayer(map<string, string> fieldsInput) {

    fieldsInput.merge(fields);
    fields = fieldsInput;
}

ApplicationLayer::ApplicationLayer(int method) {
    ApplicationLayer::method = returnMethod(method);
}

/*
    This function simulates the application layer
    encapsulation for an HTTP request.
*/
string ApplicationLayer::encapsulate() {
    /*
        Header structure

            Request line: method SP URL SP Version CR LF
            Header lines: header-field-name SP value CR LF 
            CR LF
            Entity Body
    
    */
    string encapsulatedMessage = fields["Method"] + " " + fields["URL"] + " " + fields["Version"] + "\r\n";


    for (const auto& [key, value] : fields) {
        if (key != "Method" && key != "URL"  && key != "Version" && key != "Body" ) {
            encapsulatedMessage += key + ": ";
            encapsulatedMessage += value + "\r\n";
        }
    }
    encapsulatedMessage += "\r\n" + fields["Body"];

    return encapsulatedMessage;
}

string ApplicationLayer::decapsulate(string message) {
    return "";
}

void ApplicationLayer::removeField(string fieldName) {
    fields.erase(fieldName);
}

// void ApplicationLayer::setHeaderField(string fieldName, string fieldValue)  {
//     fields.insert(fieldName, fieldValue);
// }

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
