#include <iostream>

// include client
#include "client/client.cpp"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{

    cout << "Test" << endl;
    
    Client* c1 = new Client("192.168.056.001"); 
    Client* c2 = new Client("172.031.000.001"); 

    c1->SendMessage("172.031.000.001");
    /* code */
    return 0;
}

