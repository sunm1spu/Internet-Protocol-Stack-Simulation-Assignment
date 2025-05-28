
#ifndef NETWORK_H
#define NETWORK_H

#include <string>

using std::string;

class NetworkLayer {
    public:
        NetworkLayer();
        string Encapsulate(string message);
        string Decapsulate(string message);

    private:
        string dwIPVersion;
        string dwSourceIP;
        string dwDestinationIP;

};

#endif