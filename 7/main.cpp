#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<char> hashText(string text, vector<char> hash = vector<char>(16, 0), int offset = 0) {
    for (int i = 0; i < text.size(); i++) {
        hash[(offset + i) % 16] += text[i];
    }

    return hash;
}

void coutHash(const vector<char>& hash) {
    cout << '[';

    for (int i = 0; i < hash.size(); i++) {
        if (i != 0) {
            cout << ", ";
        }

        cout << (int)hash[i];
    }
    
    cout << ']' << endl;
}

string makePrintZone(int initialIndex, const vector<char>& initialHash, const vector<char>& targetHash) {

}

int main(){
    int caseCount;
    cin >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        int originalLineCount;
        cin >> originalLineCount;

        cin.ignore();

        string originalText;

        for(int i = 0; i < originalLineCount; i++) {
            string line;
            getline(cin, line);

            originalText += line;
        }

        int alteredLineCount;
        cin >> alteredLineCount;

        cin.ignore();

        string alteredText;

        for(int i = 0; i < alteredLineCount; i++) {
            string line;
            getline(cin, line);

            alteredText += line;
        }

        vector<char> originalHash = hashText(originalText);

        int printTextPosition = alteredText.find("------") + 3;


        coutHash(originalHash);

        cout << "Case #" << caseNumber << ": " << endl;
    }
}