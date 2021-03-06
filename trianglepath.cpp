#include <cstring>
#include <iostream>

#define UNMEMOIZED -1

using namespace std;

typedef struct {
    int y;
    int x;
} Point;

int numRow;
int triangle[100][100];
int maximumPathCache[100][100];

int memoizeMaximumPath(Point from) {
    if (from.y == numRow - 1) return triangle[from.y][from.x];

    int &maximumPath = maximumPathCache[from.y][from.x];

    if (maximumPath != UNMEMOIZED) return maximumPath;

    return maximumPath = triangle[from.y][from.x]
                         + max(memoizeMaximumPath({from.y + 1, from.x}),
                               memoizeMaximumPath({from.y + 1, from.x + 1}));
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        cin >> numRow;

        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < i + 1; j++) {
                cin >> triangle[i][j];
            }
        }

        memset(maximumPathCache, UNMEMOIZED, sizeof(maximumPathCache));

        cout << memoizeMaximumPath({0, 0}) << endl;
    }

    return 0;
}
