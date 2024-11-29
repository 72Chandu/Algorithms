#include<iostream>
using namespace std;
void dijkstra(int n, int cost[10][10], int s, int dist[10]){
    int i, v, count = 1, min, visited[10];
    for(i = 1; i <= n; i++){
        visited[i] = 0;
        dist[i] = cost[s][i];
    }
    visited[s] = 1;  
    dist[s] = 0;     
    while(count < n){  
        min = 999;
        v = -1;
        for(i = 1; i <= n; i++){
            if(!visited[i] && dist[i] < min){
                min = dist[i];
                v = i;
            }
        }
        if(v == -1) break;
        visited[v] = 1;  
        count++;
        for(i = 1; i <= n; i++){
            if(!visited[i] && dist[i] > (dist[v] + cost[v][i])){
                dist[i] = dist[v] + cost[v][i];
            }
        }
    }
}
int main(){
    int i, j, n, s, cost[10][10], dist[10];
    printf("\nEnter number of nodes: ");
    scanf("%d", &n);
    
    printf("\nRead cost matrix: \n");
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            scanf("%d", &cost[i][j]);
            if(cost[i][j] == 0) cost[i][j] = 999;  
        }
    }
    printf("\nRead source vertex: ");
    scanf("%d", &s);
    dijkstra(n, cost, s, dist);
    printf("\nShortest path from %d is \n", s);
    for(i = 1; i <= n; i++){
        if(s != i){
            printf("%d -> %d = %d\n", s, i, dist[i]);
        }
    }
    return 0;
}

/*
Number of nodes: 4

Cost matrix (adjacency matrix representation of graph):
0 1 4 0
1 0 2 6
4 2 0 3
0 6 3 0
source vertx=1

Here, 0 means no direct connection between nodes.
Replace 0 with 999 (infinity) for computation, except for self-loops (cost[i][i]).
Source vertex: 1

999  1  4 999
  1 999  2   6
  4   2 999   3
999   6   3 999

Visited Array: [0, 0, 0, 0, 0].
Distance Array: [999, 0, 1, 4, 999] shortest known distance to each vertex. Initially

Iteration 1
dist = [999, 0, 1, 4, 999], the closest unvisited node is 2 (distance = 1).
Mark 2 as visited: Visited Array: [0, 1, 1, 0, 0].
Update distances for neighbors of 2:
dist[3] = min(dist[3], dist[2] + cost[2][3]) = min(4, 1 + 2) = 3.
dist[4] = min(dist[4], dist[2] + cost[2][4]) = min(999, 1 + 6) = 7. Updated Distance Array: [999, 0, 1, 3, 7].

Iteration 2
dist = [999, 0, 1, 3, 7], the closest unvisited node is 3 (distance = 3).
Mark 3 as visited:Visited Array: [0, 1, 1, 1, 0].
Update distances for neighbors of 3:
dist[4] = min(dist[4], dist[3] + cost[3][4]) = min(7, 3 + 3) = 6. Updated Distance Array: [999, 0, 1, 3, 6].

Iteration 3
dist = [999, 0, 1, 3, 6], the closest unvisited node is 4 (distance = 6).
Mark 4 as visited:Visited Array: [0, 1, 1, 1, 1].
No further updates needed as all nodes are visited.
Final Shortest Distances

From source vertex 1, the shortest distances to all other nodes:

1 -> 2 = 1
1 -> 3 = 3
1 -> 4 = 6
Output: Shortest path from 1 is 
1 -> 2 = 1
1 -> 3 = 3
1 -> 4 = 6
*/


//methode 2
#include <limits.h>
#include <stdio.h>

#define V 9 // Number of vertices in the graph
int minDistance(int dist[], bool sptSet[]){
	int min = INT_MAX, min_index;// Initialize min value
	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}
void printSolution(int dist[], int n){
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("\t%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src){
	int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

	for (int i = 0; i < V; i++)   	// Initialize all distances as INFINITE and stpSet[] as false
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;	// Distance of source vertex from itself is always 0
	
	for (int count = 0; count < V - 1; count++) {  // Find shortest path for all vertices
		int u = minDistance(dist, sptSet);		// Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
		sptSet[u] = true;// Mark the picked vertex as processed
		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < V; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])   			// Update dist[v] only if is not in sptSet,there is an edge from u to v, and total weight  of path from src to v through u is smaller than current value of dist[v]
				dist[v] = dist[u] + graph[u][v];
	}
	printSolution(dist, V);
}
int main()
{
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	dijkstra(graph, 0);
	return 0;
}