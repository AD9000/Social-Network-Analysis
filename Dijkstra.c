// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static bool inPredNodeList(PredNode* L, Vertex ver);
static void freePredList(PredNode* L);

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
				    freePredList(throwAway.pred[curr->w]);
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


//complete
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

//complete
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
