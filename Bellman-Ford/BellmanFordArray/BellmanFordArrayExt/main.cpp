#include <iostream>
#include <vector>

#define EMPTY INT32_MAX/4
#define INF INT32_MAX/6
#define IFEMPTY 999
using namespace std;

bool noNegativeCycle = true;

void createGraph(vector<vector<int>>& weightOfEdgesArray, const int& vertices){
    int weight;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            cin >> weight;
            if(weight != IFEMPTY)
                weightOfEdgesArray[i][j] = weight;
            else
                weightOfEdgesArray[i][j] = EMPTY;
        }
    }
}

/// Printing shortest path values
void printShortestPath(const vector<int>& valueOfShortestPath){
    for(int i = 0; i < valueOfShortestPath.size(); i++){
        if(valueOfShortestPath[i] == INF)
            cout <<"V: " << i << " -> N/A" << endl;
        else
            cout << "V: " << i << " -> "  << valueOfShortestPath[i] << endl;
    }
}

void printPredecessor(const vector<int>& shortestPath){
    for(int i = 0; i < shortestPath.size(); i++){
        if(shortestPath[i] == -1){
            cout << "V: " << i << " -> N/A "<< endl;
        } else
            cout << "V: " << i << " -> " << shortestPath[i] << endl;
    }
}
/*
void printPathToSelected(const vector<int>& shortestPath, const int& source){
    int vertexToFindPathFor, temp;
    cin >> vertexToFindPathFor;
    vector<int> pathToSelectedVertex;
    pathToSelectedVertex.push_back(vertexToFindPathFor);
    temp = vertexToFindPathFor;
    while(temp != source){
        temp = shortestPath[temp];
        pathToSelectedVertex.push_back(temp);
    }

    cout << "Path from " << source << " to " << vertexToFindPathFor << ": " << endl;
    for(int i = pathToSelectedVertex.size() - 1; i >= 0 ; i--){
        cout << pathToSelectedVertex[i] << " ";
    }
    cout << endl;
}
*/

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
    createGraph(weightOfEdgesArray, vertices);

    vector<int> valueOfShortestPath(vertices,INF);
    vector<int> shortestPath(vertices,-1);

    int startingPoint;
    cin >> startingPoint;
    valueOfShortestPath[startingPoint] = 0;

    BellmanFord(vertices, weightOfEdgesArray, valueOfShortestPath, shortestPath);

    if(noNegativeCycle){
        cout << endl <<  "Distances from " << startingPoint << " to: " << endl;
        printShortestPath(valueOfShortestPath);
        cout << endl << "Predecessors:" << endl;
        printPredecessor(shortestPath);
        cout << endl;
        //printPathToSelected(shortestPath, startingPoint);
    } else{
        cout << "Negative cycle exist" << endl;
    }
    
}

int main() {
    testcase();
    return 0;
}