#include <iostream>
#include <thread>

#include "C:/includes/CppSockets/sockets.cpp"

using namespace std;

int main(){
    string solution;

    while (cin) {
        string temp;
        getline(cin, temp);
        solution += temp;
    }

	TCPClient cl("52.49.91.111", 2019);

    cl.send(solution);

    do {
        cout << cl.recv();
    } while(cl.isConnected());
}