#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"


typedef struct Heap{
  struct Node* array;
  int count; 
  int capacity;
}Heap;

struct Node CreateNode( int key,  void * value) {
    struct Node nodito;
    nodito.key = key;
    nodito.value = value;
    return nodito;
}

struct Heap* CreateHeap( ){

  struct Heap* heap = (struct Heap*) calloc(1, sizeof(struct Heap) );
  heap->count = 0;
  heap->capacity = 3;
  heap->array = (struct Node*) calloc(heap->capacity, sizeof( struct Node));

  return heap;
}

int Empty(struct Heap* h){
  if(h->count == 0) return 1;
  else return 0;
}

void ResizeHeap(struct Heap* h){
  struct Node* array_old = h->array;
  h->array = (struct Node*) calloc(h->capacity *2, sizeof(struct Node));
  for(int i =0; i < h->capacity; i++){
    *(h->array+i) = *(array_old+i);
  }
  h->capacity*=2;
  free(array_old);
}

int LeftChild(struct Heap *h, int i){
  int left = 2*i + 1;
  if(left >= h->count) return -1;
  return left;
}

int RightChild(struct Heap *h, int i){
  int right = 2*i + 2;
  if(right >= h->count) return -1;
  return right;
}

int Parent(struct Heap *h, int i){
  if(i <= 0 || i>=h->count) return -1;
  return (i-1)/2;
}

struct Node GetMax(struct Heap *h){
  if(Empty(h)){
    struct Node nose;
    printf("La heap esta vacia wachin \n");
    return nose;
  }
  return *(h->array);
}

void PercolateDown(struct Heap* h, int i){
  int l, r, max;
  struct Node temp;
  l = LeftChild(h, i);
  r = RightChild(h, i);
  if( l != -1 && (*(h->array+l)).key > (*(h->array+i)).key ) max = l;
  else max = i;

  if( r != -1 && (*(h->array+r)).key > (*(h->array+max)).key ) max = r;
  
  if(max != i){
    temp = *(h->array+i);
    *(h->array+i) = *(h->array+max);
    *(h->array+max) = temp;

    PercolateDown(h, max);
  }

  
}

void PercolateUp(struct Heap* h, int i){
  int parent = Parent(h, i);
  if(parent == -1) return;

  if( (*(h->array+i)).key > (*(h->array+parent)).key ){
    struct Node temp;
    temp = *(h->array+i);
    *(h->array+i) = *(h->array+parent);
    *(h->array+parent) = temp;

    PercolateUp(h, parent);
  }
  

}


struct Node DeleteMax(struct Heap *h){
  struct Node data;

  if(Empty(h)){
    printf("La heap esta vacia wachin \n");
    return data;
  }
  data = *(h->array);
  *(h->array) = *(h->array+h->count-1);
  h->count--;
  PercolateDown(h, 0);
  return data;  
}

void Insert(struct Heap* h, struct Node data){

  int i;

  if(h->count == h->capacity) ResizeHeap(h);
  
  h->count++;

  i = h->count -1;
  *(h->array + i) = data;
  
  PercolateUp(h, i);
  
}

void DestroyHeap(struct Heap *h){

  if(h == NULL) return;
  free(h->array);
  free(h);
  h = NULL;
}
