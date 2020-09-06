#include <iostream>
#include <queue>

using namespace std;

typedef struct PseudoRng {
    unsigned seed;

    PseudoRng(): seed(1983) {};

    unsigned next() {
        seed = seed * 214013 + 2531011;

        return seed % 10000 + 1;
    }
} PseudoRng; // 'RNG' refers to 'Random Number Generator'

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

        sequence.push(0);

        for (int i = 0; i < numSignal; i++) {
            unsigned currentSignal = pseudoRng.next();

            sequence.push(currentSignal);

            sequenceSum += currentSignal;

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
