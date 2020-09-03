#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

#define UNMEMOIZED -1
#define MAXIMUM_RSS 10000001

using namespace std;

int sequenceSize;
int sequence[100];
int partialSumCache[100];
int squaredPartialSumCache[100];
int minimumRssCache[101][11]; // 'RSS' refers to 'Residual Sum of Squares'

int calculateRss(int startingAt, int quantizationSize) {
    int sum = partialSumCache[startingAt + quantizationSize - 1]
              - (startingAt == 0 ? 0 : partialSumCache[startingAt - 1]);
    int squaredSum = squaredPartialSumCache[startingAt + quantizationSize - 1]
                     - (startingAt == 0 ? 0 : squaredPartialSumCache[startingAt - 1]);
    int mean = lround((double) sum / quantizationSize);

    return squaredSum - 2 * mean * sum + quantizationSize * mean * mean;
}

int memoizeMinimumRss(int startingAt, int numLeftQuantizer) {
    if (startingAt == sequenceSize) return 0;

    if (numLeftQuantizer == 0) return MAXIMUM_RSS;

    int &minimumRss = minimumRssCache[startingAt][numLeftQuantizer];

    if (minimumRss != UNMEMOIZED) return minimumRss;

    minimumRss = MAXIMUM_RSS;

    for (int quantizationSize = 1; startingAt + quantizationSize <= sequenceSize; quantizationSize++) {
        minimumRss = min(minimumRss,
                         calculateRss(startingAt, quantizationSize)
                         + memoizeMinimumRss(startingAt + quantizationSize, numLeftQuantizer - 1));
    }

    return minimumRss;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numQuantizer;

        cin >> sequenceSize >> numQuantizer;

        for (int i = 0; i < sequenceSize; i++) {
            cin >> sequence[i];
        }

        sort(sequence, sequence + sequenceSize);

        partialSumCache[0] = sequence[0];
        squaredPartialSumCache[0] = sequence[0] * sequence[0];

        for (int i = 1; i < sequenceSize; i++) {
            partialSumCache[i] = partialSumCache[i - 1] + sequence[i];
            squaredPartialSumCache[i] = squaredPartialSumCache[i - 1] + sequence[i] * sequence[i];
        }

        memset(minimumRssCache, UNMEMOIZED, sizeof(minimumRssCache));

        cout << memoizeMinimumRss(0, numQuantizer) << endl;
    }

    return 0;
}
