#include <iostream>
#include <vector>

using namespace std;

#define MINIMUM_KARATSUBA_A_SIZE 50

void normalize(vector<int> &number) {
    number.push_back(0);

    for (int i = 0; i < number.size() - 1; i++) {
        if (number[i] < 0) {
            int borrow = (abs(number[i]) + 9) / 10;

            number[i + 1] -= borrow;
            number[i] += borrow * 10;
        } else {
            number[i + 1] += number[i] / 10;
            number[i] %= 10;
        }
    }

    while(number.size() > 1 && number.back() == 0) {
        number.pop_back();
    }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    vector<int> multiplication(a.size() + b.size() + 1, 0);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            multiplication[i + j] += a[i] * b[j];
        }
    }

    normalize(multiplication);

    return multiplication;
}

void add(vector<int> &to, vector<int> &howMuch, int howMuchExponent) {
    int howMuchSize = howMuch.size();

    if (to.size() < howMuch.size() + howMuchExponent) to.resize(howMuch.size() + howMuchExponent);

    for (int i = 0; i < howMuchSize; i++) {
        to[howMuchExponent + i] += howMuch[i];
    }

    normalize(to);
}

void subtract(vector<int> &from, vector<int> &howMuch) {
    int howMuchSize = howMuch.size();

    for (int i = 0; i < howMuchSize; i++) {
        from[i] -= howMuch[i];
    }

    normalize(from);
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
    string aString;
    string bString;
    vector<int> a;
    vector<int> b;
    vector<int> multiplication;

    cin >> aString >> bString;

    for (char &aChar : aString) {
        a.insert(a.begin(), aChar - '0');
    }

    for (char &bChar : bString) {
        b.insert(b.begin(), bChar - '0');
    }

    multiplication = multiplyKaratsuba(a, b);

    for (int &multiplicationInt : multiplication) {
        cout << multiplicationInt << " ";
    }

    return 0;
}
