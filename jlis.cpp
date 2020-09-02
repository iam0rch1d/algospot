#include <cstring>
#include <iostream>

#define UNMEMOIZED -1

using namespace std;

int numAElement;
int numBElement;
int sequenceA[100];
int sequenceB[100];
int maximumLengthCache[101][101];

int memoizeMaximumLength(int sequenceAStartingAt, int sequenceBStartingAt) {
    int &maximumLength = maximumLengthCache[sequenceAStartingAt + 1][sequenceBStartingAt + 1];

    if (maximumLength != UNMEMOIZED) return maximumLength;

    maximumLength = 0;

    long long sequenceACurrentElement = sequenceAStartingAt == -1 ? INT64_MIN : sequenceA[sequenceAStartingAt];
    long long sequenceBCurrentElement = sequenceBStartingAt == -1 ? INT64_MIN : sequenceB[sequenceBStartingAt];
    long long maximumCurrentElement = max(sequenceACurrentElement, sequenceBCurrentElement);

    for (int i = sequenceAStartingAt + 1; i < numAElement; i++) {
        if (maximumCurrentElement < sequenceA[i]) {
            maximumLength = max(maximumLength, memoizeMaximumLength(i, sequenceBStartingAt) + 1);
        }
    }

    for (int i = sequenceBStartingAt + 1; i < numBElement; i++) {
        if (maximumCurrentElement < sequenceB[i]) {
            maximumLength = max(maximumLength, memoizeMaximumLength(sequenceAStartingAt, i) + 1);
        }
    }

    return maximumLength;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        cin >> numAElement >> numBElement;

        for (int i = 0; i < numAElement; i++) {
            cin >> sequenceA[i];
        }

        for (int i = 0; i < numBElement; i++) {
            cin >> sequenceB[i];
        }

        memset(maximumLengthCache, -1, sizeof(maximumLengthCache));

        cout << memoizeMaximumLength(-1, -1) << endl;
    }

    return 0;
}
