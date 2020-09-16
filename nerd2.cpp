#include <iostream>
#include <map>

using namespace std;

map<int, int> nerds;

bool isFake(pair<int, int> toInsertPerson) {
    auto nerdsLowerBound = nerds.lower_bound(toInsertPerson.first);

    if (nerdsLowerBound == nerds.end()) return false;

    return toInsertPerson.second < nerdsLowerBound->second;
}

void removeFake(pair<int, int> toInsertPerson) {
    auto head = nerds.lower_bound(toInsertPerson.first);

    if (head == nerds.begin()) return;

    head--;

    while (true) {
        if (head->second > toInsertPerson.second) break;

        if (head == nerds.begin()) {
            nerds.erase(head);

            break;
        }

        auto temp = head;

        temp--;

        nerds.erase(head);

        head = temp;
    }
}

int calculateNerdCount(pair<int, int> toInsertPerson) {
    if (isFake(toInsertPerson)) return nerds.size();

    removeFake(toInsertPerson);

    nerds[toInsertPerson.first] = toInsertPerson.second;

    return nerds.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int numTestcase;

    scanf("%d", &numTestcase);

    while (numTestcase-- > 0) {
        int numParticipant;
        int totalNerdCount = 0;

        scanf("%d", &numParticipant);

        while (numParticipant-- > 0) {
            pair<int, int> person;  // .first = <problems solved>, .second = <ramens eaten>

            scanf("%d%d", &person.first, &person.second);

            totalNerdCount += calculateNerdCount(person);
        }

        printf("%d\n", totalNerdCount);
        nerds.clear();
    }

    return 0;
}
