// PQ ADT interface for Ass2 (COMP2521)
//Written by Jasdeep, Atharv & Pramit
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_ELEMS 2048
static void fixUp(ItemPQ **a, int i);
static void fixDown(ItemPQ **a, int i, int N);
static void swap(ItemPQ **a, int i, int j);

struct PQRep {
    ItemPQ ** Prior_Q; //an array of pointers to PQ structures
    int N; //num of elements in PQ;
};

//complete
PQ newPQ() {

	PQ new = malloc(sizeof(struct PQRep));
	assert(new != NULL);
	new->Prior_Q = malloc(MAX_ELEMS * (sizeof(ItemPQ*)));
	for (int i = 0; i < MAX_ELEMS; i++){
	    new->Prior_Q[i] = NULL;
	}
	new->N = 0;
	return new;
}

//complete
int PQEmpty(PQ p) {

		return (p->N == 0);
}

//complete
void addPQ(PQ pq, ItemPQ element) {
    
    //update 'value' if 'key' exists
    int i = 1;
    while(i <= pq->N && pq->Prior_Q[i] != NULL){
        if(pq->Prior_Q[i]->key == element.key){
            pq->Prior_Q[i]->value = element.value;
            return;
        }
        i++;
    }
    
    //insertion if key does not exist
    ItemPQ *newNode = malloc(sizeof(ItemPQ));
    pq->N++;
    pq->Prior_Q[pq->N] = newNode;
    newNode->key = element.key;
    newNode->value = element.value;
    fixUp(pq->Prior_Q, pq->N);
}

//complete
ItemPQ dequeuePQ(PQ pq) {
	
	ItemPQ throwAway;
	throwAway.key = pq->Prior_Q[1]->key;
	throwAway.value = pq->Prior_Q[1]->value;
	pq->Prior_Q[1] = pq->Prior_Q[pq->N];
	pq->N--;
	fixDown(pq->Prior_Q, 1, pq->N);
	return throwAway;
}

//complete
void updatePQ(PQ pq, ItemPQ element) {
    int i = 1;
    while (i <= pq->N){
        if(pq->Prior_Q[i]->key == element.key){
            pq->Prior_Q[i]->value = element.value;
        }
        i++;
    }
}

//complete
void  showPQ(PQ pq) {
    
    int i = 1;
    while(pq->Prior_Q[i] != NULL){
        printf("(%d, %d)\n", pq->Prior_Q[i]->key, pq->Prior_Q[i]->value);
        i++;    
    }
}

//complete
void  freePQ(PQ pq) {

    assert(pq != NULL);
    int i = 1;
    while (i <= pq->N && pq->Prior_Q[i] != NULL){
        ItemPQ *PQNode=  pq->Prior_Q[i];
        free(PQNode);
        i++;
    }
    free(pq->Prior_Q);
    free(pq);
}


//not complete
static void swap(ItemPQ **a, int i, int j){

}

//not complete
//fixUp function
static void fixUp(ItemPQ **a, int i){
}

//not complete
//fixDown function
static void fixDown(ItemPQ **a, int i, int N){

}




