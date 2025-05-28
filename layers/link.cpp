using namespace std;
#include <string>
#include "link.h"
#include <vector>

LinkLayer::LinkLayer() {
    m_dwEthernetVersion = "0800"; // Ethernet II
    m_dwSource = "7c:21:4a:3c:0b:f9";
    m_dwDestination = "1c:93:7c:61:60:68";
}

string LinkLayer::Encapsulate(string message) {
    return message + m_dwEthernetVersion + ", " + 
    "Src: " + m_dwSource + ", " + 
    "Dst: " + m_dwDestination;
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
    return message.substr(0, message.length() - 50);
}

