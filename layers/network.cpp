using namespace std;
#include <string>
#include "network.h"
#include <vector>


NetworkLayer::NetworkLayer(string ipVersion, string sourceIP, string destinationIP) {
    dwIPVersion = ipVersion;
    dwSourceIP = sourceIP;
    dwDestinationIP = destinationIP;
}

string NetworkLayer::Encapsulate(string message) {
    return dwIPVersion +
    dwSourceIP +
    dwDestinationIP + message;
}

vector<string> NetworkLayer::Decapsulate(vector<string> messages) {
    vector<string> segments = {};
    for (string message : messages) {
        segments.push_back(DecapsulateSegment(message));
    }
    return segments;
}

string NetworkLayer::DecapsulateSegment(string message) {
    // 2 + 2 * 15 = 32
    return message.substr(32);
}