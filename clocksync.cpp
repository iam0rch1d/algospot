#include <iostream>
#include <vector>

#define NUM_SWITCH 10
#define NUM_CLOCK 16
#define NUM_TIME_TYPE 4
#define NUM_TIME_UNIT 3

using namespace std;

//      "0123456789abcdef"
const char mappingTable[NUM_SWITCH][NUM_CLOCK + 1] = {
        "@@@.............", // Switch No.[0] is mapped to clock No.[0, 1, 2]
        "...@...@.@.@....", // Switch No.[1] is mapped to clock No.[3, 7, 9, 11]
        "....@.....@...@@", // Switch No.[2] is mapped to clock No.[4, 10, 14, 15]
        "@...@@@@........", // Switch No.[3] is mapped to clock No.[0, 4, 5, 6, 7]
        "......@@@.@.@...", // Switch No.[4] is mapped to clock No.[6, 7, 8, 10, 12]
        "@.@...........@@", // Switch No.[5] is mapped to clock No.[0, 2, 14, 15]
        "...@..........@@", // Switch No.[6] is mapped to clock No.[3, 14, 15]
        "....@@.@......@@", // Switch No.[7] is mapped to clock No.[4, 5, 7, 14, 15]
        ".@@@@@..........", // Switch No.[8] is mapped to clock No.[1, 2, 3, 4, 5]
        "...@@@...@...@..", // Switch No.[9] is mapped to clock No.[3, 4, 5, 9, 13]
};

class Clocks {
private:
    vector<int> times;

public:
    explicit Clocks(vector<int> &times) {
        this->times = times;
    }

    bool areAligned() {
        for (int i = 0; i < NUM_CLOCK; i++) {
            if (times[i] != NUM_TIME_TYPE * NUM_TIME_UNIT) return false;
        }

        return true;
    }

    void pushSwitch(int switchNo) {
        for (int i = 0; i < NUM_CLOCK; i++) {
            if (mappingTable[switchNo][i] == '@') times[i] += 3;

            if (times[i] > NUM_TIME_TYPE * NUM_TIME_UNIT) times[i] = 1 * NUM_TIME_UNIT;
        }
    }
};

int countPushMinimum(Clocks clocks, int switchNo) {
    int numPushMinimum = INT16_MAX;

    if (switchNo == NUM_SWITCH) return clocks.areAligned() ? 0 : INT16_MAX; // Base case

    for (int i = 0; i < NUM_TIME_TYPE; i++) {
        numPushMinimum = min(numPushMinimum, countPushMinimum(clocks, switchNo + 1) + i); // Recursive steps

        clocks.pushSwitch(switchNo);
    }

    return numPushMinimum;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    for (int testcaseNo = 0; testcaseNo < numTestcase; testcaseNo++) {
        vector<int> times(NUM_CLOCK);

        for (int &time : times) {
            cin >> time;
        }

        int numPushMinimum = countPushMinimum(Clocks(times), 0);

        if (numPushMinimum == INT16_MAX) numPushMinimum = -1;

        cout << numPushMinimum << "\n";
    }

    return 0;
}
