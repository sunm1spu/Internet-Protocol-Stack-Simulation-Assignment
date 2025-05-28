
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <stack>

using std::string;
using std::stack;

class Client {
    public:
        Client(string dwIP); // default constructor
        void SendRequest(string dwHost);
        void ProcessIncomingRequests();
        void RecieveRequest();

    private:
        string m_dwIP;
        string m_dwMACAddress;
        stack<
};

#endif