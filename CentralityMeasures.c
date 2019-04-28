// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static int numberOfOccurrences(PredNode **pred, Vertex dest, Vertex src, Vertex find);
static int numberOfShortestPaths(PredNode **pred, Vertex dest, Vertex src);


// Find out the outDegree centrality of each vertex of the graph
NodeValues outDegreeCentrality(Graph g){
	// Pointer containing centrality values.
	NodeValues centrality;

	// For each vertex in the graph...
	centrality.noNodes = numVerticies(g);
	centrality.values = malloc(centrality.noNodes * sizeof(double));

	for (int i = 0; i < centrality.noNodes; i++)
	{
		int count = 0;

		// Find out-cident list.
		AdjList out = outIncident(g, i);

		// Length of the list is the centrality for the vertex.
		AdjList current = out;
		while (current != NULL)
		{
			count++;
			current = current -> next;
		}
		centrality.values[i] = (double)count;
	}
	return centrality;
}

NodeValues inDegreeCentrality(Graph g){
	assert(g != NULL);
	
	// Pointer containing centrality values.
	NodeValues centrality;

	// For each vertex in the graph...
	centrality.noNodes = numVerticies(g);
	centrality.values = malloc(centrality.noNodes * sizeof(double));

	for (int i = 0; i < centrality.noNodes; i++)
	{
		int count = 0;

		// Find in-Incident list.
		AdjList in = inIncident(g, i);

		// Length of the list is the centrality for the vertex.
		AdjList current = in;
		while (current != NULL)
		{
			count++;
			current = current -> next;
		}
		centrality.values[i] = (double)count;
	}
	return centrality;
}
NodeValues degreeCentrality(Graph g) {
	assert(g != NULL);
	
	// Pointer containing centrality values.
	NodeValues centrality;

	// For each vertex in the graph...
	centrality.noNodes = numVerticies(g);
	centrality.values = malloc(centrality.noNodes * sizeof(double));

	NodeValues out = outDegreeCentrality(g);
	NodeValues in = inDegreeCentrality(g);

	for (int i = 0; i < centrality.noNodes; i++)
	{
		// Add the in-Incident and out-Incident degree centrality
		centrality.values[i] = in.values[i] + out.values[i];
	}
	return centrality;
}

NodeValues closenessCentrality(Graph g){
	assert(g != NULL);
	
	// Pointer containing centrality values.
	NodeValues centrality;

	centrality.noNodes = numVerticies(g);
	centrality.values = malloc(centrality.noNodes * sizeof(double));

	// For each vertex in the graph...
	for (int i = 0; i < centrality.noNodes; i++)
	{
		// Find the all the shortest paths from that vertex
		ShortestPaths path = dijkstra(g, i);

		// N = centrality.noNodes = Number of nodes in graph
		// n = number of paths that exist.
		int n = 1;
		//showShortestPaths(path);
		
		// d(x, y) = distance from vertex x to y

		// So find the sum of the distances...
		int distance = 0;
		for (int j = 0; j < path.noNodes; j++)
		{
			if (path.dist[j] > 0)
			{
				n++;
				distance += path.dist[j];
			}
		}

		// If there exists a path...
		// If path is of size 1, then the centrality is zero. (cz there is no central node?)
		if (n > 1 && distance > 0)
		{
			centrality.values[i] = ((n - 1) * 1.0/(centrality.noNodes - 1)) * ((n - 1)/(distance * 1.0));
		}
		// Special case: Isolated node:
		else
		{
			centrality.values[i] = 0;
		}
	}
	return centrality;
}

// // Length of appearances array is len
// double *countShortestPaths(PredNode **pred, int appearances[], int len, Vertex src)
// {
// 	// For each pair of nodes, find the number of appearances of each node in the shortest path...
// 	// But the first node is fixed. ie the src.
// 	// And pred[i] makes i the last node.
// 	// So if a node has 2 pred nodes, and one of the 
// 	PredNode *current = pred[0];
// 	while (current != NULL)
// 	{
// 		// If the current vertex is not the source...it makes an appearance!
// 		if (current -> v != src)
// 		{
// 			appearances[current -> v]++;
// 		}
// 		current = pred[current -> v];
// 	}
// 	// Once current has reached null... the shortest path is completed. Now do th
// }

// static int noPaths(PredNode **pred, Vertex look)
// {
// 	int count = 0;
// 	PredNode *current = pred[look];
// 	while (current != NULL)
// 	{
// 		count++;
// 		current = current -> next;
// 	}
// 	return count;
// }

static int numberOfOccurrences(PredNode **pred, Vertex dest, Vertex src, Vertex find)
{
	if (dest == find)
	{
		return numberOfShortestPaths(pred, dest, find);
	}
	else
	{
		PredNode *current = pred[dest];
		int total = 0;
		while (current != NULL)
		{
			total += numberOfOccurrences(pred, current -> v, src, find);
			current = current -> next;
		}
		return total;
	}
}

