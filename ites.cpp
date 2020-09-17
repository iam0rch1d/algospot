#include <iostream>
#include <queue>

using namespace std;

typedef struct PseudoRng {
    unsigned seed;

    PseudoRng(): seed(1983) {};

    unsigned next() {
        unsigned next = seed;

        seed = seed * 214013 + 2531011;

        return next % 10000 + 1;
    }
} PseudoRng;  // 'RNG' refers to 'Random Number Generator'

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int target;
        int numSignal;
        PseudoRng pseudoRng;
        queue<unsigned> sequence;
        unsigned sequenceSum = 0;
        int hitCount = 0;

        cin >> target >> numSignal;

        for (int i = 0; i < numSignal; i++) {
            unsigned currentSignal = pseudoRng.next();

            sequenceSum += currentSignal;

            sequence.push(currentSignal);

            while (sequenceSum > target) {
                sequenceSum -= sequence.front();

                sequence.pop();
            }

            if (sequenceSum == target) hitCount++;
        }

        cout << hitCount << endl;
    }

    return 0;
}
