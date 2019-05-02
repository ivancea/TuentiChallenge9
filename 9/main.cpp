#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>

using namespace std;

istream& in = cin;

/*istringstream in = istringstream(R"_(3
4
7 10 2 1000
5
2 3 100 10 2
6
4 2 1000 100 10 2
4
5 10 100 2
3
5 10 6
8
1000 10 10000 2 100 1 5 6
4
1000 8 100 2
6
7 100 4 1000 10 7
7
1000 5 100 3 6 10 5
)_");*/



 int toInt(vector<int>& vals) {
    int result = 0;

    int currentMul = 1;

    for (int i = vals.size() - 1; i >= 0; i--) {
        if (vals[i] > 9) {
            if (currentMul > 1) {
                result += currentMul;
            }
            currentMul = vals[i];
        } else {
            result += currentMul * vals[i];
            currentMul = 1;
        }
    }
    
    if (currentMul > 9) {
        result += currentMul;
    }

    return result;
}

bool isValid(vector<int>& vals) {
    if (vals[0] == 10000) {
        return false;
    }
    
    int maxMul = 1000000;

    bool lastWasDigit = false;
    bool lastWasOne = false;

    for (int val : vals) {
        if (val < 10) {
            if (lastWasDigit) {
                return false;
            }

            lastWasOne = (val == 1);
            lastWasDigit = true;
        } else {
            if (val >= maxMul) {
                return false;
            }

            if (val < 10000 && lastWasOne) {
                return false;
            }

            lastWasDigit = false;
            lastWasOne = false;
            maxMul = val;
        }
    }
    
    return true;
}

vector<int> generatePossibleNumbers(vector<int>& kanjis) {
    vector<int> possibleNumbers;

    possibleNumbers.reserve(1000);

    sort(kanjis.begin(), kanjis.end());

    do {
        if (isValid(kanjis)) {
            possibleNumbers.push_back(toInt(kanjis));
        }
    } while(next_permutation(kanjis.begin(), kanjis.end()));

    return possibleNumbers;
    /*digits = []
    muls = []

    for val in vals:
        if val > 9:
            muls.append(val)
        else:
            digits.append(val)
    
    muls.sort(reverse=true)

    if len(digits) == 0:
        return muls

    for digitPermutation in itertools.permutations(digits):
        for i in range(0, len(vals) - len(digits) + 1):
            array = muls.copy()
            putAll(array, digits.copy(), i)

            if isValid(array):
                yield toInt(val)*/
}


string solve(vector<int> aKanji, vector<int> bKanji, vector<int> resultKanji) {
    for(int a : generatePossibleNumbers(aKanji)) {
        for(int b : generatePossibleNumbers(bKanji)) {
            for(int result : generatePossibleNumbers(resultKanji)) {
                char operand;

                if (a + b == result) {
                    operand = '+';
                } else if (a - b == result) {
                    operand = '-';
                } else if (a * b == result) {
                    operand = '*';
                } else {
                    continue;
                }
                
                return to_string(a) + " " + operand + " " + to_string(b) + " = " + to_string(result);
            }
        }
    }

    return "";
}

int main(){
    int caseCount;
    in >> caseCount;

    vector<future<string>> futures;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        int aCount, bCount, resultCount;
        vector<int> aKanji, bKanji, resultKanji;

        in >> aCount;
        for (int i = 0; i < aCount; i++) {
            int n;
            in >> n;

            aKanji.push_back(n);
        }

        in >> bCount;
        for (int i = 0; i < bCount; i++) {
            int n;
            in >> n;

            bKanji.push_back(n);
        }

        in >> resultCount;
        for (int i = 0; i < resultCount; i++) {
            int n;
            in >> n;

            resultKanji.push_back(n);
        }

        futures.emplace_back(async(launch::async, solve, aKanji, bKanji, resultKanji));
    }

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        string result = futures[caseNumber - 1].get();

        cerr << "Case #" << caseNumber << ": " << result << endl;
        cout << "Case #" << caseNumber << ": " << result << endl;
    }
}