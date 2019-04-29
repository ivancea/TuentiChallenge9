#include <iostream>
#include <map>

using namespace std;

int gcd(int a, int b)
{
    while (true)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int main(){
    int caseCount;
    cin >> caseCount;

    for(int caseNumber=1; caseNumber<=caseCount; caseNumber++){
        int entryCount;
        cin >> entryCount;

        map<uint64_t, uint64_t> entriesToCount;

        uint64_t listMult = 1;

        for (int i = 0; i < entryCount; i++) {
            uint64_t number;
            cin >> number;

            entriesToCount[number] += number;
        }

        for (const auto& it : entriesToCount) {
            listMult = lcm(listMult, lcm(it.first * it.first, it.second) / it.second);
        }

        uint64_t personCount = 0;
        uint64_t candyCount = 0;

        for (const auto& it : entriesToCount) {
            uint64_t candiesPerPerson = it.first;
            uint64_t personNumber = (it.second * listMult) / (it.first * it.first);

            personCount += personNumber;
            candyCount += personNumber * candiesPerPerson;
        }

        uint64_t resultGcd = gcd(candyCount, personCount);

        cout << "Case #" << caseNumber << ": " << (candyCount / resultGcd) << "/" << (personCount / resultGcd) << endl;
    }
}