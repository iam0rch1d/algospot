#include <iostream>
#include <stack>

using namespace std;

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        string bracketString;
        stack<char> bracketStack;
        bool isMatching = true;

        cin >> bracketString;

        for (char i : bracketString) {
            switch (i) {
                case '(': {
                    bracketStack.push('(');

                    break;
                }
                case '{': {
                    bracketStack.push('{');

                    break;
                }
                case '[': {
                    bracketStack.push('[');

                    break;
                }
                case ')': {
                    if (bracketStack.empty() || bracketStack.top() != '(') {
                        isMatching = false;

                        break;
                    }

                    bracketStack.pop();

                    break;
                }
                case '}': {
                    if (bracketStack.empty() || bracketStack.top() != '{') {
                        isMatching = false;

                        break;
                    }

                    bracketStack.pop();

                    break;
                }
                default: {
                    if (bracketStack.empty() || bracketStack.top() != '[') {
                        isMatching = false;

                        break;
                    }

                    bracketStack.pop();

                    break;
                }
            }

            if (!isMatching) break;
        }

        cout << (bracketStack.empty() && isMatching ? "YES" : "NO") << endl;
    }

    return 0;
}
