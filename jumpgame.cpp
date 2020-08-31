#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int y;
    int x;
} Point;

int dpCanJump(vector<vector<int>> &jumpDistances, vector<vector<int>> &canJumpCache, Point at) {
    int boardSize = jumpDistances.size();

    if (at.y >= boardSize || at.x >= boardSize) return 0;

    if (at.y == boardSize - 1 && at.x == boardSize - 1) return 1;

    int &canJump = canJumpCache[at.y][at.x];

    if (canJump != -1) return canJump == 1;

    int jumpDistance = jumpDistances[at.y][at.x];

    return canJump = dpCanJump(jumpDistances, canJumpCache, {at.y + jumpDistance, at.x})
    || dpCanJump(jumpDistances, canJumpCache, {at.y, at.x + jumpDistance});
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int boardSize;

        cin >> boardSize;

        vector<vector<int>> jumpDistances(boardSize, vector<int>(boardSize));
        vector<vector<int>> canJumpCache(boardSize, vector<int>(boardSize, -1));

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                cin >> jumpDistances[i][j];
            }
        }

        cout << (dpCanJump(jumpDistances, canJumpCache, {0, 0}) == 1 ? "YES" : "NO") << endl;
    }

    return 0;
}
