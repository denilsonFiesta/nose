//
//  Heap.H
//  
//
//  Created by Al1bi
//  Copyright © 2023 Denilson Fiesta. All rights reserved. xd
//

#ifndef Heap_h
#define Heap_h

typedef struct Heap Heap;

typedef struct Node {
     int  key;
     void * value;
} Node;

struct Node CreateNode( int key,  void * value);

int Empty(struct Heap* h);

struct Heap* CreateHeap(int capacity);

void ResizeHeap(struct Heap* h);

int LeftChild(struct Heap *h, int i);

int RightChild(struct Heap *h, int i);

int Parent(struct Heap *h, int i);

struct Node GetMax(struct Heap *h);

void PercolateDown(struct Heap* h, int i);

void PercolateUp(struct Heap* h, int i);

struct Node DeleteMax(struct Heap *h);

void Insert(struct Heap* h, struct Node data);

void DestroyHeap(struct Heap *h);



#endif /* Heap_h */

//joselito