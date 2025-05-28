using namespace std;
#include <string>
#include "network.h"


NetworkLayer::NetworkLayer() {
    dwIPVersion = "Internet Protocol Version 4";
    dwSourceIP = "10.1.2.345";
    dwDestinationIP = "45.678.910.11";
}

string NetworkLayer::Encapsulate(string message) {
    return message + dwIPVersion + ", " +
    "Src: " + dwSourceIP + ", " +
    "Dst: " + dwDestinationIP;
}

string NetworkLayer::Decapsulate(string message) {
    return "";
}