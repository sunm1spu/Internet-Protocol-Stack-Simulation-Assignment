#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::map;

class ApplicationLayer{    
    public:
        ApplicationLayer(int method);

        string send();
        string receive(string message);

        string encapsulate();
        string decapsulate(string message);
        void setHeaderField(string fieldName, string fieldValue);
        void removeField(string fieldName);
    
    private:
        string returnMethod(int method);
        string parseMessage(string message);

        string method = "";
        map<string, string>fields = {
            {"Host:", ""},
            {"Acccept:", ""},
            {"Connection:", "close"},
            {"User-agent:", ""},
            {"Accept-language", "en"}
        };
        
};
