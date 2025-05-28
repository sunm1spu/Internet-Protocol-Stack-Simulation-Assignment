
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
using std::string;

class Client {
    public:
        Client(); // default constructor
        void SendRequest(string host, string method, string body);
        void ProcessRequests();
        void RecieveRequest();

    private:
        string m_dwIP;
        string m_dwMACAddress;
};

#endif