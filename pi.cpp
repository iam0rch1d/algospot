#include <cstring>
#include <iostream>

#define UNMEMOIZED -1
#define MAXIMUM_TOTAL_DIFFICULTY 20001

using namespace std;

string sequence;
int totalDifficultyCache[10002];

int calculateDifficulty(int startingAt, int size) {
    string subsequence = sequence.substr(startingAt, size);
    bool isProgressive = true;
    bool isAlternating = true;

    if (subsequence == string(size, subsequence[0])) return 1;

    for (int i = 0; i < size - 2; i++) {
        if (subsequence[i + 1] - subsequence[i] != subsequence[i + 2] - subsequence[i + 1]) {
            isProgressive = false;

            break;
        }
    }

    if (isProgressive) return abs(subsequence[1] - subsequence[0]) == 1 ? 2 : 5;

    for (int i = 0; i < size - 2; i++) {
        if (subsequence[i + 1] - subsequence[i] != subsequence[i + 1] - subsequence[i + 2]) {
            isAlternating = false;

            break;
        }
    }

    return isAlternating ? 4 : 10;
}

int memoizeTotalDifficulty(int startingAt) {
    if (startingAt == sequence.size()) return 0;

    int &totalDifficulty = totalDifficultyCache[startingAt];

    if (totalDifficulty != UNMEMOIZED) return totalDifficulty;

    totalDifficulty = MAXIMUM_TOTAL_DIFFICULTY;

    for (int pieceSize = 3; pieceSize <= 5; pieceSize++) {
        if (startingAt + pieceSize <= sequence.size()) {
            totalDifficulty = min(totalDifficulty,
                                  calculateDifficulty(startingAt, pieceSize)
                                  + memoizeTotalDifficulty(startingAt + pieceSize));
        }
    }

    return totalDifficulty;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        cin >> sequence;

        memset(totalDifficultyCache, UNMEMOIZED, sizeof(totalDifficultyCache));

        cout << memoizeTotalDifficulty(0) << endl;
    }

    return 0;
}
