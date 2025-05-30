#include <iostream>
#include <windows.h>
#include <string>

// include client
#include "client/client.cpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(65001);
    
    Client* c1 = new Client("192.168.056.001"); 
    Client* c2 = new Client("172.031.000.001"); 

    string cats = "Domestic cats are found across the globe, though their popularity as pets varies by region. Out of the estimated 600 million cats worldwide, 400 million reside in Asia, including 58 million pet cats in China. The United States leads in cat ownership with 73.8 million cats. In the United Kingdom, approximately 10.9 million domestic cats are kept as pets.";
    c1->SendMessage(c2, cats);
    /* code */
    return 0;
}

