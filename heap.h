/*
-------------------------------------
File:    heap.h
Project: nich4770_a9
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-20
-------------------------------------
 */
#ifndef HEAP_H_
#define HEAP_H_

#define SIZE 20
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATATYPE int
#define MIN_CAPACITY 4

typedef struct heap {
	unsigned int capacity;
	unsigned int size;
	DATATYPE *data;
} heap;

heap *new_heap(int capacity);
void insert(heap *, DATATYPE);
DATATYPE extract_min(heap *);
void decrease_key(heap *h, int nodeindex, int newkeyvalue);
int find_index(heap *, DATATYPE);
void heapify_up(heap *, int);
void heapify_down(heap *, int, int);


void display_heap(heap *);
int cmp(DATATYPE a, DATATYPE b);


#endif /* HEAP_H_ */
