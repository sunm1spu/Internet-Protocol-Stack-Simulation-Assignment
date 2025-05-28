
#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <vector>

class TransportLayer {
    public:
        TransportLayer();
        string Encapsulate(string message);
        string Decapsulate(string message);

        vector<string> encapsulate(string message);

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
        int MSS = 10;
        string sourcePort;
        string destPort;
        int sequence;
};

#endif
