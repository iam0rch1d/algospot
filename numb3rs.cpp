#include <cstring>
#include <iostream>
#include <vector>

#define UNMEMOIZED -1

using namespace std;

int numVillage;
int elapsedDays;
int prison;
int villageConnections[50][101];
int villageDegrees[50];
double probabilityCache[50][101];

double memoizeProbability(int currentVillageNo, int currentDay) {
    if (currentDay == 0) return currentVillageNo == prison ? 1 : 0;

    double &probability = probabilityCache[currentVillageNo][currentDay];

    if (probability != UNMEMOIZED) return probability;

    probability = 0;

    for (int previousVillageNo = 0; previousVillageNo < numVillage; previousVillageNo++) {
        if (villageConnections[currentVillageNo][previousVillageNo]) {
            probability += memoizeProbability(previousVillageNo, currentDay - 1) / villageDegrees[previousVillageNo];
        }
    }

    return probability;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numTarget;

        cin >> numVillage >> elapsedDays >> prison;

        memset(villageDegrees, 0, sizeof(villageDegrees));

        for (int i = 0; i < numVillage; i++) {
            for (int j = 0; j < numVillage; j++) {
                cin >> villageConnections[i][j];

                villageDegrees[i] += villageConnections[i][j];
            }
        }

        for (auto &i : probabilityCache) {
            for (double &j : i) {
                j = UNMEMOIZED;
            }
        }

        cin >> numTarget;

        vector<int> targets(numTarget);

        for (int i = 0; i < numTarget; i++) {
            cin >> targets[i];
        }

        cout.precision(8);

        for (int i = 0; i < numTarget; i++) {
            cout << memoizeProbability(targets[i], elapsedDays) << " ";
        }

        cout << endl;
    }

    return 0;
}
