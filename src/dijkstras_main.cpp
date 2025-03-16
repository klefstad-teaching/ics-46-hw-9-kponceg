#include "dijkstras.h"
#include <vector>

int main(){
    Graph G{};
    file_to_graph("largest.txt", G);
    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, 3, previous);
    vector<int> shortest_path = extract_shortest_path(distances, previous, 7);
    print_path(shortest_path, distances[7]);
}