#include <iostream>

// include client
#include "client/client.cpp"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{

    Client* c1 = new Client("192.168.56.1"); 
    Client* c2 = new Client("172.31.0.1"); 

    c1->SendMessage("172.31.0.1");
    /* code */
    return 0;
}

