
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
using std::string;

class Client {
    public:
        Client(string dwIP); // default constructor
        void SendRequest(string dwHost);
        void ProcessRequests();
        void RecieveRequest();

    private:
        string m_dwIP;
        string m_dwMACAddress;
};

#endif