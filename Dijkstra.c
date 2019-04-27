// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static bool inPredNodeList(PredNode* L, Vertex ver);

//shortest distance complete
//working on pred path - almost there
ShortestPaths dijkstra(Graph g, Vertex v) {
	
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
	ItemPQ src;
	src.key = v;
	src.value = 0;
	addPQ(priorQ, src);

	while(!PQEmpty(priorQ)){
		ItemPQ popItem = dequeuePQ(priorQ);
		Vertex u = popItem.key;
		AdjList new = outIncident(g, u);
		AdjList curr = new;
		while (curr != NULL){
			if (throwAway.dist[curr->w] > (throwAway.dist[u] + curr->weight)){
				throwAway.dist[curr->w] = throwAway.dist[u] + curr->weight;
				ItemPQ uVertex;
				uVertex.key = curr->w;
				uVertex.value = curr->weight;
				addPQ(priorQ, uVertex);
				if(throwAway.pred[curr->w] == NULL){
				    PredNode *new = malloc(sizeof(PredNode));
				    throwAway.pred[curr->w] = new;
				    new->v = u;
				    new->next = NULL;
				} else {
			        PredNode *new = malloc(sizeof(PredNode));
			        throwAway.pred[curr->w] = new;
			        new->v = u;
			        new->next = NULL;
				}
			}
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
	}
	
	for(int i = 0; i < throwAway.noNodes; i++){
	    if(throwAway.dist[i] == INT_MAX){
	        throwAway.dist[i] = 0;
	    }
	}
	freePQ(priorQ);
	return throwAway;
}


//Little more work - 20 mins max
void showShortestPaths(ShortestPaths paths) {
    printf("Total Nodes in Graph: %d\n\n", paths.noNodes);
    printf("Distance from node %d to other nodes is as under: ", paths.src);
    printf("Distance:\n");
    for(int i = 0; i < paths.noNodes; i++){
        printf("%d : %d\n", i, paths.dist[i]);   
    }
    printf("Preds");
    for(int i = 0; i < paths.noNodes; i++){
        printf("%d : ", i);
    }
}

//Little more work - 20 mins max
void  freeShortestPaths(ShortestPaths paths) {
    free(paths.dist);
    //free the linked list pred
}

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

