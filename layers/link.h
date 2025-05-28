
#ifndef LINK_H
#define LINK_H

#include <string>

using std::string;

class Link {
    public:
        Link();
        string Encapsulate(string message);
        string Decapsulate(string message);

    private:

};

#endif