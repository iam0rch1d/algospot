#include <cstring>
#include <iostream>

#define UNMEMOIZED -1
#define CASE_CLEAR_COEFFICIENT 0.25
#define CASE_RAINY_COEFFICIENT 0.75

using namespace std;

int goal;
int deadline;
double expectedHeightCache[2001][1000];

double memoizeExpectedHeight(int currentHeight, int currentDay) {
    if (currentDay == deadline) return currentHeight >= goal ? 1 : 0;

    double &expectedHeight = expectedHeightCache[currentHeight][currentDay];

    if (expectedHeight != UNMEMOIZED) return expectedHeight;

    return expectedHeight = CASE_CLEAR_COEFFICIENT * memoizeExpectedHeight(currentHeight + 1, currentDay + 1)
                            + CASE_RAINY_COEFFICIENT * memoizeExpectedHeight(currentHeight + 2, currentDay + 1);
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        cin >> goal >> deadline;

        for (auto &i : expectedHeightCache) {
            for (double &j : i) {
                j = UNMEMOIZED;
            }
        }

        cout.precision(8);

        cout << memoizeExpectedHeight(0, 0) << endl;
    }

    return 0;
}
