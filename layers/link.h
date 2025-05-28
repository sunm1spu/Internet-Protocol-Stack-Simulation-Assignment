
#ifndef LINK_H
#define LINK_H

#include <string>

using std::string;

class LinkLayer {
    public:
        LinkLayer();
        string Encapsulate(string message);
        string Decapsulate(string message);

    private:

};

#endif