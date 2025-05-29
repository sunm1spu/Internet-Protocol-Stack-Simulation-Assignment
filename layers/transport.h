
#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <vector>
#include <stdint.h>

class TransportLayer {
    public:
        TransportLayer();
        string Encapsulate(string message);
        string Decapsulate(string message);

        vector<string> encapsulate(string message);
        string decapsulate(vector<string> segments);

        vector<string> sendSegments(string message, string header);

    private:
        string m_dwTCPVersion;
        string m_dwSourcePort;
        string m_dwDestinationPort;
        string m_dwSequence;
        string m_dwAcknowledge;
        string m_dwLength;

        /*
            Default Max Segment Size in characters
        */
        int MSS = 20;
        int sourcePort;
        int destPort;
        int sequence;

        /*
            32 bits is 10, 16 bits is 5
        */
        string convertBitToString(uint32_t number, int digits);
};

#endif
