// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

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
		int n = 0;
		// d(x, y) = distance from vertex x to y

		// So find the sum of the distances...
		int distance = 0;
		for (int j = 0; j < path.noNodes; j++)
		{
			if (path.dist[j] > 0) // or (pred[j] != NULL)
			{
				n++;
				distance += path.dist[j];
			}
		}

		// Calculate the centrality...
		
		// If there exists a path...
		// If path is of size 1, then the centrality is zero. (cz there is no central node?)

		// if pred is null
		// if (pred[i] != NULL)
		if (n > 1 && distance > 0)
		{
			centrality.values[i] = ((n - 1.0)/(centrality.noNodes - 1.0)) * ((n - 1.0)/(distance * 1.0));
		}
		// Special case: Isolated node:
		else
		{
			centrality.values[i] = 0;
		}
	}
	return centrality;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
	for (int i = 0; i < values.noNodes; i++)
	{
		printf("%d: %lf\n", i, values.values[i]);
	}
}

void freeNodeValues(NodeValues values){
	free(values.values);
}
