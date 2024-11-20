#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Compare function for sorting edges by weight
bool compareEdge(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

// Disjoint set structure
struct DisjointSet {
    vector<int> parent, rank;

    // Initialize the disjoint set
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Find the root of a set
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    // Union of two sets
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Kruskal's Algorithm
void kruskalMST(int vertices, vector<Edge> &edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdge);

    // Initialize disjoint set
    DisjointSet ds(vertices);

    vector<Edge> mst; // Store MST edges
    int mstWeight = 0;

    for (const auto &edge : edges) {
        int u = edge.src;
        int v = edge.dest;

        // Check if the edge forms a cycle
        if (ds.find(u) != ds.find(v)) {
            mst.push_back(edge);  // Include the edge in MST
            mstWeight += edge.weight;
            ds.unite(u, v);       // Union the sets
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

int main() {
    int vertices = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(vertices, edges);

    return 0;
}
