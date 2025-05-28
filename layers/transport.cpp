using namespace std;
#include <string>
#include "transport.h"


TransportLayer::TransportLayer() {
    m_dwTCPVersion = "Transmission Control Protocol";
    m_dwSourcePort = "63784";
    m_dwDestinationPort = "80";
    m_dwSequence = "1";
    m_dwAcknowledge = "1";
    m_dwLength = "76";
}

string TransportLayer::Encapsulate(string message) {
    return message +  + ", " +
    "Src Port: " + m_dwSourcePort + ", " + "Dst Port: " + m_dwDestinationPort + ", " + 
    "Seq: " + m_dwSequence + ", " + "Ack: " + m_dwAcknowledge + ", " + "Len: " + m_dwLength;
}

string TransportLayer::Decapsulate(string message) {
    return "";
}