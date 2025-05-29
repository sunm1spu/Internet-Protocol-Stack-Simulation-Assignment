using namespace std;
#include <string>
#include "link.h"
#include <vector>

LinkLayer::LinkLayer(string source, string destination, string type) {
    m_dwSource = source;
    m_dwDestination = destination;
    m_dwType = type;
}

string LinkLayer::Encapsulate(string message) {
    return m_dwSource + m_dwDestination + m_dwType + message;
}

vector<string> LinkLayer::Decapsulate(vector<string> messages) {
    vector<string> segments = {};
    for (string message : messages) {
        segments.push_back(DecapsulateSegment(message));
    }
    return segments;
}

string LinkLayer::DecapsulateSegment(string message) {
    // 17 * 2 + 4 = 38
    return message.substr(38);
}

