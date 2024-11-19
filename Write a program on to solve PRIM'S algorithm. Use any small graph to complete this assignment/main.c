//Write a program on to solve PRIM'S algorithm. Use any small graph to complete this assignment.
/*
Step 1: Determine an arbitrary vertex as the starting vertex of the MST.
Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
Step 3: Find edges connecting any tree vertex with the fringe vertices.
Step 4: Find the minimum among these edges.
Step 5: Add the chosen edge to the MST if it does not form any cycle.
Step 6: Return the MST and exit
*/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define n 5 // Number of vertices in the graph

//find the vertex with the minimum key value that is not included in the MST yet
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// print the constructed MST stored in parent[]
void printMST(int parent[], int graph[n][n]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

//construct MST for a graph represented using adjacency matrix
void primMST(int graph[n][n]) {
    int parent[n];     // Array to store the MST
    int key[n];        // Key values to pick the minimum weight edge
    bool mstSet[n];    // To represent vertices not yet included in MST
    for (int i = 0; i < n; i++) {// Initialize all keys as infinite
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    key[0] = 0;        // Make key 0 so that this vertex is picked first
    parent[0] = -1;    // First node is always the root of MST
    for (int count = 0; count < n - 1; count++) {// MST will have n vertices
        int u = minKey(key, mstSet);// Pick the minimum key vertex from the set of vertices not yet included in MST
        mstSet[u] = true;  // Add the picked vertex to the MST Set
        for (int v=0;v<n;v++){// Update the key value and parent index of the adjacent vertices of the picked vertex
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {// Update key only if graph[u][v] is smaller than key[v]
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}
int main() {
    // Example graph represented as an adjacency matrix
    int graph[n][n] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    primMST(graph);
    return 0;
}

/*

Edge    Weight
0 - 1   2
1 - 2   3
0 - 3   6
1 - 4   5

*/