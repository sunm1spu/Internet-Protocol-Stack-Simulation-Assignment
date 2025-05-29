using namespace std;
#include <string>
#include "link.h"
#include <vector>

LinkLayer::LinkLayer(string source, string destination, string type) {
    m_dwSource = source;
    m_dwDestination = destination;
    m_dwType = type;
    
    //m_dwSource = "7c:21:4a:3c:0b:f9";
    //m_dwDestination = "1c:93:7c:61:60:68";
    //m_dwEthernetVersion = "0800";
}

string LinkLayer::Encapsulate(string message) {
    return "Src: " + m_dwSource + ", " + 
    "Dst: " + m_dwDestination + ", " + m_dwType + message;
}

vector<string> LinkLayer::Decapsulate(vector<string> messages) {
    vector<string> segments = {};
    for (string message : messages) {
        segments.push_back(DecapsulateSegment(message));
    }
    return segments;
}

string LinkLayer::DecapsulateSegment(string message) {
    // 4 + 17 * 2 = 38, 38 + 12 = 50
    return message.substr(50);
}

