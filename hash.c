/*
-------------------------------------

File:    hash.c
Project: nich4770_a9
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-22
-------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"


int hash(char *word) {

	unsigned int hash = 0, i;
	for (i = 0; word[i] != '\0'; i++) {
		hash = 31 * hash + word[i];
	}
	return hash % SIZE;

}
hashdata *search(hashdata *hashmap[], char *name) {

	int hashIndex = hash(name);
	while (hashmap[hashIndex] != NULL) {
		if (strcmp(hashmap[hashIndex]->name, name)
				== 0&& hashmap[hashIndex] != NULL) {
			return hashmap[hashIndex];
		}
		++hashIndex;
		hashIndex %= SIZE;
	}
	return NULL;


}
hashdata *put(hashdata *hashmap[], char *name, int data) {
	int hashIndex = hash(name);


	int counter = 0;
	while (hashmap[hashIndex] != NULL && counter < SIZE) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0) {
			printf("first\n");
			hashmap[hashIndex]->data = data;
			hashmap[hashIndex]->key = hashIndex;
			return hashmap[hashIndex];
		}
		++hashIndex;
		hashIndex %= SIZE;
		counter++;
	}

	if (hashmap[hashIndex] == NULL) {
		hashmap[hashIndex]->data = data;
		hashmap[hashIndex]->key = hashIndex;

	}
	return NULL;



}
int get(hashdata *hashmap[], char *name) {
	int hashIndex = hash(name), counter = 0;
	while (hashmap[hashIndex] != NULL && counter < SIZE) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0
				&& hashmap[hashIndex]->key != -1) {
			return hashmap[hashIndex]->data;
		}
		++hashIndex;
		hashIndex %= SIZE;
		counter++;
	}
	return -1;

}
int contains(hashdata *hashmap[], char *name) {

	if (search(hashmap, name) != NULL) {
		return 1;
	}

	return 0;

}
void display_hash(hashdata *hashmap[], int opt) {
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if (hashmap[i]->key != -1)
			printf("(%d,%d,%s)\n", i, hashmap[i]->data, hashmap[i]->name);
		else
			printf("(%d, NULL)\n", i);
	}
	printf("\n");

}

int remove_item(hashdata *hashmap[], char *name) {

	int hashIndex = hash(name), counter = 0;
	while (hashmap[hashIndex] != NULL && counter < SIZE) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0
				&& hashmap[hashIndex]->key != -1) {
			hashmap[hashIndex]->key = -1;
			return 1;
		}
		++hashIndex;
		counter++;
		hashIndex %= SIZE;
	}
	return 0;

}
int clear(hashdata *hashmap[]) {

	int i = 0;
	while (i < SIZE) {
		free(hashmap[i]);
		i++;
	}
	return size(hashmap);

}
int size(hashdata *hashmap[]) {

	int hashIndex = 0;
	int counter = 0;
	int size = 0;

	while (counter < SIZE) {
		if (hashmap[hashIndex] != NULL && hashmap[hashIndex]->key != -1) {
			size++;
		}
		counter++;
		++hashIndex;
		hashIndex %= SIZE;

	}
	return size;
}
