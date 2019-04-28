// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_ELEMS 2048
static void fixUp(ItemPQ **a, int i);
static void fixDown(ItemPQ **a, int i, int N);
static void swap(ItemPQ **a, int i, int j);

//Priority Queue Representation
struct PQRep {
    ItemPQ ** Prior_Q; //an array of pointers to PQ structures
    int N; //num of elements in PQ;
    int nSlots; //Number of slots/spaces in array
};

//Creates new priority queue, that can store items of type ItemPQ.
PQ newPQ() {

	PQ new = malloc(sizeof(struct PQRep));
	assert(new != NULL);
	new->Prior_Q = malloc(MAX_ELEMS * (sizeof(ItemPQ*)));
	for (int i = 0; i < MAX_ELEMS; i++){
	    new->Prior_Q[i] = NULL;
	}
	new->N = 0;
	new->nSlots = MAX_ELEMS - 1;
	return new;
}

//checks if Priority Queue is empty
int PQEmpty(PQ p) {

		return (p->N == 0);
}

//Adds item (ItemPQ) to the priority queue.
//If an item with 'key' exists, it's 'value' is updated.
void addPQ(PQ pq, ItemPQ element) {
    
    //realloc more memory if array Prior_Q is full
    if(pq->N == pq->nSlots){
        pq->Prior_Q = realloc(pq->Prior_Q, 2*MAX_ELEMS);
        assert(pq->Prior_Q != NULL);
        pq->nSlots = pq->nSlots + MAX_ELEMS;
        for (int i = (pq->N + 1); i <= pq->nSlots; i++){
            pq->Prior_Q[i] = NULL;
        }
    }
    
    //update 'value' if 'key' exists
    int existsFlag = 0;
    int i = 1;
    while(i <= pq->N && pq->Prior_Q[i] != NULL){
        if(pq->Prior_Q[i]->key == element.key){
            existsFlag = 1;
            break;
        }
        i++;
    }
    
    if (existsFlag){
        updatePQ(pq, element);

    //insertion if key does not exist
    } else {
        ItemPQ *newNode = malloc(sizeof(ItemPQ));
        pq->N++;
        pq->Prior_Q[pq->N] = newNode;
        newNode->key = element.key;
        newNode->value = element.value;
        fixUp(pq->Prior_Q, pq->N);
    }
}

//Removes and returns the item (ItemPQ) with smallest 'value'.
//For items with equal 'value', observes FIFO.
ItemPQ dequeuePQ(PQ pq) {
	
	ItemPQ throwAway;
	throwAway.key = pq->Prior_Q[1]->key;
	throwAway.value = pq->Prior_Q[1]->value;
	free(pq->Prior_Q[1]);
	pq->Prior_Q[1] = pq->Prior_Q[pq->N];
	pq->N--;
	fixDown(pq->Prior_Q, 1, pq->N);
	return throwAway;
}

//Updates item with a given 'key' value, by updating that item's value to the given 'value'.
//If item with 'key' does not exist in the queue, no action is taken
void updatePQ(PQ pq, ItemPQ element) {
    
    int i = 1;
    while (i <= pq->N){
        if((pq->Prior_Q[i]->key) == (element.key)){
            if ((element.value) < (pq->Prior_Q[i]->value)){
                pq->Prior_Q[i]->value = element.value;
                fixUp(pq->Prior_Q, i);
                return;
            } else if ((element.value) > (pq->Prior_Q[i]->value)){
                pq->Prior_Q[i]->value = element.value;
                fixDown(pq->Prior_Q, 1, pq->N);
                return;
            } 
        }
        i++;
    }

}

//prints Priority Queue for testing and visual inspection
void  showPQ(PQ pq) {
    
    int i = 1;
    while(pq->Prior_Q[i] != NULL && i <= pq->N){
        printf("(%d, %d)\n", pq->Prior_Q[i]->key, pq->Prior_Q[i]->value);
        i++;    
    }
}

//frees memory associated with Priority Queue
void  freePQ(PQ pq) {

    assert(pq != NULL);
    int i = 1;
    while (i <= pq->N && pq->Prior_Q[i] != NULL){
        ItemPQ *PQNode =  pq->Prior_Q[i];
        free(PQNode);
        i++;
    }
    free(pq->Prior_Q);
    free(pq);
}


//swaps two nodes of Priority Queue
static void swap(ItemPQ **a, int i, int j){

   ItemPQ *tmp = a[i];
   a[i] = a[j];
   a[j] = tmp;
}
 
//when a new element/node is inserted or updated (less than current value)
//to the queue it moves the element in the right place by going up the heap
static void fixUp(ItemPQ **a, int i){
    while(i > 1 && a[i/2]->value > a[i]->value){
        swap(a, i, i/2);
        i=i/2;
    }
}

//when the root element is removed from the heap or
//updated (more than the current value of Node), it moves 
//the element in the right place by going down the heap
static void fixDown(ItemPQ **a, int i, int N){
    
    while(2*i < N){
        int j = 2*i;
        
        if (j < N && a[j]->value > a[j+1]->value){
            j++;
        }
        
        if (! (a[i]->value > a[j]->value)) {
            break;
        }
        swap(a, i, j);
        i = j;
    }
}
