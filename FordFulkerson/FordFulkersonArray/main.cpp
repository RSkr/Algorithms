#include <iostream>
#include <vector>
#include <queue>

#define INF INT32_MAX

using namespace std;

/// filling capacity values from given input
void fillGraph(vector<vector<int>>& graph, const int& edges){
    int startPoint, endPoint, capacity;
    for(int i = 0; i < edges; i++){
        cin >> startPoint >> endPoint >> capacity;
        graph[startPoint][endPoint] = capacity;
    }
}


/// bfs function to search for path from starting vertex to end vertex
bool BFS(vector<vector<int>>& residualGraph, const int& vertices,const int& startPoint, const int& endPoint, vector<int>& pathOfBFS){
    vector<bool> visited(vertices, false);
    queue<int> pathBFS;
    pathBFS.push(startPoint);
    visited[startPoint] = true;
    pathOfBFS[startPoint] = -1;

    while(!pathBFS.empty()){
        int currentNode = pathBFS.front();
        pathBFS.pop();

        for(int nextNode = 0; nextNode < vertices; nextNode++) {
            if(visited[nextNode] == false && residualGraph[currentNode][nextNode] > 0){
                pathBFS.push(nextNode);
                pathOfBFS[nextNode] = currentNode;
                visited[nextNode] = true;
            }
        }
    }
    bool endPointReached = visited[endPoint];
    return endPointReached;
}

int FordFulkerson(const int& vertices, vector<vector<int>>& graph, const int& startVertex, const int& endVertex){
    int u, v;
    int maxFlow = 0;

    vector< vector<int>> residualGraph(vertices, vector<int> (vertices));
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            residualGraph[i][j] = graph[i][j];
        }
    }

    vector<int> pathOfBFS(vertices, 0);

    while(BFS(residualGraph, vertices, startVertex, endVertex,pathOfBFS)){
        int flowInPath = INF;
        /// find minimal flow in path
        for(v = endVertex; v != startVertex; v = pathOfBFS[v]){
            u = pathOfBFS[v];
            flowInPath = min(flowInPath, residualGraph[u][v]);
        }
        ///update capacites
        for(int v = endVertex; v != startVertex; v = pathOfBFS[v]){
            u = pathOfBFS[v];
            residualGraph[u][v] -= flowInPath;
            residualGraph[v][u] += flowInPath;
        }

        maxFlow += flowInPath;

    }
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            int flowValue = graph[i][j] - residualGraph[i][j];
            if(flowValue > 0){
                cout << i << " " << j << " " << flowValue << endl;
            }
        }
    }
    return maxFlow;
}



void testcase(){
    int vertices;
    cin >> vertices;
    int edges;
    cin >> edges;
    int startVertex, endVertex;

    /// create array for edges capacity in normal graph, setting all values to 0
    vector< vector<int>> graph(vertices, vector<int> (vertices,0));
    ///fillig graph with given values and edges
    fillGraph(graph, edges);

    cin >> startVertex >> endVertex;
    /// Running algorithm to find maximum flow and printing max flow
    cout << FordFulkerson(vertices, graph, startVertex, endVertex) << endl;


}

int main() {
    testcase();
    return 0;
}
