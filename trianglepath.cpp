#include <iostream>
#include <vector>

#define UNMEMOIZED -1

using namespace std;

typedef struct {
    int y;
    int x;
} Point;

int memoizeMaximumPath(vector<vector<int>> &numbers, vector<vector<int>> &maximumPathCache, Point at) {
    if (at.y == numbers.size() - 1) return numbers[at.y][at.x];

    int &maximumPath = maximumPathCache[at.y][at.x];

    if (maximumPath != UNMEMOIZED) return maximumPath;

    return maximumPath = numbers[at.y][at.x] + max(memoizeMaximumPath(numbers, maximumPathCache, {at.y + 1, at.x}),
                                                   memoizeMaximumPath(numbers, maximumPathCache, {at.y + 1, at.x + 1}));
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numRow;

        cin >> numRow;

        vector<vector<int>> numbers(numRow, vector<int>(numRow));
        vector<vector<int>> maximumPathCache(numRow, vector<int>(numRow, UNMEMOIZED));

        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < i + 1; j++) {
                cin >> numbers[i][j];
            }
        }

        cout << memoizeMaximumPath(numbers, maximumPathCache, {0, 0}) << endl;
    }

    return 0;
}

