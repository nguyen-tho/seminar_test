// A C program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
#include <limits.h>
#include<fstream>
#include <stdbool.h>
#include <stdio.h>

using namespace std;

// Number of vertices in the graph
#define MAX 100

int V;
int graph[MAX][MAX];

void getData() {
    ifstream IF("prim.inp");
    IF>>V;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            IF>>graph[i][j];
			
        }
    }
    IF.close();
}

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[MAX][MAX])
{
    int totalWeight = 0;
	printf("Edge \tWeight\n");
	for (int i = 1; i < V; i++){
        printf("%d - %d \t%d \n", parent[i], i,
			graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("\nMinimum weight of tree: %d", totalWeight);
		
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[MAX][MAX])
{
	// Array to store constructed MST
	int parent[V];
	// Key values used to pick minimum weight edge in cut
	int key[V];
	// To represent set of vertices included in MST
	bool mstSet[V];

	// Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first
	// vertex.
	key[0] = 0;
	parent[0] = -1; // First node is always root of MST

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < V; v++)

			// graph[u][v] is non zero only for adjacent
			// vertices of m mstSet[v] is false for vertices
			// not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false
				&& graph[u][v] < key[v] && graph[u][v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST
	printMST(parent, graph);
}

// driver's code
int main()
{
	/* Let us create the following graph
		2 3
	(0)--(1)--(2)
	| / \ |
	6| 8/ \5 |7
	| /	 \ |
	(3)-------(4)
			9		 */
	

	// Print the solution
	getData();
	primMST(graph);

	return 0;
}
