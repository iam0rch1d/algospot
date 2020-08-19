#include <iostream>

using namespace std;

string reverseQuadtree(string::iterator &i) {
    char head = *i;

    i++;

    // Base case
    if (head == 'b' || head == 'w') return string(1, head);

    // Divide
    string upperLeftDivision = reverseQuadtree(i);
    string upperRightDivision = reverseQuadtree(i);
    string lowerLeftDivision = reverseQuadtree(i);
    string lowerRightDivision = reverseQuadtree(i);

    // Merge
    return string("x") + lowerLeftDivision + lowerRightDivision + upperLeftDivision + upperRightDivision;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    for (int testcaseNo = 0; testcaseNo < numTestcase; testcaseNo++) {
        string quadtree;
        string::iterator quadtreeBegin;

        cin >> quadtree;

        quadtreeBegin = quadtree.begin();

        cout << reverseQuadtree(quadtreeBegin) << endl;
    }

    return 0;
}
