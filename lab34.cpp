#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

const int SIZE = 13;

// real world application is a package delivery network
// nodes are facilities
// weights are travel time between facilities

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

const string FACILITY_NAMES[SIZE] = {
    "Central Distribution Center",   // 0
    "Legacy Hub (Inactive)",         // 1 - no roads attached
    "North Warehouse",               // 2
    "East Warehouse",                // 3
    "South Hub",                     // 4
    "West Hub",                      // 5
    "Decommissioned Facility",       // 6 - no roads attached
    "Regional Airport",              // 7
    "Port Terminal",                 // 8
    "Downtown Micro-Hub",            // 9
    "Cross-Docking Center",          // 10
    "Retail Consolidation Center",   // 11
    "Outlet Cluster"                 // 12
};

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
        cout << "Package Delivery Network Topology:" << endl;
        cout << "==================================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            if(adjList[i].empty()){
                continue;
            }

            cout << "Facility " << i << " (" << FACILITY_NAMES[i] << ") connects to:\n";
            for (Pair v : adjList[i]){
                cout << "  \u2192 Facility " << v.first
                     << " (" << FACILITY_NAMES[v.first]
                     << ") - Travel Time: " << v.second << " minutes\n";
            }
        }
        cout << endl;
    }

    // depth first search 
    void DFSUtil(int v, vector<bool> &visited){
        visited[v] = true;
        cout << "Inspecting Facility " << v << " (" << FACILITY_NAMES[v] << ")\n";

        for(auto &neighbor : adjList[v]){
            int dest = neighbor.first;
            int time = neighbor.second;
            if(!visited[dest]){
                cout << "  \u2192 Possible route to Facility " << dest
                     << " (" << FACILITY_NAMES[dest]
                     << ") - Travel Time: " << time << " minutes\n";
                DFSUtil(dest, visited);
            }
        }
    }

    void DFS(int start){
        vector<bool> visited(SIZE, false);
        cout << "Route Trace (DFS) from Facility " << start
             << " (" << FACILITY_NAMES[start] << "):" << endl;
        cout << "Purpose: Exploring deep delivery routes through the network" << endl;
        cout << "=========================================================" << endl;
        DFSUtil(start,visited);
        cout << endl;
    }

    // breadth first search
    void BFS(int start){
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Layer-by-Layer Delivery Coverage (BFS) from Facility " << start
             << " (" << FACILITY_NAMES[start] << "):" << endl;
        cout << "Purpose: Checking which areas are serviced in each hop" << endl;
        cout << "======================================================" << endl;

        while(!q.empty()){
            int v = q.front();
            q.pop();
            cout << "Checking Facility " << v << " (" << FACILITY_NAMES[v] << ")\n";

            for (auto &neighbor : adjList[v]){
                int dest = neighbor.first;
                if(!visited[dest]){
                    visited[dest] = true;
                    q.push(dest);
                     cout << "  \u2192 Next delivery stop: Facility " << dest
                         << " (" << FACILITY_NAMES[dest]
                         << ") - Travel Time: " << time << " minutes\n";
                }
            }
        }

        cout << endl;
    }

    // shortest path djikstra
    void shortestPath(int start){
        vector<int> dist(SIZE, INT_MAX);
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while(!pq.empty()){
            auto [d, u] = pq.top();
            pq.pop();
            
            if(d > dist[u]) continue;

            for(auto &edge : adjList[u]){
                int v = edge.first;
                int w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nShortest path from node " << start << ":\n";
        for (int v = 0; v < SIZE; v++) {
            if (dist[v] != INT_MAX) {
                cout << start << " -> " << v << " : " << dist[v] << endl;
            }
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // deleted nodes 1 and 6
        // adding six new nodes, 7 8 9 10 11 12
        {0,2,31},{0,3,19},{2,3,16},{4,5,13},{2,4,28},{2,5,5},{5,7,12},{4,7,12},{7,8,13},{7,9,7},{8,9,12},{8,10,13},{7,10,21},{10,11,11},{8,11,50},{11,12,18},{7,12,15}
    };

    // Creates graph
    Graph graph(edges);

    cout << "=== Logistics Routing Application ===" << endl;
    cout << "Nodes represent logistics facilities; edges represent delivery routes\n"
         << "with travel times in minutes.\n\n";


    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    graph.shortestPath(0);

    return 0;
}

