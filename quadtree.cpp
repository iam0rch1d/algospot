#include <iostream>

using namespace std;

string reverseQuadtree(string::iterator &i) {
    char head = *i;

    i++;

    if (head == 'b' || head == 'w') return string(1, head);

    string upperLeftDivision = reverseQuadtree(i);
    string upperRightDivision = reverseQuadtree(i);
    string lowerLeftDivision = reverseQuadtree(i);
    string lowerRightDivision = reverseQuadtree(i);

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
