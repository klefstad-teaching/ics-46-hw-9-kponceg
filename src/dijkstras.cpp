#include "dijkstras.h"
#include <algorithm>
#include <queue>

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int, int>> pq_vertex;
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
    return extract_shortest_path(distances, previous, )
}