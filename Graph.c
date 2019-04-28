
// Graph ADT interface for Ass2 (COMP2521)
//Written By Jasdeep, Atharv & Pramith

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

static int validVertex(Graph g, Vertex v);

//Graph Representation using Adjacency list representation
struct GraphRep{
	int nVertices;
	int nEdges;
	AdjList *edges;
};

//Creates a new graph
Graph newGraph(int noNodes) {

	assert(noNodes > 0);
	Graph new = malloc(sizeof(struct GraphRep));
	assert(new != NULL);
	new->nVertices = noNodes;
	new->nEdges = 0;
	new->edges = malloc(noNodes*(sizeof(AdjList)));
	for (int i = 0; i < noNodes; i++){
		new->edges[i] = NULL;
	}
	return new;
}

//returns number of vertices in a graph
int numVerticies(Graph g) {
	assert(g != NULL);
	return g->nVertices;
}

//inserts edge into a graph 
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert (g != NULL);
	assert(weight > 0);
	assert(validVertex(g,src) && validVertex(g,dest));
	//if edges[src] is NULL
	if(g->edges[src] == NULL){
		AdjList new = malloc(sizeof(adjListNode));
		new->w = dest;
		new->weight = weight;
		new->next = NULL;
		g->edges[src] = new;
		g->nEdges++;
	//if edges[src] is not NULL
	//insert in the front of the list
	} else {
		AdjList new = malloc(sizeof(adjListNode));
		new->w = dest;
		new->weight = weight;
		new->next = g->edges[src];
		g->edges[src] = new;
		g->nEdges++;
	}
}

//removes and edge from graph and frees associated memory with that edge
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

//checks if two given vertices are adjacent in a graph
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

//Returns a list of adjacent vertices
//on outgoing edges from a given vertex.
AdjList outIncident(Graph g, Vertex v) {
	assert (g != NULL);
	assert(validVertex(g,v));
	AdjList curr = g->edges[v];
	AdjList outInciList = NULL;
    while(curr != NULL){
        if(outInciList == NULL){
            AdjList new = malloc(sizeof(adjListNode));
		    assert(new != NULL);
		    new->w = curr->w;
		    new->weight = curr->weight;
		    outInciList = new;
		    new->next = NULL;
        } else {
            AdjList new = malloc(sizeof(adjListNode));
			assert(new != NULL);
			new->w = curr->w;
			new->weight = curr->weight;
			new->next = outInciList;
			outInciList = new;
        }
       curr = curr->next;
    }	
	return outInciList;
}

//Returns a list of adjacent vertices
//on incoming edges from a given vertex.
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

//prints graph for testing and visual inspection
void  showGraph(Graph g) {
	assert (g != NULL);
	printf("Num of Vertices = %d, Num of Edges = %d\n", g->nVertices, g->nEdges);
	for(int i = 0; i < g->nVertices; i++){
		AdjList curr = g->edges[i];
		while(curr != NULL){
			printf("%d, %d, %d\n", i, curr->w, curr->weight);
			curr = curr->next;
		}
		printf("\n");
	}
}

//frees all memory associated with graph
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

//checks if a given vertex is valid
static int validVertex(Graph g, Vertex v){

	return (g != NULL && v >= 0 && v < g->nVertices);
}
