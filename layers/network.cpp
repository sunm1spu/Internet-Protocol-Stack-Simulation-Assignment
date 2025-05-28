using namespace std;
#include <string>

string generateHeader() {
    string dwIPVersion = "Internet Protocol Version 4";
    string dwSourceIP = "10.1.2.345";
    string dwDestinationIP = "45.678.910.11";
    return dwIPVersion + ", " + "Src: " + dwSourceIP + ", " + "Dst: " + dwDestinationIP;
}