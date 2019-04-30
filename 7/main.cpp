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


bool canMakeDiff(char diff, int elementCount) {
    // TODO
}

string makePrintZone(int initialOffset, const vector<char>& initialHash, const vector<char>& targetHash, const string& remainingText) {
    vector<char> diffs(targetHash);

    for(int i = 0; i < remainingText.size(); i++) { // Test this block: if remainingText == all the text, diffs = {0}
        diffs[(initialOffset + i) % 16] -= remainingText[i];
    }

    vector<int> newElements(16, 0);

    for(int nextElementOffset = 0; ; nextElementOffset++) {
        newElements[(initialOffset + nextElementOffset) % 16]++;

        bool isPossible = true;

        for(int i = 0; i < newElements.size(); i++) {
            if (!canMakeDiff(diffs[(initialOffset + nextElementOffset + i) % 16], newElements[i])) {
                isPossible = false;
                break;
            }
        }

        if (isPossible) {
            // Make vectors of optimized chars
            // Convert them to string
            // Return it
        }
    }

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

        int printTextPosition = alteredText.find("------") + 3;

        vector<char> originalHash = hashText(originalText);
        vector<char> alteredHashUntilPrintZone = hashText(alteredText.substr(0, printTextPosition));


        coutHash(originalHash);

        string result = makePrintZone(printTextPosition, alteredHashUntilPrintZone, originalHash, alteredText.substr(printTextPosition))

        cout << "Case #" << caseNumber << ": " << endl;
    }
}