// Graph ADT interface for Ass2 (COMP2521)
//Written By Jasdeep, Atharv & Pramith

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"

//complete
struct GraphRep{
	int nVertices;
	int nEdges;
	AdjList edges[];
};

//complete
Graph newGraph(int noNodes) {

	assert(noNodes > 0);
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	new->nVertices = noNodes;
	new->nEdges = 0;
	new->edges = malloc(noNodes*(sizeof(AdjList)));
	for (int i = 0; i < noNodes; i++){
		new->edges[i] = NULL;
	}
	return new;
}

//complete
int numVerticies(Graph g) {
	assert(g != NULL)
	return g->nVertices;
}

//complete
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert (g != NULL);
	assert(weight > 0);
	assert(validVertex(g,src) && validVertex(g,dest));
	//if edges[src] is NULL
	if(g->edges[src] == NULL){
		AdjList new = malloc(sizeof(adjListNode));
		new->Vertex = dest;
		new->weight = weight;
		new->next = NULL;
		g->edges[src] = new;
		g->nEdges++;
	//if edges[src] is not NULL
	//insert in the front of the list
	} else {
		AdjList new = malloc(sizeof(adjListNode));
		new->Vertex = dest;
		new->weight = weight;
		new->next = g->edges[src];
		g->edges[src] = new;
		g->nEdges++;
	}
}

//complete
void  removeEdge(Graph g, Vertex src, Vertex dest) {
	assert (g != NULL);
	assert(validVertex(g,src) && validVertex(g,dest));
	AdjList prev = NULL;
	AdjList curr = g->edges[src];
	while(curr != NULL && curr->w != dest){
		prev = curr;
		curr = curr->next;
	}

	//edge does not exist
	if (curr == NULL){
		return;
	}

	//unlink the node and reestablish the links
	if(prev == NULL){
		g->edges[src] = curr->next;
	} else {
		prev->next = curr->next;
	}
	g->nEdges--;
	//free memory linked with the node
	free(curr);
}

//complete
bool adjacent(Graph g, Vertex src, Vertex dest) {
	assert (g != NULL);
	assert(validVertex(g,src) && validVertex(g,dest));
	AdjList curr = g->edges[src];
	while (curr != NULL){
		if(curr->w == dest){
			return true;
		}
		curr = curr->next;	
	}
	return false;
}

//complete
AdjList outIncident(Graph g, Vertex v) {
	assert (g != NULL);
	assert(validVertex(g,v));
	AdjList outInciList = g->edges[v];
	return outInciList;
}

//complete
AdjList inIncident(Graph g, Vertex v) {
	assert (g != NULL);
	assert(validVertex(g,v));
	AdjList inInciList = NULL;
	for(int i = 0; i < g->nVertices; i++){
		AdjList curr = g->edges[i];
		while(curr != NULL){
			if(curr->w == v){
				if(inInciList == NULL){
					AdjList new = malloc(sizeof(adjListNode));
					assert(new != NULL);
					new->w = i;
					new->weight = curr->weight;
					inInciList = new;
					new->next = NULL;
				} else{
					AdjList new = malloc(sizeof(adjListNode));
					assert(new != NULL);
					new->w = i;
					new->weight = curr->weight;
					new->next = inInciList;
					inInciList = new;
				}
			}
			curr = curr->next;
		}
	}
	return inInciList;
}

//complete
void  showGraph(Graph g) {
	assert (g != NULL);
	printf("Num of Vertices = %d, Num of Edges = %d", g->nVertices, g->nEdges);
	for(int i = 0; i < g->nVertices; i++){
		AdjList curr = g->edges[i];
		while(curr != NULL){
			printf("%d, %d, %d\n", i, curr->w, curr->weight);
			curr = curr->next;
		}
		printf("\n");
	}
}

//complete
void  freeGraph(Graph g) {

	assert (g != NULL);
	for(int i = 0; i < g->nVertices; i++){
		AdjList curr = g->edges[i];
		AdjList next = NULL;
		while(curr != NULL){
			next = curr->next;
			free(curr);
			curr = next;
		}
	}
	free(g->edges);
	free(g);
}

static int validVertex(Graph g, Vertex v){

	return (g != NULL && v >= 0 && v < g->nVertices);
}
