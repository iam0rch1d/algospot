#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> slice(const vector<int> &v, int begin, int end) {
    return vector<int>(v.begin() + begin, v.begin() + end);
}

void printPostorderTraversal(const vector<int> &preorderNodes, const vector<int> &inorderNodes) {
    const int preorderSize = preorderNodes.size();

    if (preorderSize == 0) return;

    const int rootNode = preorderNodes[0];
    const int leftSubtreeSize = find(inorderNodes.begin(), inorderNodes.end(), rootNode) - inorderNodes.begin();

    printPostorderTraversal(slice(preorderNodes, 1, leftSubtreeSize + 1),
                            slice(inorderNodes, 0, leftSubtreeSize));
    printPostorderTraversal(slice(preorderNodes, leftSubtreeSize + 1, preorderSize),
                            slice(inorderNodes, leftSubtreeSize + 1, preorderSize));

    cout << rootNode << " ";
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int numNode;

        cin >> numNode;

        vector<int> preorderNodes(numNode);
        vector<int> inorderNodes(numNode);

        for (int &node : preorderNodes) {
            cin >> node;
        }

        for (int &node : inorderNodes) {
            cin >> node;
        }

        printPostorderTraversal(preorderNodes, inorderNodes);
    }

    return 0;
}
