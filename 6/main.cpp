#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

template<typename C, typename T>
bool contains(const C& container, const T& element) {
    return container.find(element) != container.end();
}

bool hasOneDifferentLetter(const string& word) {
    set<char> letters;

    for (char c : word) {
        letters.insert(c);
    }

    return letters.size() == 1;
}

bool solve(int caseNumber, const vector<string>& words, string& orderedLetters) {
    int debugCase = 57;

    string const* lastWord = nullptr;

    /**
     * Key: Letter
     * Value: Letters that are greater than the key
     * */
    map<char, set<char>> letterToGreaterLetters;

    set<char> allLetters;

    for (const string& word : words) {
        if (lastWord != nullptr) {
            for (int i = 0; i < lastWord->size() && i < word.size(); i++) {
                if ((*lastWord)[i] != word[i]) {
                    letterToGreaterLetters[(*lastWord)[i]].emplace(word[i]);

                    allLetters.emplace((*lastWord)[i]);
                    allLetters.emplace(word[i]);

                    break;
                }
            }
        }

        lastWord = &word;
    }

    for(const string& word : words) {
        for(char ch : word) {
            if (allLetters.find(ch) == allLetters.end()) {
                for (const string& word : words) {
                    if (!hasOneDifferentLetter(word)) {
                        return false;
                    }
                }
                
                // Only 1 letter in all the dictionary
                orderedLetters.push_back(ch);

                return true;
            }
        }
    }

    if (caseNumber == debugCase) {
        cerr << endl;
        for (auto& p : letterToGreaterLetters) {
            char letter = p.first;

            for (char greaterLetter : p.second) {
                cerr << letter << " < " << greaterLetter << endl;
            }
        }
    }

    while (!allLetters.empty()) {
        bool ok = false;

        for(char letter : allLetters) {
            int min = -1;
            int max = orderedLetters.size();

            if (caseNumber == debugCase) cerr << "Current letter: " << letter << endl;

            for(int i = 0; i < orderedLetters.size() && min + 1 < max; i++) {
                char orderedLetter = orderedLetters[i];

                if (caseNumber == debugCase) cerr << "Test: " << orderedLetter << endl;

                if (contains(letterToGreaterLetters[letter], orderedLetter)) {
                    max = i;
                    if (caseNumber == debugCase) cerr << "New max: " << max << endl;

                    break;
                }

                if (contains(letterToGreaterLetters[orderedLetter], letter)) {
                    min = i;
                    if (caseNumber == debugCase) cerr << "New min: " << min << endl;
                }
            }

            if (caseNumber == debugCase) cerr << min << " - " << max << endl;

            if (min + 1 == max) {
                orderedLetters.insert(orderedLetters.begin() + min + 1, letter);

                if (caseNumber == debugCase) cerr << "Current order: " << orderedLetters << endl;

                allLetters.erase(letter);

                ok = true;

                break;
            }
        }

        if (!ok) { // Couldn't place any letter
            return false;
        }
    }

    return true;
}

int main(){
    int caseCount;
    cin >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        int wordCount;
        cin >> wordCount;

        vector<string> words;

        words.reserve(wordCount);

        for (int i = 0; i < wordCount; i++) {
            string word;
            cin >> word;

            words.emplace_back(word);
        }

        cout << "Case #" << caseNumber << ":";

        string orderedLetters;

        if (solve(caseNumber, words, orderedLetters)) {
            for(char c : orderedLetters) {
                cout << " " << c;
            }
        } else {
            cout << " AMBIGUOUS";
        }

        cout << endl;
    }
}