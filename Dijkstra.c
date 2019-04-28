// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static bool inPredNodeList(PredNode* L, Vertex ver);
static void freePredList(PredNode* L);
static void freeAdjListMem(AdjList L);

/* Finds shortest paths from a given vertex to all other vertices, as discussed in the lectures.
 * Returns 'ShortestPaths' structure with the required information
 * (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph)
 */
ShortestPaths dijkstra(Graph g, Vertex v) {
	
	//declaring throwAway structure
	ShortestPaths throwAway;
	throwAway.noNodes = numVerticies(g);
	throwAway.src = v;
	throwAway.dist = malloc(throwAway.noNodes * sizeof(int));
	throwAway.pred = malloc(throwAway.noNodes * sizeof(PredNode *));

	//Intialising dist array with infinity like value
	for(int i = 0; i < throwAway.noNodes; i++){
		throwAway.dist[i] = INT_MAX;
	}
	
	//Initialising pred node array with NULL values
	for(int i = 0; i < throwAway.noNodes; i++){
		throwAway.pred[i] = NULL;
	}
	
	//source or starting vertex has the shortest distance 0
	throwAway.dist[v] = 0;

	//Initialising a Priority Queue and
	//inserting vertices with edges from the graph g
	PQ priorQ = newPQ();

	//add adjacent vertices and edge weights 
    	AdjList l = outIncident(g, v);
	AdjList curr = l;
	while (curr != NULL){
		ItemPQ new;
		new.key = v;
		new.value = curr->weight;
		addPQ(priorQ, new);
		curr = curr->next;
    }
    
	//add the source vertex to the Priority Queue
	//make its distance 0
	ItemPQ src;
	src.key = v;
	src.value = 0;
	addPQ(priorQ, src);
	
	//until the priority queue is empty
	while(!PQEmpty(priorQ)){

		//extract the minimum distance vertex from pq
		ItemPQ popItem = dequeuePQ(priorQ);
		Vertex u = popItem.key;
		AdjList new = outIncident(g, u);
		AdjList curr = new;
		
		//Loop through all adjacent vertices of u and
		//do the following for every adjacent vertex uVertex.
		//If there is a shorter path to uVertex through u
		//update the distance of uVertex.
		//Also update the PredNode list with predecessor vertices
		while (curr != NULL){

			//if a shorter path from u to curr->w node exists
			//update the distance and add u as pred in the PredNode list
			if (throwAway.dist[curr->w] > (throwAway.dist[u] + curr->weight)){
				throwAway.dist[curr->w] = throwAway.dist[u] + curr->weight;
				ItemPQ uVertex;
				uVertex.key = curr->w;
				uVertex.value = curr->weight;

				//insert uVertex in the pq even if it is already there
				addPQ(priorQ, uVertex);
				
				//if the PredNode linked list is empty
				if(throwAway.pred[curr->w] == NULL){
				    PredNode *new = malloc(sizeof(PredNode));
				    throwAway.pred[curr->w] = new;
				    new->v = u;
				    new->next = NULL;

				//Delete the existing PredNode linked list and
				//create new one as new shortest path has been found.
				//The new path would have different PredNodes
				} else {
				    freePredList(throwAway.pred[curr->w]);
			        PredNode *new = malloc(sizeof(PredNode));
			        throwAway.pred[curr->w] = new;
			        new->v = u;
			        new->next = NULL;
				}
			}
			//if the shortest distance is the same as existing
			//shortest path, add the vertex to PredNode list
			if (throwAway.dist[curr->w] == (throwAway.dist[u] + curr->weight)){
			    if (!inPredNodeList(throwAway.pred[curr->w], u)){
			        PredNode *new = malloc(sizeof(PredNode));
			        new->v = u;
		            new->next = throwAway.pred[curr->w];
		            throwAway.pred[curr->w] = new;
			    }
			}
			
			curr = curr->next;
		}
		freeAdjListMem(new);
	}
	
	//convert the distance of all the vertices that can't
	//be reached from src vertex from infinity to 0
	for(int i = 0; i < throwAway.noNodes; i++){
	    if(throwAway.dist[i] == INT_MAX){
	        throwAway.dist[i] = 0;
	    }
	}
	freeAdjListMem(l);
	freePQ(priorQ);
	return throwAway;
}


//prints the struct ShortestPaths for testing and visual inspection
void showShortestPaths(ShortestPaths paths) {
    printf("Total Nodes in Graph: %d\n\n", paths.noNodes);
    printf("Distance from node %d to other nodes is as under: \n", paths.src);
    printf("Distance:\n");
    for(int i = 0; i < paths.noNodes; i++){
        printf("%d : %d\n", i, paths.dist[i]);   
    }
    printf("Preds\n");
    for(int i = 0; i < paths.noNodes; i++){
        PredNode *curr = paths.pred[i];
        printf("%d: ", i);
        while(curr!=NULL){
            printf(" [%d] ", curr->v);
            curr = curr->next;
        }
    }
}

//frees memory allocated to ShortestPaths struct
void  freeShortestPaths(ShortestPaths paths) {
    free(paths.dist);
    //free the linked lists in the pred
    for(int i = 0; i < paths.noNodes; i++){
        PredNode *prev = NULL;
        PredNode *curr = paths.pred[i];
        while (curr != NULL){
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    free(paths.pred);
}

//checks if a vertex is already in the PredNode list
static bool inPredNodeList(PredNode* L, Vertex ver){
    PredNode *curr = L;
    while(curr != NULL){
        if (curr->v == ver){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

//frees memory related to a PredList when a 
//new PredList is created upon the discovery of 
//a path shorter than the current shortest path
static void freePredList(PredNode* L){
    PredNode *prev = NULL;
    PredNode *curr = L;
    while (curr != NULL){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
}

//free memory allocated to outIncident list from Graph.c
static void freeAdjListMem(AdjList L){
    adjListNode *prev = NULL;
    adjListNode *current = L;
    while (current != NULL){
        prev = current;
        current = current->next;
        free(prev);
    }
}

