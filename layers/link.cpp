using namespace std;
#include <string>
#include "link.h"

LinkLayer::LinkLayer() {
    m_dwEthernetVersion = "Ethernet II";
    m_dwSource = "7c:21:4a:3c:0b:f9";
    m_dwDestination = "1c:93:7c:61:60:68";
}

string LinkLayer::Encapsulate(string message) {
    return message + m_dwEthernetVersion + ", " + 
    "Src: " + m_dwSource + ", " + 
    "Dst: " + m_dwDestination;
}

string LinkLayer::Decapsulate(string message) {
    return "";
}