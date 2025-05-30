
#ifndef UTIL_CPP
#define UTIL_CPP

#include <string>
using std::string;

string R(string x, int c) {
    string build = "";
    for (int i = 0 ; i < c; ++i) {
        build += x;
    }
    return build;
}

string GenerateHeaders(int fcount) {
    string out = ""; 
    if (fcount == 0) {
        out += "┌────────────────────────────────────────┬──────────────────────────────────┬──────────────────────┬──────────────────────┐\n";
        out += "│ Link Layer                             │ Network Layer                    │ Transport Layer      │ Application Fragment │\n";
        out += "├────────────────────────────────────────┼──────────────────────────────────┼──────────────────────┼──────────────────────┤\n";
    }
    else if (fcount == 1) {
        out += "┌──────────────────────────────────┬──────────────────────┬──────────────────────┐\n";
        out += "│ Network Layer                    │ Transport Layer      │ Application Fragment │\n";
        out += "├──────────────────────────────────┼──────────────────────┼──────────────────────┤\n";

    }
    else if (fcount == 2) {
        out += "┌──────────────────────┬──────────────────────┐\n";
        out += "│ Transport Layer      │ Application Fragment │\n";
        out += "├──────────────────────┼──────────────────────┤\n";
    }
    else if (fcount == 3) {
        // this one will be a little more special
    }
    return out;
}

string GenerateFooters(int fcount) {
    string out = "";
    if (fcount == 0) {
        out = "└────────────────────────────────────────┴──────────────────────────────────┴──────────────────────┴──────────────────────┘";
    }
    else if (fcount == 1) {
        out = "└──────────────────────────────────┴──────────────────────┴──────────────────────┘";

    }
    else if (fcount == 2) {
        out = "└──────────────────────┴──────────────────────┘";
    }
    else if (fcount == 3 ) {
        out = "";
    }
    return out;
}

// this function exists purely to generate nice looking output
string GenerateRow(string message, int fcount) {
    string link = "";
    string network = "";
    string transport = "";
    string fapplicaion = "";

    if (fcount <= 0) {
        link = message.substr(0, 38);
        message = message.substr(38);
    }
    
    if (fcount <= 1) {
        network = message.substr(0, 32);
        message = message.substr(32);
    }

    if (fcount <= 2) {
        transport = message.substr(0, 20);
        message = message.substr(20);
    }

    if (fcount <= 3) {
        fapplicaion = message + R(" ", 20-message.size());
    }

    if (fcount == 0) {
        return "│ " + link + " │ " + network + " │ " + transport + " │ " + fapplicaion + " │";
    }

    if (fcount == 1) {
        return "│ " + network + " │ " + transport + " │ " + fapplicaion + " │";
    }

    if (fcount == 2) {
        return "│ " + transport + " │ " + fapplicaion + " │";
    }

}

string FormatNL(string body) {
    string out = "";
    for (int i = 0; i < body.size(); ++i) {
        if (body[i] == '\r') {
            out += "\\r";
            continue;
        }
        if (body[i] == '\n') {
            out += "\\n";
            continue;
        }

        out += body[i];
    }
    return out;
}

string ReNL(string body) {
    string out = "";
    for (int i = 0; i < body.size(); ++i) {
        if (body[i] == '\\') {
            if (body[i+1] == 'r') {
                out += "\r";
                i += 1;
                continue;
            }
            if (body[i+1] == 'n') {
                out += "\n";
                i += 1;
                continue;
            }
        }

        out += body[i];
        
    }
    return out;
}

string FitInTable(string title, string input) {
    string head = "┌───────────────────────────────────────────────────────────────────────────┐\n";
    head += "│ " + title + R(" ", 72-title.size()+1) + " │\n";
    head += "├───────────────────────────────────────────────────────────────────────────┤\n";
    string foot = "└───────────────────────────────────────────────────────────────────────────┘";
    string body = "";
    
    string coll = "";
    int c = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] != '\n' && input[i] != '\r') {
            coll += input[i];
        }
        c += 1;

        if (c > 72 || input[i] == '\n') {
            body += "│ " + coll + R(" ", 72-coll.size()+1) + " │\n";
            coll = "";
            c = 0;
        }
    }
    if (coll.size() > 0) {
        body += "│ " + coll + R(" ", 72-coll.size()+1) + " │\n";
    }

    return head + body + foot;
}

#endif