#ifndef LINK_H
#define LINK_H

#include <string>

using std::string;

class LinkLayer {
    public:
        LinkLayer(string source, string destination, string type);
        string Encapsulate(string message);
        vector<string> Decapsulate(vector<string> messages);
        string DecapsulateSegment(string message);

    private:
        string m_dwType;
        string m_dwSource;
        string m_dwDestination;
};

#endif