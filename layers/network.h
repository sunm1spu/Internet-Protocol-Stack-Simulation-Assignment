
#ifndef NETWORK_H
#define NETWORK_H

#include <string>

using std::string;

class NetworkLayer {
    public:
        NetworkLayer();
        string Encapsulate(string message);
        vector<string> Decapsulate(vector<string> messages);
        string DecapsulateSegment(string message);

    private:
        string dwIPVersion;
        string dwSourceIP;
        string dwDestinationIP;

};

#endif