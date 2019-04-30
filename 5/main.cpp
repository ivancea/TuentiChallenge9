#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator<(const Point& p) const {
        if (x == p.x) {
            return y < p.y;
        }

        return x < p.x;
    }
};

const vector<string> keyboard = {
    "1234567890",
    "QWERTYUIOP",
    "ASDFGHJKL;",
    "ZXCVBNM,.-"
};

map<char, Point> createCharsToPositions() {
    map<char, Point> m;

    for(int i = 0; i < keyboard.size(); i++) {
        for(int j = 0; j < keyboard[i].size(); j++) {
            m.emplace(keyboard[i][j], Point(i, j));
        }
    }

    return m;
}

const map<char, Point> charsToPositions = createCharsToPositions();

char withOffset(char character, const Point& offset) {
    Point originalPosition = charsToPositions.at(character);

    int newX = (originalPosition.x + offset.x) % keyboard.size();
    int newY = (originalPosition.y + offset.y) % keyboard[newX].size();

    return keyboard[newX][newY];
}

int main(){
    int caseCount;
    cin >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        char expectedLastLetter;
        cin >> expectedLastLetter;

        cin.ignore();

        string message;
        getline(cin, message);

        Point expectedLastLetterPosition = charsToPositions.at(expectedLastLetter);
        Point actualLastLetterPosition = charsToPositions.at(message[message.size() - 1]);

        int initialOffsetX = expectedLastLetterPosition.x - actualLastLetterPosition.x;
        int initialOffsetY = expectedLastLetterPosition.y - actualLastLetterPosition.y;

        Point offset = Point(
            initialOffsetX < 0 ? keyboard.size() + initialOffsetX : initialOffsetX,
            initialOffsetY < 0 ? keyboard[0].size() + initialOffsetY : initialOffsetY
        );

        for(char& c : message) {
            if (charsToPositions.find(c) != charsToPositions.end()) {
                c = withOffset(c, offset);
            }
        }

        cout << "Case #" << caseNumber << ": " << message << endl;
    }
}