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