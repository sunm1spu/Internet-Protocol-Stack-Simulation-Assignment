#include "client.h"
#include <iostream>
#include <string>

#include "../layers/application.cpp"
#include "../layers/transport.cpp"
#include "../layers/network.cpp"
#include "../layers/link.cpp"

using std::cout;
using std::endl;
using std::string;

Client::Client(string dwIP) : m_dwIP(dwIP) { 
    // randomly generate MACAddress
    m_dwMACAddress = "1A:2B:3C:D4:E5:F6";
};

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

void Client::SendMessage(string dwHost) {
    map<string, string> fieldMap = {
        {"Method", "GET"},
        {"URL", "https://www.innersloth.com/games/among-us/"},
        {"Version", "HTTP/1.1"},
        {"Accept", "text/html"},
        {"Body", "Among Us is a 2018 online multiplayer social deduction game developed and published by American game studio Innersloth. The game allows for cross-platform play; it was released on iOS and Android devices in June 2018 and on Windows later that year in November. It was ported to the Nintendo Switch in December 2020 and on the PlayStation 4, PlayStation 5, Xbox One and Xbox Series X/S in December 2021. A virtual reality adaptation, Among Us VR, was released on November 10, 2022."},
    };

    string dwMessage = "GET / HTTP/1.1\r\n";

    cout << "[Client /w IP: " << m_dwIP << "] ============ Sending ============" << endl;

    // create application layer and encapsulate the first layer of the message, we are emulating sending a simple GET request.
    cout << "[Application Layer] Sending: " << dwMessage << endl << endl;
    ApplicationLayer* pApplication = new ApplicationLayer(fieldMap);
    string dwTransport = pApplication->encapsulate(); // capitalize this decapsulate
    
    // create transport layer and encapsulate our message
    cout << "\n[Transport Layer] Sending: \n" << dwTransport << endl << endl;
    TransportLayer* pTransport = new TransportLayer();
    string dwNetwork = pTransport->Encapsulate(dwTransport);

    vector<string> networkTest = pTransport->encapsulate(dwTransport);
    cout << "Segments: \n" << endl;
    
    // create transport and network layers and encapsulate our message
    cout << "\n[Network Layer] Sending Segments \n";
    for (int i = 0; i < networkTest.size(); i++) {
        NetworkLayer* pNetwork = new NetworkLayer("04", m_dwIP, dwHost);
        string dwNetwork = pNetwork->Encapsulate(networkTest[i]);
        LinkLayer* pLink = new LinkLayer("7c:21:4a:3c:0b:f9", m_dwMACAddress, "0800");
        string dwLink = pLink->Encapsulate(dwNetwork);
        cout << dwLink << endl;
    }

    //string humptyDumpty = pTransport->decapsulate(networkTest);
    
    // // create network layer and encapsulate our message
    // cout << "[Network Layer] Sending: " << dwNetwork << endl << endl;
    // NetworkLayer* pNetwork = new NetworkLayer();
    // string dwLink = pNetwork->Encapsulate(dwNetwork); 

    // // create link layer and encapsulate our message
    // cout << "[Link Layer] Sending: " << dwLink << endl << endl;
    // LinkLayer* pLink = new LinkLayer(); 
    // string dwFinal = pLink->Encapsulate(dwLink);

    // cout << "Final message: " << dwFinal;
}

void Client::RecieveMessage(string dwMesage) {

    // // print some headers for our output, make sure to include IP so we know who is doing what
    // cout << "[Client /w IP: " << m_dwIP << "] ============ Receiving ============" << endl;

    // // create link layer and decapsulate our message
    // cout << "[Link Layer] Receiving: " << dwMesage << endl << endl;
    // LinkLayer* pLink = new LinkLayer(); 
    // string dwNetwork = pLink->Decapsulate(dwMesage);

    // // create network layer and decapsulate our remaining message
    // cout << "[Network Layer] Receiving: " << dwNetwork << endl << endl;
    // NetworkLayer* pNetwork = new NetworkLayer();
    // string dwTransport = pNetwork->Decapsulate(dwNetwork); 

    // // create transport layer and decapsulate our remaining message
    // cout << "[Transport Layer] Receiving: " << dwTransport << endl << endl;
    // TransportLayer* pTransport = new TransportLayer();
    // string dwApplication = pTransport->Decapsulate(dwTransport);

    // // create application layer and decapsulate the final layer of the message
    // cout << "[Application Layer] Receiving: " << dwApplication << endl << endl;
    // ApplicationLayer* pApplication = new ApplicationLayer();
    // string dwMessage = pApplication->decapsulate(dwApplication); // capitalize this decapsulate

    // cout << "Final message received: " << dwMesage;
}