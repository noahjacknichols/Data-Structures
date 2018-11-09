/*
-------------------------------------
File:    heap.c
Project: nich4770_a9
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-20
-------------------------------------
 */

//heap.c
#include "heap.h"

heap *new_heap(int capacity) {
	heap *hp = (heap*) malloc(sizeof(heap));
	hp->capacity = capacity;
	hp->size = 0;
	hp->data = (DATATYPE*) malloc(sizeof(DATATYPE) * capacity);
	return hp;
}

void insert(heap *h, DATATYPE value) {
//your implementation
	int *temp;

	//printf("h->size = %d\n", h->size);
	if (h->size == h->capacity) {
		h->capacity *= 2;
		temp = (int*) realloc(h->data, sizeof(int*) * h->capacity);
		if (temp) {
			h->data = temp;

		} else {
			temp = (int*) malloc(sizeof(int*) * h->capacity);
			if (temp) {
				memcpy(temp, h->data, sizeof(int*) * h->capacity);
				free(h->data);
				h->data = temp;

			}

		}
	}
	h->data[h->size] = value;
	heapify_up(h, h->size);
	h->size++;



}

void heapify_up(heap *h, int index) {
	int parent, val = h->data[index];
	while (index) {
		parent = (index - 1) >> 1;  //equivalent to parent = (index-1)/ 2;
		if (h->data[parent] <= val)
			break;
		else {
			h->data[index] = h->data[parent];
			index = parent;
		}
	}
	h->data[index] = val;
}

void heapify_down(heap *h, int index, int n) {
	int val = h->data[index];
	int ci = (index << 1) + 1;  //left child, equivalent to ci = index * 2 + 1;
	while (ci <= n) { // if has the left child
		if ((ci < n) && (h->data[ci] > h->data[ci + 1]))
			ci++;  // ci is now the child of bigger key

		if (h->data[ci] > val)
			break; // the both children has key values less the val, done stop.
		else {
			h->data[index] = h->data[ci]; //change key value by the bigger child's value
			index = ci;
			ci = (index << 1) + 1;
		}
	}
	h->data[index] = val;
}



DATATYPE extract_min(heap *h) {
//your implementation
	int *temp;

	//printf("\n h->size = %d\n", h->size);
	if (h->size - 1 <= (h->capacity / 4)) {
		h->capacity /= 2;
		temp = realloc(h->data, sizeof(int*) * h->capacity);
		if (temp) {
			h->data = temp;
		}
	}
	int ret = h->data[0];
	h->data[0] = h->data[h->size - 1];
	h->size--;
	heapify_down(h, 0, h->size - 1);
	return ret;



}

void decrease_key(heap *h, int node_index, int keyvalue) {
//your implementation

	h->data[node_index] = keyvalue;
	int temp = h->data[0];
	h->data[0] = h->data[node_index];
	h->data[node_index] = temp;
	heapify_down(h, 0, h->size - 1);
}

int find_index(heap *h, DATATYPE value) {
//your implementation
	int index = 0;
	//printf("\n");
	while (index < h->size) {
		//printf("value at %d is [%d]\n", index, h->data[index]);
		if (h->data[index * 2 + 2] > value) {
			index = index * 2 + 1;
		} else {
			index = index * 2 +2;

		}
		if (value == h->data[index]) {
			return index;
		}

	}



	return -1;
}

void display_heap(heap *hp) {
	printf("\nsize=%d;capacity=%d\n", hp->size, hp->capacity);
	if (hp->size > 0)
		printf("%d", hp->data[0]);
	if (hp->size > 1) {
		int i;
		for (i = 1; i < hp->size; i++)
			printf(", %d", hp->data[i]);
		printf("\n");
	}
}

int cmp(DATATYPE a, DATATYPE b) {
	return a <= b ? 1 : 0;
}