static int numberOfShortestPaths(PredNode **pred, Vertex dest, Vertex src)
{
	// If you are at the dest node, then there must be predNode[dest].length ways to come here...
	// Then there are predNode[i for i in predNode[dest]].length ways to come here and so on.
	if (dest == src)
	{
		return 1;
	}
	else
	{
		PredNode *current = pred[dest];
		//PredNode *curr = pred[0];
		//printf("Does pred exist? for dest = %d: %p\n", dest, pred);
		//PredNode *curr = *pred;
		//printf("current value for dest %d: %p: %d\n", dest, *pred, curr -> v);
		//printf("current value: %d\n", current -> v);
		// if (curr != NULL)
		// {
		// 	printf("Pred can be accessed? %d\n", curr -> v);
		// }
		// else
		// {
		// 	printf("Pred can be accessed? for dest = %d: %p\n", dest, curr);
		// }
		int total = 0;
		while (current != NULL)
		{
			total += numberOfShortestPaths(pred, current -> v, src);
			//printf("Number of shortest paths between %d and %d is equal to %d\n", src, current -> v, total);
			current = current -> next;
		}
		return total;
	}
}

NodeValues betweennessCentrality(Graph g){
	assert(g != NULL);

	// Pointer containing centrality values.
	NodeValues centrality;

	centrality.noNodes = numVerticies(g);
	centrality.values = malloc(centrality.noNodes * sizeof(double));
	
	// For each node in the graph...
	for (int i = 0; i < centrality.noNodes; i++)
	{
		// Get shortest path from node i to every other node...
		ShortestPaths path = dijkstra(g, i);
		// if (i == 11)
		// {
		// 	showShortestPaths(path);
		// }
		// For each pair of nodes in graph...(src = i), (dest = j)
		for (int j = 0; j < centrality.noNodes; j++)
		{
			// Find the number of shortest paths...
			int n = numberOfShortestPaths(path.pred, j, i);
			
			// printf("Number of shortest paths between %d and %d is equal to %d\n", i, j, n);
			// printf("for i and j equal to %d and %d, n = %d\n", i, j, n);
			// printf("---------------------------------------\n");

			//PredNode *current = path.pred[j];
			// if (current != NULL)
			// {
			// 	printf("Pred can be accessed? %d\n", current -> v);
			// }
			// else
			// {
			// 	printf("Pred can be accessed? %p\n", current);
			// }

			// For each node in the graph...
			for (int k = 0; k < centrality.noNodes; k++)
			{
				// Count the number of occurences of k in the shortest paths from src to dest
				if (k == i || k == j)
				{
					continue;
				}
				int count = numberOfOccurrences(path.pred, j, i, k);

				// Then the betweenness is for the current node between i and j is:
				// if (k == 11 && (count == n) && n != 0)
				// {
				// 	printf("Count = %d and n = %d\n", count, n);
				// 	printf("src = %d and dest = %d, find = %d\n", i, j, k);
				// }
				
				if (n > 0)
				{
					centrality.values[k] += count * 1.0/n;
				}
			}
		}

		// // Assuming that betweeness array now contains the betweeness summation for each of the
		// // pairs between i and every other node...
		// // Add the betweenness to the total betweenness of each node...
		// for (int j = 0; j < centrality.noNodes; j++)
		// {
		// 	centrality.values[j] += betweenness[j];
		// }
		// Make pairs of the nodes...
		// Get shortest paths between all the pairs...
		// Dijkstra gives the shortest paths between the src and all vertices in 
		// the graph. So when you try
		// Count the number of shortest paths that exist and how many times
		// every node occurs in that shortest path then calculate the betweenness.
		// betweenness = countShortestPaths(path.pred, appearances, centrality.noNodes, i);
	}
	return centrality;
}

NodeValues betweennessCentralityNormalised(Graph g){
	assert(g != NULL);
	NodeValues centrality = betweennessCentrality(g);

	// Pointer containing centrality values.
	if (centrality.noNodes < 2)
	{
		for (int i = 0; i < centrality.noNodes; i++)
		{
			centrality.values[i] = 0;
		}
		return centrality;
	}
	
	int divisor = (centrality.noNodes - 1) * (centrality.noNodes - 2);
	for (int i = 0; i < centrality.noNodes; i++)
	{
		centrality.values[i] = centrality.values[i]/divisor;
	}
	return centrality;
}

// To show the nodeValues.
void showNodeValues(NodeValues values){
	for (int i = 0; i < values.noNodes; i++)
	{
		printf("%d: %lf\n", i, values.values[i]);
	}
}


void freeNodeValues(NodeValues values){
    free(values.values);
}
