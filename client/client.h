
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <stack>

using std::string;
using std::stack;

class Client {
    public:
        Client(string dwIP); // default constructor
        void SendMessage(string dwHost);
        void ProcessIncomingMessages();
        void AddMessage(string dwMessage);
        void RecieveMessage(string dwMesage);

    private:
        string m_dwIP;
        string m_dwMACAddress;
        stack<string> m_stdwIncomingMessages;
};

#endif