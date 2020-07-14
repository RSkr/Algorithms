#include <iostream>
#include <vector>

#define INF INT32_MAX
using namespace std;

bool noNegativeCycle = true;

struct Edge{
    int startPoint;
    int endPoint;
    int weight;
};

void createGraph(Edge* weightOfEdges, const int& edges){
    int sourceVertex, destinationVertex, weight;
    for(int i = 0; i < edges; i++){
        cin >> sourceVertex >> destinationVertex >> weight;
        weightOfEdges[i].startPoint = sourceVertex;
        weightOfEdges[i].endPoint = destinationVertex;
        weightOfEdges[i].weight = weight;
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

void BellmanFord(const int& vertices, const int& edges, Edge* weightOfEdges, vector<int>& valueOfShortestPath, vector<int>& shortestPath){
    for(int i = 0; i <= vertices - 1; i++){
        for(int j = 0; j < edges; j++){
            int startVertex = weightOfEdges[j].startPoint;
            int endVertex = weightOfEdges[j].endPoint;
            int weight = weightOfEdges[j].weight;
            if(valueOfShortestPath[startVertex] != INF && valueOfShortestPath[startVertex] + weight < valueOfShortestPath[endVertex]){
                valueOfShortestPath[endVertex] = valueOfShortestPath[startVertex] + weight;
                shortestPath[endVertex] = startVertex;
            }
        }
    }
    /// checking for negative path - without negative paths, there shouldn't be a "cheaper" path after above loop, so if we find one, then there exist negative cycle
    for(int j = 0; j < edges; j++){
        int startVertex = weightOfEdges[j].startPoint;
        int endVertex = weightOfEdges[j].endPoint;
        int weight = weightOfEdges[j].weight;
        if(valueOfShortestPath[startVertex] != INF && valueOfShortestPath[startVertex] + weight < valueOfShortestPath[endVertex]){
                noNegativeCycle = false;
        }

    }
}

void testcase(){
    int vertices;
    cin >> vertices;
    int edges;
    cin >> edges;

    Edge weightOfEdges[edges];
    createGraph(weightOfEdges, edges);

    vector<int> valueOfShortestPath(vertices,INF);
    vector<int> shortestPath(vertices,-1);

    int startingPoint;
    cin >> startingPoint;
    valueOfShortestPath[startingPoint] = 0;

    BellmanFord(vertices, edges, weightOfEdges, valueOfShortestPath, shortestPath);

    if(noNegativeCycle){
        cout << endl <<  "Distances from " << startingPoint << " to: " << endl;
        printShortestPath(valueOfShortestPath);
        cout << endl << "Predecessors:" << endl;
        printPredecessor(shortestPath);
        cout << endl;
        printPathToSelected(shortestPath, startingPoint);
    } else{
        cout << "Negative cycle exist" << endl;
    }

    
}

int main() {
    testcase();
    return 0;
}