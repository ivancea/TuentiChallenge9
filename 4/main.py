from math import gcd

def lcm(a, b):
    return abs(a*b) // gcd(a, b)

def main():
    caseCount = int(input())

    for caseNumber in range(1, caseCount + 1):
        entryCount = int(input())

        entriesToCount = {}

        listMult = 1

        for n in input().split():
            number = int(n)
            entriesToCount[number] = number + entriesToCount[number] if number in entriesToCount else number

        for candiesPerPerson, total in entriesToCount.items():
            listMult = lcm(listMult, lcm(candiesPerPerson * candiesPerPerson, total) // total)

        personCount = 0
        candyCount = 0

        for candiesPerPerson, total in entriesToCount.items():
            personNumber = (total * listMult) // (candiesPerPerson * candiesPerPerson)

            personCount += personNumber
            candyCount += personNumber * candiesPerPerson

        resultGcd = gcd(candyCount, personCount)

        print("Case #" + str(caseNumber) + ": " + str(candyCount // resultGcd) + "/" + str(personCount // resultGcd))

main()