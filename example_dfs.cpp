#include <iostream>
#include <vector>

using namespace std;

bool hasVisited[1000];
vector<int> adjacentVertexes[1000];

void dfs(int currentVertex) {
    hasVisited[currentVertex] = true;

    cout << "DFS visits " << currentVertex << endl;

    for (int adjacentVertex : adjacentVertexes[currentVertex]) {
        if (!hasVisited[adjacentVertex]) dfs(adjacentVertex);
    }
}

int main() {
    int numEdge;

    cin >> numEdge;

    for (int i = 0; i < numEdge; i++) {
        int fromVertex;
        int toVertex;

        cin >> fromVertex >> toVertex;

        adjacentVertexes[fromVertex].push_back(toVertex);
        adjacentVertexes[toVertex].push_back(fromVertex);
    }

    dfs(0);

    return 0;
}
