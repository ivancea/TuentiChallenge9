#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

using Byte = uint8_t;

const int HASH_SIZE = 16;

const Byte MAX_BYTE = 122;
const Byte MIN_BYTE = 48;

const string PRINT_SEPARATOR = "---";

istream& in = cin;

/*istringstream in = istringstream(R"_(1
3
b
------
a
3
a
------
aaaaaaaaaaaaaa)_");*/

/*istringstream in = istringstream(R"_(1
3
Subject: Boat;From: Charlie;To: Desmond;
------
Not Penny's boat
3
Subject: Boat;From: Charlie;To: Desmond;
------
Penny's boat :))_");*/



template<typename T>
ostream& operator<<(ostream& o, const vector<T>& hash) {
    o << '[';

    for (int i = 0; i < hash.size(); i++) {
        if (i != 0) {
            o << ", ";
        }

        o << (int)hash[i];
    }
    
    o << ']';

    return o;
}

vector<Byte> hashText(string text, vector<Byte> hash = vector<Byte>(HASH_SIZE, 0), int offset = 0) {
    for (int i = 0; i < text.size(); i++) {
        hash[(offset + i) % HASH_SIZE] += text[i];
    }

    return hash;
}

vector<Byte> generateDiffs(int initialOffset, const vector<Byte>& initialHash, const vector<Byte>& targetHash, const string& remainingText) {
    vector<Byte> diffs(targetHash);

    for(int i = 0; i < initialHash.size(); i++) {
        diffs[i] -= initialHash[i];
    }

    for(int i = 0; i < remainingText.size(); i++) {
        diffs[(initialOffset + i) % HASH_SIZE] -= remainingText[i];
    }

    return diffs;
}

bool canMakeDiff(Byte diff, int elementCount) {
    if ((MAX_BYTE - MIN_BYTE) * elementCount >= 255) {
        return true;
    }

    int max = (elementCount * MAX_BYTE) % 256;
    int min = (elementCount * MIN_BYTE) % 256;

    if (max < min) {
        return diff >= min || diff <= max;
    }

    return diff >= min && diff <= max;
}

void addChars(string& result, int initialCharIndex, Byte diff, int elementCount) {
    Byte currentDiff = diff;

    for(int i = 0; i < elementCount; i++) {
        // Bruteforce, may be improved
        for(Byte j = MIN_BYTE; j <= MAX_BYTE; j++) {
            if (canMakeDiff(currentDiff - j, elementCount - i - 1)) {
                result[initialCharIndex + (i * HASH_SIZE)] = j;
                currentDiff -= j;
                break;
            }
        }
    }
}

bool isPossible(const vector<Byte>& diffs, int elementsInserted, const vector<int>& newElements) {
    for(int i = 0; i < newElements.size(); i++) {
        if (!canMakeDiff(diffs[i], newElements[i])) {
            if (elementsInserted == 49) {
                cerr << "New elements: " <<  newElements << endl;
            } 
            return false;
        }
    }

    return true;
}

string makePrintArea(int initialOffset, const vector<Byte>& diffs, int elementsInserted, const vector<int>& newElements) {
    string result = string(elementsInserted, '_');

    for(int i = 0; i < newElements.size(); i++) {
        int currentIndex = (initialOffset + i) % HASH_SIZE;

        addChars(result, i % HASH_SIZE, diffs[currentIndex], newElements[currentIndex]);
    }

    return result;
}

string solve(int initialOffset, const vector<Byte>& initialHash, const vector<Byte>& targetHash, const string& remainingText) {
    vector<int> newElements(HASH_SIZE, 0);

    for(int elementsInserted = 0; ; elementsInserted++) {
        vector<Byte> diffs = generateDiffs(initialOffset + elementsInserted, initialHash, targetHash, remainingText);

        if (isPossible(diffs, elementsInserted, newElements)) {
            cerr << "Elements inserted: " << elementsInserted << endl;

            return makePrintArea(initialOffset, diffs, elementsInserted, newElements);
        }
        
        // Insert element and rotate diffs
        newElements[(initialOffset + elementsInserted) % HASH_SIZE]++;

    }

    return "";
}

int main(){
    int caseCount;
    in >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        int originalLineCount;
        in >> originalLineCount;

        in.ignore();

        string originalText;

        for(int i = 0; i < originalLineCount; i++) {
            string line;
            getline(in, line);

            originalText += line;
        }

        int alteredLineCount;
        in >> alteredLineCount;

        in.ignore();

        string alteredText;

        for(int i = 0; i < alteredLineCount; i++) {
            string line;
            getline(in, line);

            alteredText += line;
        }

        int printTextPosition = alteredText.find(PRINT_SEPARATOR) + PRINT_SEPARATOR.size();

        vector<Byte> originalHash = hashText(originalText);
        vector<Byte> alteredHash = hashText(alteredText);
        vector<Byte> alteredHashUntilPrintZone = hashText(alteredText.substr(0, printTextPosition));


        cerr << "Original: " << originalHash << endl;
        cerr << "Altered: " << alteredHash << endl;
        cerr << "Initial offset: " << (printTextPosition % 16) << endl;

        string result = solve(printTextPosition, alteredHashUntilPrintZone, originalHash, alteredText.substr(printTextPosition));

        vector<Byte> finalHash = hashText(alteredText.substr(0, printTextPosition) + result + alteredText.substr(printTextPosition));

        cerr << "Final: " << finalHash << endl;
        cerr << "Result: " << (originalHash == finalHash ? "OK" : "ERROR") << endl;

        cout << "Case #" << caseNumber << ": " << result << endl;
    }
}