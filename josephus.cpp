#include <iostream>
#include <queue>

using namespace std;

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numSoldier;
        int toSuicide;
        queue<int> soldiers;

        cin >> numSoldier >> toSuicide;

        for (int i = 1; i <= numSoldier; i++) {
            soldiers.push(i);
        }

        while (numSoldier-- > 2) {
            soldiers.pop();

            for (int i = 0; i < toSuicide - 1; i++) {
                int temp = soldiers.front();

                soldiers.pop();
                soldiers.push(temp);
            }
        }

        cout << min(soldiers.front(), soldiers.back()) << " " << max(soldiers.front(), soldiers.back()) << endl;
    }

    return 0;
}
