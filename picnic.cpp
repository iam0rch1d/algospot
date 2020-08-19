#include <iostream>
#include <vector>

using namespace std;

int backtrackPairingCount(vector<vector<bool>> &friendPairGraph, vector<bool> &isPicked) {
    int numStudent = friendPairGraph.size();
    int indexFirstUnpicked = -1;
    int numPairing = 0;

    for (int i = 0; i < numStudent; i++) {
        if (!isPicked[i]) {
            indexFirstUnpicked = i;

            break;
        }
    }

    if (indexFirstUnpicked == -1) return 1;

    for (int i = indexFirstUnpicked + 1; i < numStudent; i++) {
        if (friendPairGraph[indexFirstUnpicked][i] && !isPicked[i]) {
            isPicked[indexFirstUnpicked] = true;
            isPicked[i] = true;

            numPairing += backtrackPairingCount(friendPairGraph, isPicked);

            isPicked[indexFirstUnpicked] = false;
            isPicked[i] = false;
        }
    }

    return numPairing;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    for (int testcaseNo = 0; testcaseNo < numTestcase; testcaseNo++) {
        int numStudent;
        int numFriendPair;
        vector<bool> tempBoolVector;
        vector<vector<bool>> friendPairGraph;

        cin >> numStudent >> numFriendPair;

        tempBoolVector.assign(numStudent, false);
        friendPairGraph.assign(numStudent, tempBoolVector);

        vector<bool> isPicked(tempBoolVector);
        vector<vector<int>> friendPair(numFriendPair, {0, 0});

        for (int i = 0; i < numFriendPair; i++) {
            cin >> friendPair[i][0] >> friendPair[i][1];

            friendPairGraph[friendPair[i][0]][friendPair[i][1]] = true;
            friendPairGraph[friendPair[i][1]][friendPair[i][0]] = true;
        }

        cout << backtrackPairingCount(friendPairGraph, isPicked) << endl;
    }

    return 0;
}
