#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> keyboard = {
    "1234567890",
    "QWERTYUIOP",
    "ASDFGHJKL;",
    "ZXCVBNM,.-"
};

int main(){
    int caseCount;
    cin >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        char lastLetter;
        cin >> lastLetter;

        string message;
        getline(cin, message);

        cout << "Case #" << caseNumber << ": " << endl;
    }
}