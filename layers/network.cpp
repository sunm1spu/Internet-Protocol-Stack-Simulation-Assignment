using namespace std;
#include <string>
#include "network.h"
#include <vector>


NetworkLayer::NetworkLayer(string ipVersion, string sourceIP, string destinationIP) {
    dwIPVersion = ipVersion;
    dwSourceIP = sourceIP;
    dwDestinationIP = destinationIP;
    
    //dwIPVersion = "04"; // IPV4
    //dwSourceIP = "010.001.002.345";
    //dwDestinationIP = "045.678.910.011";
}

string NetworkLayer::Encapsulate(string message) {
    return message + dwIPVersion + ", " +
    "Src: " + dwSourceIP + ", " +
    "Dst: " + dwDestinationIP;
}

vector<string> NetworkLayer::Decapsulate(vector<string> messages) {
    vector<string> segments = {};
    for (string message : messages) {
        segments.push_back(DecapsulateSegment(message));
    }
    return segments;
}

string NetworkLayer::DecapsulateSegment(string message) {
    // 2 + 2 * 15 = 32, 32 + 12 = 44
    return message.substr(0, message.length() - 44);
}