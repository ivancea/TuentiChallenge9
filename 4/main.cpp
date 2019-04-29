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

        map<int, int> entriesToCount;

        int listMult = 1;

        for (int i = 0; i < entryCount; i++) {
            int number;
            cin >> number;

            entriesToCount[number] += number;
        }

        for (const auto& it : entriesToCount) {
            listMult = lcm(listMult, lcm(it.first * it.first, it.second) / it.second);
        }

        cerr << listMult << endl;

        int personCount = 0;
        int candyCount = 0;

        for (const auto& it : entriesToCount) {
            int candiesPerPerson = it.first;
            int personNumber = (it.second * listMult) / (it.first * it.first);

            personCount += personNumber;
            candyCount += personNumber * candiesPerPerson;
        }

        cerr << personCount << " - " << candyCount << endl;

        int resultGcd = gcd(candyCount, personCount);

        cout << "Case #" << caseNumber << ": " << (candyCount / resultGcd) << "/" << (personCount / resultGcd) << endl;
    }
}