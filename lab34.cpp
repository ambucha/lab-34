#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // depth first search
    void DFSUtil(int v, vector<bool> &visited){
        visited[v] = true;
        cout << v << " ";

        for(auto &neighbor : adjList[v]){
            int dest = neighbor.first;
            if(!visited[dest])
                DFSUtil(dest, visited);
        }
    }

    void DFS(int start){
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << start << ":" << endl;
        DFSUtil(start,visited);
        cout << endl;
    }

    // breadth first search
    void BFS(int start){
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while(!q.empty()){
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v]){
                int dest = neighbor.first;
                if(!visited[dest]){
                    visited[dest] = true;
                    q.push(dest);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // deleted nodes 1 and 6
        // adding six new nodes, 7 8 9 10 11 12
        {0,2,31},{0,3,19},{2,3,6},{4,5,13},{2,4,3},{2,5,5},{5,7,12},{4,7,2},{7,8,13},{7,9,7},{8,9,1},{8,10,13},{7,10,2},{10,11,11},{8,11,5},{11,12,8},{7,12,15}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}

