#include <iostream>
#include <vector>

using namespace std;

int countPairings(int numStudent, vector<vector<bool>> &areFriends, vector<bool> &isPicked) {
    int indexFirstUnpicked = -1;
    int numPairings = 0;

    for (int i = 0; i < numStudent; i++) {
        if (!isPicked[i]) {
            indexFirstUnpicked = i;

            break;
        }
    }

    if (indexFirstUnpicked == -1) return 1; // Base case

    for (int i = indexFirstUnpicked + 1; i < numStudent; i++) {
        if (!isPicked[i] && areFriends[indexFirstUnpicked][i]) {
            isPicked[indexFirstUnpicked] = true;
            isPicked[i] = true;

            numPairings += countPairings(numStudent, areFriends, isPicked); // Recursion steps

            isPicked[indexFirstUnpicked] = false;
            isPicked[i] = false;
        }
    }

    return numPairings;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    for (int testcaseNo = 0; testcaseNo < numTestcase; testcaseNo++) {
        int numStudent;
        int numFriendPair;
        vector<bool> temp;
        vector<vector<bool>> areFriends;

        cin >> numStudent >> numFriendPair;

        temp.assign(numStudent, false);
        areFriends.assign(numStudent, temp);

        vector<bool> isPicked(temp);
        vector<vector<int>> friendPair(numFriendPair, {0, 0});

        for (int i = 0; i < numFriendPair; i++) {
            cin >> friendPair[i][0] >> friendPair[i][1];

            areFriends[friendPair[i][0]][friendPair[i][1]] = true;
            areFriends[friendPair[i][1]][friendPair[i][0]] = true;
        }

        cout << countPairings(numStudent, areFriends, isPicked) << "\n";
    }

    return 0;
}
