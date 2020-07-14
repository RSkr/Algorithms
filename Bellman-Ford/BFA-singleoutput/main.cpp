#include <iostream>
#include <vector>

#define EMPTY INT32_MAX/4
#define INF INT32_MAX/6
using namespace std;

bool noNegativeCycle = true;

void createGraph(vector<vector<int>>& weightOfEdgesArray){
    int edges, sourceVertex, destinationVertex, weight;
    /// getting number of edges in graph
    cin >> edges;
    /// getting edges and their weight
    for(int i = 0; i < edges; i++){
        cin >> sourceVertex >> destinationVertex >> weight;
        weightOfEdgesArray[sourceVertex][destinationVertex] = weight;
    }
}

/// Printing shortest path values
void printShortestPath(const vector<int>& valueOfShortestPath){
    for(int i = 0; i < valueOfShortestPath.size(); i++){
        if(valueOfShortestPath[i] == INF)
            cout << "N/A ";
        else
            cout << valueOfShortestPath[i] << " ";
    }
    cout << endl;
}

void printPredecessor(const vector<int>& shortestPath){
    for(int i = 0; i < shortestPath.size(); i++){
        cout << shortestPath[i] << " ";
    }
    cout << endl;
}


void BellmanFord(const int& vertices, vector< vector<int>>& weightOfEdgesArray, vector<int>& valueOfShortestPath, vector<int>& shortestPath){
    for(int i = 0; i <= vertices - 1; i++){
        for(int u = 0; u < vertices; u++){
            for(int v = 0; v < vertices; v++){
                if(weightOfEdgesArray[u][v] == EMPTY)
                    continue;
                if(valueOfShortestPath[u] != INF && valueOfShortestPath[u] + weightOfEdgesArray[u][v] < valueOfShortestPath[v]){
                    valueOfShortestPath[v] = valueOfShortestPath[u] + weightOfEdgesArray[u][v];
                    shortestPath[v] = u;
                }
            }
        }
    }
    /// checking for negative path - without negative paths, there shouldn't be a "cheaper" path after above loop, so if we find one, then there exist negative cycle
    for(int u = 0; u < vertices; u++){
        for(int v = 0; v < vertices; v++){
            if(weightOfEdgesArray[u][v] == EMPTY)
                continue;
            if(valueOfShortestPath[u] != INF && valueOfShortestPath[u] + weightOfEdgesArray[u][v] < valueOfShortestPath[v]){
                noNegativeCycle = false;
            }
        }
    }
}

void testcase(){
    int vertices;
    cin >> vertices;
    vector< vector<int>> weightOfEdgesArray (vertices, vector<int> (vertices, EMPTY)); //
    createGraph(weightOfEdgesArray);

    vector<int> valueOfShortestPath(vertices,INF);
    vector<int> shortestPath(vertices,-1);

    int startingPoint;
    cin >> startingPoint;
    valueOfShortestPath[startingPoint] = 0;

    BellmanFord(vertices, weightOfEdgesArray, valueOfShortestPath, shortestPath);

    if(noNegativeCycle){
        printShortestPath(valueOfShortestPath);
        printPredecessor(shortestPath);
        cout << endl;
    } else{
        cout << "Negative cycle exist" << endl;
    }

}

int main() {
    testcase();
    return 0;
}