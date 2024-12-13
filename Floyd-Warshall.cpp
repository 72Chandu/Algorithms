// C++ program to implement Floyd-Warshall algorithm
#include <iostream>
#include <limits.h>
#include <vector>
#define INF INT_MAX
using namespace std;
void printSolution(const vector<vector<int>> &dist){
    int V = dist.size();
    cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; ++i){
        for (int j = 0; j < V; ++j){
            if (dist[i][j] == INF) cout << "INF" << "\t";
            else cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}
void floydWarshall(vector<vector<int>> &graph){
    int V = graph.size();
    vector<vector<int>> dist = graph;
    // Update the solution matrix by considering all vertices
    for (int k = 0; k < V; ++k){
        for (int i = 0; i < V; ++i){
            for (int j = 0; j < V; ++j){
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolution(dist);
}
int main(){
    /* Let us create the following weighted graph
           10
      (0)------->(3)
       |         /|\
     5 |          |
       |          | 1
      \|/         |
      (1)------->(2)
           3           */
    vector<vector<int>> graph = {{0, 5, INF, 10}, {INF, 0, 3, INF}, {INF, INF, 0, 1}, {INF, INF, INF, 0}};
    floydWarshall(graph);
    return 0;
}
// C Program for Floyd Warshall Algorithm
#include <stdio.h>
#define V 4
#define INF 99999
void printSolution(int dist[][V]){
    printf("The following matrix shows the shortest distances between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) printf("%7s", "INF");
            else printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
void floydWarshall(int dist[][V]){
    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of an iteration, we have shortest distances between all pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of an iteration,  vertex no. k is added to the set of intermediate vertices and the set  becomes {0, 1, 2, .. k} */
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from  i to j, then update the value of  dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])  dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolution(dist);
}

int main(){
    /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */
    int graph[V][V] = { { 0, 5, INF, 10 },{ INF, 0, 3, INF },{ INF, INF, 0, 1 },{ INF, INF, INF, 0 } };
    floydWarshall(graph);
    return 0;
}
/*
o/p=

The following matrix shows the shortest distances between every pair of vertices 
0   5   8   9   
INF 0   3   4   
INF INF 0   1   
INF INF INF 0   
*/
