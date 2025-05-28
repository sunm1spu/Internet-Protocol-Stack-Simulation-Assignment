#include "client.h"
#include "../layers/application.h"

Client::Client(string dwIP) : m_dwIP(dwIP) { 
    // randomly generate MACAccress
    m_dwMACAddress = "1A:2B:3C:D4:E5:F6";
};

void Client::SendRequest(string dwHost) {
    string dwRequest = "GET / HTTP/1.1\r\n";
}
