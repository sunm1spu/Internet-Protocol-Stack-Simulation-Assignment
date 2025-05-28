
#ifndef TRANSPORT_H
#define TRANSPORT_H

class TransportLayer {
    public:
        TransportLayer();
        string Encapsulate(string message);
        string Decapsulate(string message);

    private:
        string m_dwTCPVersion;
        string m_dwSourcePort;
        string m_dwDestinationPort;
        string m_dwSequence;
        string m_dwAcknowledge;
        string m_dwLength;
};

#endif
