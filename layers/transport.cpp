using namespace std;
#include <string>
#include "transport.h"
#include <vector>
#include <stdint.h>


TransportLayer::TransportLayer() {
    m_dwTCPVersion = "Transmission Control Protocol";
    m_dwSourcePort = "63784";
    m_dwDestinationPort = "00080";
    m_dwSequence = "1";
    m_dwAcknowledge = "1";
    m_dwLength = "76";

    sourcePort = m_dwSourcePort;
    destPort = m_dwDestinationPort;
}

string TransportLayer::Encapsulate(string message) {
    return message + m_dwTCPVersion + ", " +
    "Src Port: " + m_dwSourcePort + ", " + "Dst Port: " + m_dwDestinationPort + ", " + 
    "Seq: " + m_dwSequence + ", " + "Ack: " + m_dwAcknowledge + ", " + "Len: " + m_dwLength;
}



vector<string> TransportLayer::encapsulate(string message) {
    string transportHeader = sourcePort + destPort; 
    return sendSegments(message, transportHeader);
}

vector<string> TransportLayer::sendSegments(string message, string transportHeader) {
    int messageLength = message.length();
    vector<string> segmentArray; 

    /*
        Create segments of equal to or less than MSS 
    */
    int totalSegments = messageLength / MSS;
    if (messageLength % MSS != 0) {
        totalSegments++;
    }

    int i = 0;
    for (; i + MSS < messageLength; i += MSS) {  

        int sequenceNumber = i / MSS;
            
        cout<< i << "i " << endl << endl;
        segmentArray.push_back(transportHeader + to_string(sequenceNumber) + message.substr(i, MSS));

    }

    if (i < messageLength) {
        segmentArray.push_back(transportHeader + to_string(totalSegments) + message.substr(i));
    }

    return segmentArray;
}

string TransportLayer::Decapsulate(string message) {
    return "";
}