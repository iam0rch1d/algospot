#include <cstring>
#include <iostream>

#define UNMEMOIZED -1
#define MODULO 10000000

using namespace std;

int pieces;
int polyominoCountCache[101][101];

int memoizePolyominoCount(int left, int toUse) {
    if (left == toUse) return 1;

    int &polyominoCount = polyominoCountCache[left][toUse];

    if (polyominoCount != UNMEMOIZED) return polyominoCount;

    polyominoCount = 0;

    for (int nextToUse = 1; nextToUse <= left - toUse; nextToUse++) {
        polyominoCount = (polyominoCount
                          + (toUse + nextToUse - 1) * memoizePolyominoCount(left - toUse, nextToUse) % MODULO)
                         % MODULO;
    }

    return polyominoCount;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int polyominoCount = 0;

        cin >> pieces;

        memset(polyominoCountCache, UNMEMOIZED, sizeof(polyominoCountCache));

        for (int firstToUse = 1; firstToUse <= pieces; firstToUse++) {
            polyominoCount = (polyominoCount + memoizePolyominoCount(pieces, firstToUse)) % MODULO;
        }

        cout << polyominoCount << endl;
    }

    return 0;
}
