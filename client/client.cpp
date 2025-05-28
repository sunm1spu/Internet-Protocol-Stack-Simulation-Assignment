#include "client.h"
#include <iostream>
#include <string>

#include "../layers/application.h"
#include "../layers/link.h"

using std::cout;
using std::endl;
using std::string;

Client::Client(string dwIP) : m_dwIP(dwIP) { 
    // randomly generate MACAccress
    m_dwMACAddress = "1A:2B:3C:D4:E5:F6";
};

void Client::SendRequest(string dwHost) {
    string dwRequest = "GET / HTTP/1.1\r\n";
}

void Client::ProcessIncomingMessages() {

    // go through all of our incoming messages
    while (!m_stdwIncomingMessages.empty()) {

        // get the topmost message
        string dwMessage = m_stdwIncomingMessages.top();
        m_stdwIncomingMessages.pop();

        // process this message
        RecieveMessage(dwMessage);
    }
}

void Client::AddMessage(string dwMesage) {

    // accept the incoming message, push it onto our TODO stack
    m_stdwIncomingMessages.push(dwMesage);
}

void Client::RecieveMessage(string dwMesage) {

    // print some headers for our output, make sure to include IP so we know who is doing what
    cout << "[Client /w IP: " << m_dwIP << "] ============ Receiving ============" << endl;
    cout << "[Link Layer] Receiving: " << dwMesage << endl << endl;

    // create link layer and decapsulate our message
    Link* pLink = new Link(); 
    string dwLinkRemoved = pLink->Decapsulate(dwMesage);

    cout << "[Network Layer] Receiving: " << dwLinkRemoved << endl << endl;
}