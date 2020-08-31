#include <algorithm>
#include <iostream>
#include <vector>

#define MINIMUM_KARATSUBA_A_SIZE 50

using namespace std;

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    vector<int> multiplication(a.size() + b.size() + 1, 0);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            multiplication[i + j] += a[i] * b[j];
        }
    }

    return multiplication;
}

void add(vector<int> &to, vector<int> &howMuch, int howMuchExponent) {
    int howMuchSize = howMuch.size();

    if (to.size() < howMuch.size() + howMuchExponent) to.resize(howMuch.size() + howMuchExponent);

    for (int i = 0; i < howMuchSize; i++) {
        to[howMuchExponent + i] += howMuch[i];
    }
}

void subtract(vector<int> &from, vector<int> &howMuch) {
    int howMuchSize = howMuch.size();

    for (int i = 0; i < howMuchSize; i++) {
        from[i] -= howMuch[i];
    }
}

vector<int> multiplyKaratsuba(const vector<int> &a, const vector<int> &b) {
    int aSize = a.size();
    int bSize = b.size();

    if (aSize < bSize) return multiplyKaratsuba(b, a);

    if (aSize == 0 || bSize == 0) return vector<int>();

    if (aSize < MINIMUM_KARATSUBA_A_SIZE) return multiply(a, b);

    int aNumberHalfSize = aSize / 2;

    vector<int> aDivision0(a.begin(), a.begin() + aNumberHalfSize);
    vector<int> aDivision1(a.begin() + aNumberHalfSize, a.end());
    vector<int> bDivision0(b.begin(), b.begin() + min<int>(bSize, aNumberHalfSize));
    vector<int> bDivision1(b.begin() + min<int>(bSize, aNumberHalfSize), b.end());
    vector<int> karatsubaFactor0 = multiplyKaratsuba(aDivision0, bDivision0);
    vector<int> karatsubaFactor2 = multiplyKaratsuba(aDivision1, bDivision1);

    add(aDivision0, aDivision1, 0);
    add(bDivision0, bDivision1, 0);

    vector<int> karatsubaFactor1 = multiplyKaratsuba(aDivision0, bDivision0);

    subtract(karatsubaFactor1, karatsubaFactor0);
    subtract(karatsubaFactor1, karatsubaFactor2);

    vector<int> multiplication;

    add(multiplication, karatsubaFactor0, 0);
    add(multiplication, karatsubaFactor1, aNumberHalfSize);
    add(multiplication, karatsubaFactor2, aNumberHalfSize + aNumberHalfSize);

    return multiplication;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        string idols;
        string fans;
        vector<int> idolGenders;
        vector<int> fanGenders;
        vector<int> handshakes;
        int idolsSize;
        int fansSize;
        int numAllHug = 0;

        cin >> idols >> fans;

        for (string::iterator i = idols.begin(); i < idols.end(); i++) {
            if (*i == 'M') idolGenders.push_back(1);
            else idolGenders.push_back(0);
        }

        for (string::iterator i = fans.begin(); i < fans.end(); i++) {
            if (*i == 'M') fanGenders.push_back(1);
            else fanGenders.push_back(0);
        }

        idolsSize = idols.size();
        fansSize = fans.size();

        reverse(fanGenders.begin(), fanGenders.end());

        handshakes = multiplyKaratsuba(idolGenders, fanGenders);

        for (int i = idolsSize - 1; i < fansSize; i++) {
            if (handshakes[i] == 0) numAllHug++;
        }

        cout << numAllHug << endl;
    }

    return 0;
}
