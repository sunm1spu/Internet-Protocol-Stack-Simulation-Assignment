#include "client.h"
#include <iostream>
#include <string>
#include <fstream>

#include "../layers/application.cpp"
#include "../layers/transport.cpp"
#include "../layers/network.cpp"
#include "../layers/link.cpp"

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
        RecieveMessage(dwMessage);
    }
}

void Client::AddMessage(string dwMesage) {

    // accept the incoming message, push it onto our TODO stack
    m_stdwIncomingMessages.push(dwMesage);
}

void Client::wipeOutputFile() {
    ofstream file(outputFileName, std::ios::trunc);
}

void Client::writeToFile(string output) {
    ofstream outputFile;
    outputFile.open(outputFileName, std::ios::app);
    

    if (!outputFile.is_open()) {
        std::cerr << "Can't open output file!" << endl;
        return;
    }

    outputFile << output << endl;
    outputFile.close();
}

void Client::SendMessage(string dwHost) {
    map<string, string> fieldMap = {
        {"Method", "POST"},
        {"URL", "https://www.innersloth.com/games/among-us/"},
        {"Version", "HTTP/1.1"},
        {"Accept", "text/html"},
        {"Accept-Charset", "utf-8"},
        {"User-agent", "Win64"},
        {"Host", "www.innersloth.com"},
        {"Body", "Domestic cats are found across the globe, though their popularity as pets varies by region. Out of the estimated 600 million cats worldwide, 400 million reside in Asia, including 58 million pet cats in China. The United States leads in cat ownership with 73.8 million cats. In the United Kingdom, approximately 10.9 million domestic cats are kept as pets."},
    };
    wipeOutputFile();

    string dwMessage = "GET / HTTP/1.1\r\n";

    cout << "[Client /w IP: " << m_dwIP << "] ============ Sending ============" << endl;

    // create application layer and encapsulate the first layer of the message, we are emulating sending a simple GET request.
    cout << "[Application Layer] Sending: " << dwMessage << endl << endl;
    ApplicationLayer* pApplication = new ApplicationLayer(fieldMap);
    string dwTransport = pApplication->encapsulate(); // capitalize this decapsulate
    
    writeToFile("[Client /w IP: " + m_dwIP + "] ============ Sending ============\n[Application Layer] Sending: " + dwMessage);
    writeToFile(dwTransport);

    // create transport layer and encapsulate our message
    cout << "\n[Transport Layer] Sending: \n" << dwTransport << endl << endl;
    TransportLayer* pTransport = new TransportLayer();
    string dwNetwork = pTransport->Encapsulate(dwTransport);

    vector<string> networkSegments = pTransport->encapsulate(dwTransport);
    cout << "Segments: \n" << endl;
    
    writeToFile("\n[Transport Layer] Sending: \n");
    for (int i = 0; i < networkSegments.size(); i++) {
         cout << networkSegments[i] << endl;
         writeToFile(networkSegments[i]);
    }

    // create network layer and encapsulate our message
    cout << "\n[Network Layer] Sending Segments \n";
    writeToFile("\n[Network Layer] Sending Segments \n");
    vector<string> linkSegments;
    NetworkLayer* pNetwork = new NetworkLayer("04", m_dwIP, dwHost);
    for (int i = 0; i < networkSegments.size(); i++) {
        string dwNetwork = pNetwork->Encapsulate(networkSegments[i]);
        cout << dwNetwork << endl;
        writeToFile(dwNetwork);
        linkSegments.push_back(dwNetwork);
    }

    // create link layer and encapsulate our message
    cout << "\n[Link Layer] Sending Segments \n";
    writeToFile("\n[Link Layer] Sending Segments \n");
    vector<string> finalSegments;
    LinkLayer* pLink = new LinkLayer("7c:21:4a:3c:0b:f9", m_dwMACAddress, "0800");
    for (int i = 0; i < linkSegments.size(); i++) {
        string dwLink = pLink->Encapsulate(linkSegments[i]);
        cout << dwLink << endl;
        writeToFile(dwLink);
        finalSegments.push_back(dwLink);
    }

    cout << "\nencapsulation finished" << endl;

    cout <<"\n==== Receiving ====" << endl;
    writeToFile("\n==== Receiving ====");

    vector<string> linkSegmentsDecap = pLink->Decapsulate(finalSegments);
    writeToFile("\n========== Link Layer Decapsulate:\n" + linkSegmentsDecap[0]);


    vector<string> networkSegmentsDecap = pNetwork->Decapsulate(linkSegmentsDecap);
    writeToFile("\n========== Newtork Layer Decapsulate:\n" + networkSegmentsDecap[0]);

    string decapTransMessage = pTransport->decapsulate(networkSegmentsDecap);
    
    cout << "Transport Layer Decapsulate: \n" << decapTransMessage << endl << endl;
    writeToFile("\n========== Transport Layer Decapsulate:\n" + decapTransMessage);
    string decapAppMessage = pApplication->decapsulate(decapTransMessage);

    cout << "Final message: \n" << decapAppMessage << endl << endl;
    writeToFile("\n========== Final message:\n" + decapAppMessage);
}

void Client::RecieveMessage(string dwMesage) {

}