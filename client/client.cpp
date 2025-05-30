#include "client.h"
#include <iostream>
#include <string>
#include <fstream>

#include "../layers/application.cpp"
#include "../layers/transport.cpp"
#include "../layers/network.cpp"
#include "../layers/link.cpp"
#include "../util.cpp";

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

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
        //RecieveMessage(dwMessage);
    }
}

void Client::AddMessage(string dwMesage) {

    // accept the incoming message, push it onto our TODO stack
    m_stdwIncomingMessages.push(dwMesage);
}

void Client::SendMessage(Client* pOther, string body) {
    map<string, string> fieldMap = {
        {"Method", "POST"},
        {"URL", "https://www.innersloth.com/games/among-us/"},
        {"Version", "HTTP/1.1"},
        {"Accept", "text/html"},
        {"Accept-Charset", "utf-8"},
        {"User-agent", "Win64"},
        {"Host", "www.innersloth.com"},
        {"Body", FormatNL(body)},
    };

    cout << "\n[Client /w IP: " << m_dwIP << "] ============ Sending ============" << endl;

    // create application layer and encapsulate the first layer of the message, we are emulating sending a simple GET request.
    cout << "\n[Application Layer] Sending: \n" << FitInTable("Message Body", body) << endl << endl;
    ApplicationLayer* pApplication = new ApplicationLayer(fieldMap);
    string dwTransport = FormatNL(pApplication->encapsulate()); // capitalize this decapsulate

    // create transport layer and encapsulate our message
    cout << "\n[Transport Layer] Sending: \n" << FitInTable("Pre TCP Segmentation Data", dwTransport) << endl << endl;
    TransportLayer* pTransport = new TransportLayer();
    string dwNetwork = pTransport->Encapsulate(dwTransport);

    vector<string> networkSegments = pTransport->encapsulate(dwTransport);
    cout << "Generated TCP Segments:" << endl;
    
    cout << GenerateHeaders(2);
    for (int i = 0; i < networkSegments.size(); i++) {
        cout << GenerateRow(networkSegments[i], 2) << endl;
    }
    cout << GenerateFooters(2) << endl << endl;

    // create network layer and encapsulate our message
    cout << "\n[Network Layer] Sending Segments \n";
    vector<string> linkSegments;
    NetworkLayer* pNetwork = new NetworkLayer("04", m_dwIP, pOther->m_dwIP);

    
    cout << GenerateHeaders(1);
    for (int i = 0; i < networkSegments.size(); i++) {
        string dwNetwork = pNetwork->Encapsulate(networkSegments[i]);
        cout << GenerateRow(dwNetwork, 1) << endl;
        linkSegments.push_back(dwNetwork);
    }
    cout << GenerateFooters(1) << endl << endl;

    // create link layer and encapsulate our message
    cout << "\n[Link Layer] Sending Segments \n";
    vector<string> finalSegments;
    LinkLayer* pLink = new LinkLayer("7c:21:4a:3c:0b:f9", m_dwMACAddress, "0800");

    cout << GenerateHeaders(0);
    for (int i = 0; i < linkSegments.size(); i++) {
        string dwLink = pLink->Encapsulate(linkSegments[i]);
        cout << GenerateRow(dwLink, 0) << endl;
        finalSegments.push_back(dwLink);
    }
    cout << GenerateFooters(0);

    cout << "\nencapsulation finished" << endl;
    pOther->RecieveMessage(finalSegments);
}

void Client::RecieveMessage(vector<string> vdwSegments) {
    cout << "[Client /w IP: " << m_dwIP << "] ============ Receiving ============" << endl;

    cout << "\n[Link Layer] Receiving:" << endl;

    cout << GenerateHeaders(0);
    for (int i = 0; i < vdwSegments.size(); ++i) {
        cout << GenerateRow(vdwSegments[i], 0) << endl;
    }
    cout << GenerateFooters(0) << endl << endl;

    // print out link layer decapsulization 
    
    LinkLayer* pLink = new LinkLayer("7c:21:4a:3c:0b:f9", m_dwMACAddress, "0800");
    vector<string> linkSegmentsDecap = pLink->Decapsulate(vdwSegments);
    cout << "\n[Newtork Layer] Receiving:" << endl;
    
    cout << GenerateHeaders(1);
    for (int i = 0; i < linkSegmentsDecap.size(); ++i) {
        cout << GenerateRow(linkSegmentsDecap[i], 1) << endl;
    }
    cout << GenerateFooters(1) << endl << endl;

    NetworkLayer* pNetwork = new NetworkLayer("04", "", "");
    vector<string> networkSegmentsDecap = pNetwork->Decapsulate(linkSegmentsDecap);
    cout << "\n[Transport Layer] Receiving:" << endl;
    
    cout << GenerateHeaders(2);
    for (int i = 0; i < networkSegmentsDecap.size(); ++i) {
        cout << GenerateRow(networkSegmentsDecap[i], 2) << endl;
    }
    cout << GenerateFooters(2) << endl << endl;

    TransportLayer* pTransport = new TransportLayer();
    string decapTransMessage = ReNL(pTransport->decapsulate(networkSegmentsDecap));
    

    
    cout << "\n[Application Layer] Receiving: \n" << FitInTable("Application Layer Data", decapTransMessage) << endl << endl << endl;
    ApplicationLayer* pApplication = new ApplicationLayer();
    string decapAppMessage = pApplication->decapsulate(decapTransMessage);

    cout << "Final message: \n" << FitInTable("Final Data", decapAppMessage) << endl << endl;
}