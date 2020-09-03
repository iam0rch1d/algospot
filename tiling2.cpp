#include <cstring>
#include <iostream>

#define UNMEMOIZED -1
#define MODULUS 1000000007

using namespace std;

int tilingCountCache[101];

int memoizeTilingCount(int width) {
    if (width <= 1) return 1;

    int &tilingCount = tilingCountCache[width];

    if (tilingCount != UNMEMOIZED) return tilingCount;

    return tilingCount = (memoizeTilingCount(width - 1) + memoizeTilingCount(width - 2)) % MODULUS;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int width;

        memset(tilingCountCache, UNMEMOIZED, sizeof(tilingCountCache));

        cin >> width;

        cout << memoizeTilingCount(width) << endl;
    }

    return 0;
}
