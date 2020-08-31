#include <iostream>

using namespace std;

string reverseQuadtree(string::iterator &head) {
    char headChar = *head++;

    if (headChar == 'b' || headChar == 'w') return string(1, headChar);

    string upperLeftDivision = reverseQuadtree(head);
    string upperRightDivision = reverseQuadtree(head);
    string lowerLeftDivision = reverseQuadtree(head);
    string lowerRightDivision = reverseQuadtree(head);

    return string("x") + lowerLeftDivision + lowerRightDivision + upperLeftDivision + upperRightDivision;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        string quadtree;
        string::iterator quadtreeBegin;

        cin >> quadtree;

        quadtreeBegin = quadtree.begin();

        cout << reverseQuadtree(quadtreeBegin) << endl;
    }

    return 0;
}
