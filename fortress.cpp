#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Label {
    int x;
    int y;
    int radius;
};

struct TreeNode {
    vector<TreeNode *> children;
};

int numNode;
Label nodeLabels[100];
int longestPathLength;

int calculateCenterDistanceSquare(int a, int b) {
    return (nodeLabels[a].x - nodeLabels[b].x) * (nodeLabels[a].x - nodeLabels[b].x)
           + (nodeLabels[a].y - nodeLabels[b].y) * (nodeLabels[a].y - nodeLabels[b].y);
}

int calculateRadiusDifferenceSquare(int a, int b) {
    return (nodeLabels[a].radius - nodeLabels[b].radius) * (nodeLabels[a].radius - nodeLabels[b].radius);
}

bool isEnclosing(int a, int b) {
    return nodeLabels[a].radius > nodeLabels[b].radius
           && calculateCenterDistanceSquare(a, b) < calculateRadiusDifferenceSquare(a, b);
}

bool isChild(int parent, int child) {
    if (!isEnclosing(parent, child)) return false;

    for (int i = 0; i < numNode; i++) {
        if (i != parent && i != child && isEnclosing(parent, i) && isEnclosing(i, child)) return false;
    }

    return true;
}

TreeNode *buildTree(int root) {
    auto *tree = new TreeNode();

    for (int i = 0; i < numNode; i++) {
        if (isChild(root, i)) tree->children.push_back(buildTree(i));
    }

    return tree;
}

int calculateHeight(TreeNode *root) {
    vector<int> heights;

    for (auto &child : root->children) {
        heights.push_back(calculateHeight(child));
    }

    if (heights.empty()) return 0;

    sort(heights.begin(), heights.end(), [](int i, int j) { return i > j; });

    if (heights.size() >= 2) longestPathLength = max(longestPathLength, heights[0] + heights[1] + 2);

    return heights[0] + 1;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        int height;

        cin >> numNode;

        for (int i = 0; i < numNode; i++) {
            cin >> nodeLabels[i].x >> nodeLabels[i].y >> nodeLabels[i].radius;
        }

        TreeNode *tree = buildTree(0);

        longestPathLength = 0;
        height = calculateHeight(tree);

        cout << max(longestPathLength, height) << endl;
    }

    return 0;
}
