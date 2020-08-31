#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum CanMatchState {
    UNMATCHED = -1,
    FALSE,
    TRUE
};

int dpCanMatch(const string &pattern,
               const string &fileName,
               vector<vector<int>> &canMatchCache,
               int patternCharNo,
               int fileNameCharNo) {
    int &canMatch = canMatchCache[patternCharNo][fileNameCharNo];

    if (canMatch != UNMATCHED) return canMatch;

    if (patternCharNo < pattern.size()
    && fileNameCharNo < fileName.size()
    && (pattern[patternCharNo] == '?' || pattern[patternCharNo] == fileName[fileNameCharNo])) {
        return canMatch = dpCanMatch(pattern, fileName, canMatchCache, patternCharNo + 1, fileNameCharNo + 1);
    }

    if (patternCharNo == pattern.size()) return canMatch = ((fileNameCharNo == fileName.size()) ? TRUE : FALSE);

    if (pattern[patternCharNo] == '*'
    && (dpCanMatch(pattern, fileName, canMatchCache, patternCharNo + 1, fileNameCharNo) == TRUE
    || (fileNameCharNo < fileName.size()
    && dpCanMatch(pattern, fileName, canMatchCache, patternCharNo, fileNameCharNo + 1) == TRUE))) {
        return canMatch = TRUE;
    }

    return canMatch = FALSE;
}

int main() {
    int numTestcase;

    cin >> numTestcase;

    while (numTestcase-- > 0) {
        string pattern;
        int numFile;
        vector<string> matches;

        cin >> pattern >> numFile;

        while (numFile-- > 0) {
            string fileName;

            cin >> fileName;

            vector<vector<int>> canMatchCache(pattern.size() + 1, vector<int>(fileName.size() + 1, UNMATCHED));

            if (dpCanMatch(pattern, fileName, canMatchCache, 0, 0)) matches.push_back(fileName);
        }

        sort(matches.begin(), matches.end(), [](string &i, string &j) { return i.compare(j) < 0; });

        for (string &match : matches) {
            cout << match << endl;
        }
    }

    return 0;
}
