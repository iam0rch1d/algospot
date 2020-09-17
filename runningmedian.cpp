#include <iostream>
#include <queue>

#define MODULO 20090711

using namespace std;

typedef struct PseudoRng {
    int seed;
    int coefficientA;
    int coefficientB;

    PseudoRng(int a, int b): seed(1983), coefficientA(a), coefficientB(b) {};

    int next() {
        int next = seed;

        seed = (int) (((long long) seed * coefficientA + coefficientB) % MODULO);

        return next;
    }
} PseudoRng;  // 'RNG' refers to 'Random Number Generator'

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int sequenceSize;
        int a;
        int b;
        priority_queue<int> maxHeap;
        priority_queue<int, vector<int>, greater<>> minHeap;
        int medianSum = 0;

        cin >> sequenceSize >> a >> b;

        PseudoRng pseudoRng(a, b);

        while (sequenceSize-- > 0) {
            if (maxHeap.size() > minHeap.size()) minHeap.push(pseudoRng.next());
            else maxHeap.push(pseudoRng.next());

            if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
                int maxHeapTop = maxHeap.top();
                int minHeapTop = minHeap.top();

                maxHeap.pop();
                minHeap.pop();
                maxHeap.push(minHeapTop);
                minHeap.push(maxHeapTop);
            }

            medianSum = (medianSum + maxHeap.top()) % MODULO;
        }

        cout << medianSum << endl;
    }

    return 0;
}
