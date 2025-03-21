#include "dijkstras.h"
#include <algorithm>
#include <queue>
#include <vector>


vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> shortest_path;
    int current = destination;
    while (current != -1){
        shortest_path.push_back(current);
        current = previous[current];
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq_vertex;
    pq_vertex.push({source, 0});
    while (!pq_vertex.empty()){
        int u_vertex = pq_vertex.top().first;
        pq_vertex.pop();
        visited[u_vertex] = true;
        for (Edge e: G[u_vertex]){
            int v_vertex = e.dst;
            int weight = e.weight;
            if (!visited[v_vertex] && distances[u_vertex] + weight < distances[v_vertex]){
                distances[v_vertex] = distances[u_vertex] + weight;
                previous[v_vertex] = u_vertex;
                pq_vertex.push({v_vertex, distances[v_vertex]});
            }
        }
    }
    return distances;
}

void print_path(const vector<int>& v, int total){
    if (total == INF){cout << "No path found." << endl; return;}
    for (auto vertex: v){
        cout << vertex << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}