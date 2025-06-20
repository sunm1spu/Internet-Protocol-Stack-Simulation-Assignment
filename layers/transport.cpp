using namespace std;
#include <string>
#include "transport.h"
#include <vector>
#include <stdint.h>

#include "../util.cpp";

TransportLayer::TransportLayer() {
    m_dwTCPVersion = "Transmission Control Protocol";
    m_dwSourcePort = "63784";
    m_dwDestinationPort = "00080";
    m_dwSequence = "1";
    m_dwAcknowledge = "1";
    m_dwLength = "76";

    sourcePort = std::stoi(m_dwSourcePort);
    destPort = std::stoi(m_dwDestinationPort);
}

string TransportLayer::Encapsulate(string message) {
    return message + m_dwTCPVersion + ", " +
    "Src Port: " + m_dwSourcePort + ", " + "Dst Port: " + m_dwDestinationPort + ", " + 
    "Seq: " + m_dwSequence + ", " + "Ack: " + m_dwAcknowledge + ", " + "Len: " + m_dwLength;
}

vector<string> TransportLayer::encapsulate(string message) {
    uint16_t sourcePortBits = sourcePort;
    uint16_t destPortBits = destPort;
    
    string transportHeader =  convertBitToString(sourcePortBits, 5)+ convertBitToString(destPortBits, 5); 
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
        uint32_t sequenceNumberBit = sequenceNumber;
        segmentArray.push_back(transportHeader + convertBitToString(sequenceNumberBit, 10) + message.substr(i, MSS));

    }

    if (i < messageLength) {
        string sequenceNumber = convertBitToString(totalSegments - 1, 10);
        segmentArray.push_back(transportHeader + sequenceNumber + message.substr(i));
    }

    return segmentArray;
}

/*
    This function removes the transport layer header and 
    assembles the segments into a complete message.
*/
string TransportLayer::decapsulate(vector<string> segments) {
    cout << "Reassembling TCP Segments" << endl;

    const int headerSize = 20;
    int segmentArraySize = segments.size();
    
    string segmentArray[segmentArraySize];
    string message = "";

    /*
        Remove transport layer header and place segment in appropriate place given 
        sequence number.
    */
    for (int i = 0; i < segments.size(); i++) {
        string segment = segments[i];
        int sequence = std::stoi(segment.substr(10, 10));

        segment = segment.substr(20);
        segmentArray[sequence] = segment;
    }

    for (int i = 0; i < sizeof(segmentArray) / sizeof(segmentArray[0]); i++) {

        
        cout <<  FitInTable("Assembling TCP fragments ["+std::to_string(i)+"/"+std::to_string(segmentArraySize-1)+"]", message) << endl << endl;
        //cout << i << " putting back together: \n" << message << endl << endl;
        message += segmentArray[i];
    }

    return message; 
}

string TransportLayer::convertBitToString(uint32_t number, int dig) {
    char buffer[11]; 
    std::snprintf(buffer, sizeof(buffer), "%0*u", dig, number);
    return std::string(buffer);
}