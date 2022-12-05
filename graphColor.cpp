#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#define MAX 100
using namespace std;
int V;
// Number of vertices in the graph
void getInput(int graph[MAX][MAX], int &n){
	cout<<"Enter number of Vertex: ";
	cin>> n;
	for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++){
             cin>>graph[i][j];
        }
           
    }
}

void showMatrix(int graph[MAX][MAX], int n){
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++){
             cout<< graph[i][j]<<" ";
             
        }
        cout<<"\n";   
    }
}

void printSolution(int color[]);

// check if the colored
// graph is safe or not
bool isSafe(int graph[MAX][MAX], int color[])
{
	// check for every edge
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			if (graph[i][j] && color[j] == color[i])
				return false;
	return true;
}

/* This function solves the m Coloring
problem using recursion. It returns
false if the m colours cannot be assigned,
otherwise, return true and prints
assignments of colours to all vertices.
Please note that there may be more than
one solutions, this function prints one
of the feasible solutions.*/
bool graphColoring(int graph[MAX][MAX], int m, int i,
				int color[])
{
	// if current index reached end
	if (i == V) {
	
		// if coloring is safe
		if (isSafe(graph, color)) {
		
			// Print the solution
			printSolution(color);
			return true;
		}
		return false;
	}

	// Assign each color from 1 to m
	for (int j = 1; j <= m; j++) {
		color[i] = j;

		// Recur of the rest vertices
		if (graphColoring(graph, m, i + 1, color))
			return true;

		color[i] = 0;
	}

	return false;
}

/* A utility function to print solution */
void printSolution(int color[])
{
	cout << "Solution Exists:" " Following are the assigned colors \n";
	for (int i = 0; i < V; i++)
		cout << " " << color[i];
	cout << "\n";
}

// Driver code
int main()
{
	
	int graph[MAX][MAX];
	getInput(graph,V);
	cout<<"The graph Matrix: \n";
	showMatrix(graph,V);
	/* Create following graph and
	test whether it is 3 colorable
	(3)---(2)
	| / |
	| / |
	| / |
	(0)---(1)
	*/
/*
	bool graph[V][V] = { { 0, 1, 1, 1,0, 0 },
						{ 1, 0, 1, 0, 1, 0 },
						{ 1, 1, 0, 1, 0, 1 },
						{ 1, 0, 1, 0, 0, 1 },
                        { 0, 1, 0, 0, 0, 1 },
                        { 0, 0, 1, 1, 1, 0}, };
	
*/
	// Initialize all color values as 0.
	// This initialization is needed
	// correct functioning of isSafe()
	int color[MAX];
	for (int i = 0; i < V; i++)
		color[i] = 0;

	if (!graphColoring(graph, V, 0, color))
		cout << "Solution does not exist";

	return 0;
}

// This code is contributed by shivanisinghss2110
