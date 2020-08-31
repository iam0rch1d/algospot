#include <iostream>
#include <vector>

using namespace std;

typedef struct FenceDivision {
    int leftEnd;
    int rightEnd;
} FenceDivision;

int findMaximumFenceSurface(vector<int> &boardHeights, FenceDivision fenceDivision) {
    if (fenceDivision.leftEnd == fenceDivision.rightEnd) return boardHeights[fenceDivision.leftEnd];

    int center = (fenceDivision.leftEnd + fenceDivision.rightEnd) / 2;
    int maximumFenceSurface = max(findMaximumFenceSurface(boardHeights, {fenceDivision.leftEnd, center}),
                                  findMaximumFenceSurface(boardHeights, {center + 1, fenceDivision.rightEnd}));
    FenceDivision stretched = {center, center + 1};
    int stretchedHeight = min(boardHeights[stretched.leftEnd], boardHeights[stretched.rightEnd]);

    maximumFenceSurface = max(maximumFenceSurface, 2 * stretchedHeight);

    while (stretched.leftEnd > fenceDivision.leftEnd || stretched.rightEnd < fenceDivision.rightEnd) {
        if (stretched.rightEnd < fenceDivision.rightEnd
        && (stretched.leftEnd == fenceDivision.leftEnd
        || boardHeights[stretched.leftEnd - 1] < boardHeights[stretched.rightEnd + 1])) {
            stretched.rightEnd++;
            stretchedHeight = min(stretchedHeight, boardHeights[stretched.rightEnd]);
        } else {
            stretched.leftEnd--;
            stretchedHeight = min(stretchedHeight, boardHeights[stretched.leftEnd]);
        }

        maximumFenceSurface = max(maximumFenceSurface, stretchedHeight * (stretched.rightEnd - stretched.leftEnd + 1));
    }

    return maximumFenceSurface;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numBoard;

        cin >> numBoard;

        vector<int> boardHeights(numBoard);

        for (int &boardHeight : boardHeights) {
            cin >> boardHeight;
        }

        cout << findMaximumFenceSurface(boardHeights, {0, numBoard - 1}) << endl;
    }

    return 0;
}
