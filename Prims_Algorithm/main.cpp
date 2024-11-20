/* O(V2)
Step 1: Determine an arbitrary vertex as the starting vertex of the MST.
Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
Step 3: Find edges connecting any tree vertex with the fringe vertices.
Step 4: Find the minimum among these edges.
Step 5: Add the chosen edge to the MST if it does not form any cycle.
Step 6: Return the MST and exit

Create a set mstSet that keeps track of vertices already included in MST. 
Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. Assign the key value as 0 for the first vertex so that it is picked first. 
While mstSet doesn’t include all vertices 
Pick a vertex u that is not there in mstSet and has a minimum key value. 
Include u in the mstSet. 
Update the key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. 
For every adjacent vertex v, if the weight of edge u-v is less than the previous key value of v, update the key value as the weight of u-v. 
*/
#include <bits/stdc++.h>
using namespace std;
#define V 5 // Number of vertices in the graph

// Function to find the vertex with the minimum key value
// from the set of vertices not yet included in MST
int minKey(vector<int> &key, vector<bool> &mstSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST stored in parent[]
void printMST(vector<int> &parent, vector<vector<int>> &graph) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
    }
}

// Function to construct and print MST for a graph
// represented using adjacency matrix representation
void primMST(vector<vector<int>> &graph) {
    vector<int> parent(V); // Array to store constructed MST
    vector<int> key(V, INT_MAX); // Key values to pick minimum weight edge
    vector<bool> mstSet(V, false); // To represent set of vertices included in MST

    // Always include the first vertex in MST. Make key[0] 0 so that it's picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);
        
        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of adjacent vertices of the picked vertex
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}
int main() {
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    primMST(graph);
    return 0;
}

/******************************************************************/
//methode 2    tc=O(E*log(E)
/*
We transform the adjacency matrix into adjacency list using array of  vectors in C++.
Then we create a Pair class to store the vertex and its weight .
We sort the list on the basis of lowest weight.
We create priority queue and push the first vertex and its weight in the queue
Then we just traverse through its edges and store the least weight in a variable called ans.
At last after all the vertex we return the ans.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to find the sum of weights of edges of the Minimum Spanning Tree.
int spanningTree(int V, int E, vector<vector<int>> &edges) {
    // Create an adjacency list representation of the graph
    vector<vector<pair<int, int>>> adj(V);

    // Fill the adjacency list with edges and their weights
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Create a priority queue to store edges with their weights
    // Pair first = weight, second = vertex
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Create a visited array to keep track of visited vertices
    vector<bool> visited(V, false);

    // Variable to store the result (sum of edge weights)
    int res = 0;

    // Start with vertex 0
    pq.push({0, 0});

    // Perform Prim's algorithm to find the Minimum Spanning Tree
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        int wt = p.first;  // Weight of the edge
        int u = p.second;  // Vertex connected to the edge

        if (visited[u]) {
            continue;  // Skip if the vertex is already visited
        }

        res += wt;  // Add the edge weight to the result
        visited[u] = true;  // Mark the vertex as visited

        // Explore the adjacent vertices
        for (auto &v : adj[u]) {
            // v.first represents the vertex and v.second represents the edge weight
            if (!visited[v.first]) {
                pq.push({v.second, v.first});  // Add the adjacent edge to the priority queue
            }
        }
    }

    return res;  // Return the sum of edge weights of the Minimum Spanning Tree
}

int main() {
    // Input graph with edges represented as [vertex1, vertex2, weight]
    vector<vector<int>> graph = {
        {0, 1, 5},  // Edge between vertex 0 and vertex 1 with weight 5
        {1, 2, 3},  // Edge between vertex 1 and vertex 2 with weight 3
        {0, 2, 1}   // Edge between vertex 0 and vertex 2 with weight 1
    };
    cout << spanningTree(3, 3, graph) << endl;

    return 0;
}
