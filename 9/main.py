import io
import itertools

KANJIS = {
    '一': 1,
    '二': 2,
    '三': 3,
    '四': 4,
    '五': 5,
    '六': 6,
    '七': 7,
    '八': 8,
    '九': 9,
    '十': 10,
    '百': 100,
    '千': 1000,
    '万': 10000,
}

def toInt(vals):
    result = 0

    currentMul = 1

    for val in reversed(vals):
        if val > 9:
            if currentMul > 1:
                result += currentMul
            currentMul = val
        else:
            result += currentMul * val
            currentMul = 1
    
    if currentMul > 9:
        result += currentMul

    return result

def isValid(vals):
    if vals[0] == 10000:
        return False
    
    maxMul = 1000000

    lastWasDigit = False
    lastWasOne = False

    for val in vals:
        if val < 10:
            if lastWasDigit: # Two digits without mul
                return False

            lastWasOne = (val == 1)
            lastWasDigit = True

        if val > 9:
            if val >= maxMul:
                return False
            if val < 10000 and lastWasOne:
                return False

            lastWasDigit = False
            lastWasOne = False
            maxMul = val
    
    return True

def generatePossibleNumbers(kanjis):
    vals = [KANJIS[kanji] for kanji in kanjis]

    digits = []
    muls = []

    for val in vals:
        if val > 9:
            muls.append(val)
        else:
            digits.append(val)
    
    muls.sort(reverse=True)

    if len(digits) == 0:
        return muls

    for digitPermutation in itertools.permutations(digits):
        for i in range(0, len(vals) - len(digits) + 1):
            array = muls.copy()
            putAll(array, digits.copy(), i)

            if isValid(array):
                yield toInt(val)


def solve(aKanji, bKanji, resultKanji):
    for a in generatePossibleNumbers(aKanji):
        for b in generatePossibleNumbers(bKanji):
            for result in generatePossibleNumbers(resultKanji):
                operand = ""

                if a + b == result:
                    operand = "+"
                elif a - b == result:
                    operand = "-"
                elif a * b == result:
                    operand = "*"
                
                if operand != "":
                    return str(a) + " " + operand + " " + str(b) + " = " + str(result)

def main():
    file = io.open("submitInput.txt", mode="r", encoding="utf-8")
    outputFile = io.open("customSubmitInput.txt", mode="w", encoding="utf-8")
    caseCount = int(file.readline())

    print(caseCount, file=outputFile)

    for caseNumber in range(1, caseCount + 1):
        line = file.readline().rstrip('\n')

        operands, resultKanji = line.split(" = ")
        aKanji, bKanji = operands.split(" OPERATOR ")

        #result = "Case #" + str(caseNumber) + ": " + solve(aKanji, bKanji, resultKanji)

        print(len(aKanji), file=outputFile)
        print(" ".join([str(KANJIS[kanji]) for kanji in aKanji]), file=outputFile)

        print(len(bKanji), file=outputFile)
        print(" ".join([str(KANJIS[kanji]) for kanji in bKanji]), file=outputFile)

        print(len(resultKanji), file=outputFile)
        print(" ".join([str(KANJIS[kanji]) for kanji in resultKanji]), file=outputFile)



main()
