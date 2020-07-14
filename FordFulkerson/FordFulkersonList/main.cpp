#include <iostream>
#include <vector>
#include <queue>

#define INF INT32_MAX

using namespace std;

struct Edge{
    int startVertex;
    int endVertex;
    int capacity;
    int flow;
    int residualFlow;
};

struct VertexNeighbours{
    vector<int> inVertices;
    vector<int> outVertices;
};

void fillGraph(vector<Edge>& graph, vector<VertexNeighbours>& vertexNeighbours, const int& edges){
    int startPoint, endPoint, weightEdge;
    for(int i = 0; i < edges; i++){
        cin >> startPoint >> endPoint >> weightEdge;
        graph[i].startVertex = startPoint;
        graph[i].endVertex = endPoint;
        graph[i].capacity =  weightEdge;
        graph[i].flow = 0;
        graph[i].residualFlow = 0;

        vertexNeighbours[startPoint].inVertices.push_back(endPoint);
        vertexNeighbours[endPoint].outVertices.push_back(startPoint);
    }
}


bool BFS(vector<Edge>& graph, vector<vector<int>>& residualGraph, vector<VertexNeighbours>& vertexNeighbours, const int& vertices,const int& startPoint, const int& endPoint, vector<int>& pathOfBFS){
    vector<bool> visited(vertices, false);
    queue<int> pathBFS;
    pathBFS.push(startPoint);
    visited[startPoint] = true;
    pathOfBFS[startPoint] = -1;

    while(!pathBFS.empty()){
        int currentNode = pathBFS.front();
        pathBFS.pop();

        for(int nextNode : vertexNeighbours[currentNode].inVertices) {
            if( visited[nextNode] == false && residualGraph[currentNode][nextNode] > 0){
                pathBFS.push(nextNode);
                pathOfBFS[nextNode] = currentNode;
                visited[nextNode] = true;
            }
        }
        for(int nextNode : vertexNeighbours[currentNode].outVertices) {
            if( visited[nextNode] == false && residualGraph[currentNode][nextNode] > 0){
                pathBFS.push(nextNode);
                pathOfBFS[nextNode] = currentNode;
                visited[nextNode] = true;
            }
        }

    }
    bool endPointReached = visited[endPoint];
    return endPointReached;
}

int FordFulkerson(const int& vertices, vector<Edge>& graph, vector<VertexNeighbours>& vertexNeighbours, const int& startVertex, const int& endVertex){
    int u, v;
    int maxFlow = 0;

    vector< vector<int>> residualGraph(vertices, vector<int> (vertices, 0));
    for(int i = 0; i < graph.size(); i++){
        residualGraph[graph[i].startVertex][graph[i].endVertex] = graph[i].capacity;
    }
    vector<int> pathOfBFS(vertices, 0);


    while(BFS(graph, residualGraph, vertexNeighbours, vertices, startVertex, endVertex,pathOfBFS)){
        int flowInPath = INF;
        /// find minimal flow in path
        for(v = endVertex; v != startVertex; v = pathOfBFS[v]){
            u = pathOfBFS[v];
            flowInPath = min(flowInPath, residualGraph[u][v]);
        }
        ///update residual flow
        for(v = endVertex; v != startVertex; v = pathOfBFS[v]){
            u = pathOfBFS[v];
            residualGraph[u][v] -= flowInPath;
            residualGraph[v][u] += flowInPath;
        }
        maxFlow += flowInPath;

    }
    for(int i = 0; i < graph.size(); i++){
        int flowValue = graph[i].capacity - residualGraph[graph[i].startVertex][graph[i].endVertex];
        if(flowValue > 0){
            cout << graph[i].startVertex << " " << graph[i].endVertex << " " << flowValue << endl;
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


    vector<Edge> graph(edges);
    vector<VertexNeighbours> vertexNeighbours (vertices);
    ///filling graph with given values and edges
    fillGraph(graph, vertexNeighbours, edges);

    cin >> startVertex >> endVertex;
    /// Running algorithm to find maximum flow and printing max flow
    cout << FordFulkerson(vertices, graph, vertexNeighbours, startVertex, endVertex) << endl;
}

int main() {
    testcase();
    return 0;
}
