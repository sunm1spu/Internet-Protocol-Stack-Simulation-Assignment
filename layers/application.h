
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::map;

class application_layer{    
    public:
        string send(string messageBody, map<string, string> headerData);
        string receive(string message);

        string encapsulate(string body, int method);
        string decapsulate(string message);
        void setHeaderField(string fieldName, string fieldValue);
        void removeField(string fieldName);
    
    private:
        string returnMethod(int method);
        string parseMessage(string message);

        map<string, string>defaultFields = {
            {"Host:", ""},
            {"Acccept:", ""},
            {"Connection:", "close"},
            {"User-agent:", ""},
            {"Accept-language", "en"}
        };
        
};
