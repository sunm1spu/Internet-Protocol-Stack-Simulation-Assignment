
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <stack>
#include <vector>

using std::string;
using std::vector;
using std::stack;

class Client {
    public:
        Client(string dwIP); // default constructor
        void SendMessage(Client* pOther);
        void ProcessIncomingMessages();
        void AddMessage(string dwMessage);
        void RecieveMessage(vector<string> vdwSegments);
        
        void wipeOutputFile();
        void writeToFile(string message);

    private:
        string m_dwIP;
        string m_dwMACAddress;
        stack<string> m_stdwIncomingMessages;
        const string outputFileName = "sample_output.txt";
        void GenerateRow(string message, int fcount);
};

#endif