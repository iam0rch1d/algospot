#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int y;
    int x;
} Point;

class Piece {
public:
    Point difference[3]{};

    explicit Piece(int typeNo) {
        switch (typeNo) {
            case 0: {
                difference[0] = {0, 0};
                difference[1] = {0, 1};
                difference[2] = {1, 0};

                break;
            }
            case 1: {
                difference[0] = {0, 0};
                difference[1] = {0, 1};
                difference[2] = {1, 1};

                break;
            }
            case 2: {
                difference[0] = {0, 0};
                difference[1] = {1, 0};
                difference[2] = {1, -1};

                break;
            }
            default: {
                difference[0] = {0, 0};
                difference[1] = {1, 0};
                difference[2] = {1, 1};

                break;
            }
        }
    }
};

bool canCover(vector<vector<char>> &board, Point onPoint, Piece withPiece) {
    for (auto &difference : withPiece.difference) {
        Point toPlace = onPoint;

        toPlace.y += difference.y;
        toPlace.x += difference.x;

        if (toPlace.y < 0 || toPlace.y >= board.size() || toPlace.x < 0 || toPlace.x >= board[0].size()
            || board[toPlace.y][toPlace.x] == '#')
            return false;
    }

    return true;
}

void cover(vector<vector<char>> &board, Point onPoint, Piece withPiece, char pieceOf) {
    for (auto &difference : withPiece.difference) {
        Point toPlace = onPoint;

        toPlace.y += difference.y;
        toPlace.x += difference.x;

        board[toPlace.y][toPlace.x] = pieceOf;
    }
}

int backtrackCoveringCount(vector<vector<char>> &board) {
    Point toCover = {-1, -1};
    const int numPieceType = 4;
    int numCovering = 0;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == '.') {
                toCover = {i, j};

                break;
            }
        }

        if (toCover.y != -1) break;
    }

    if (toCover.y == -1) return 1;

    for (int i = 0; i < numPieceType; i++) {
        auto tempPiece = Piece(i);

        if (canCover(board, toCover, tempPiece)) {
            cover(board, toCover, tempPiece, '#');

            numCovering += backtrackCoveringCount(board);

            cover(board, toCover, tempPiece, '.');
        }
    }

    return numCovering;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int height;
        int width;
        string tempString;
        vector<vector<char>> board;

        cin >> height >> width;

        for (int i = 0; i < height; i++) {
            vector<char> tempCharVector;

            cin >> tempString;

            copy(tempString.begin(), tempString.end(), back_inserter(tempCharVector));
            board.push_back(tempCharVector);
        }

        cout << backtrackCoveringCount(board) << endl;
    }

    return 0;
}
