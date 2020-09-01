#include <iostream>
#include <vector>

#define UNMEMOIZED -1

using namespace std;

int memoizeMaximumLength(const vector<int> &sequence, vector<int> &maximumLengthCache, int startingAt) {
    int &maximumLength = maximumLengthCache[startingAt + 1];

    if (maximumLength != UNMEMOIZED) return maximumLength;

    maximumLength = 1;

    for (int i = startingAt + 1; i < sequence.size(); i++) {
        if (startingAt == -1 || sequence[startingAt] < sequence[i]) {
            maximumLength = max(maximumLength, memoizeMaximumLength(sequence, maximumLengthCache, i) + 1);
        }
    }

    return maximumLength;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numElement;

        cin >> numElement;

        vector<int> sequence(numElement);
        vector<int> maximumLength(numElement + 1, UNMEMOIZED);

        for (int &element : sequence) {
            cin >> element;
        }

        cout << memoizeMaximumLength(sequence, maximumLength, -1) - 1 << endl;
    }

    return 0;
}
