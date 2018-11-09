/*
-------------------------------------
File:    bst.h
Project: nich4770_a7
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-03
-------------------------------------
 */
#ifndef BST_H_
#define BST_H_


//bst.h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
	char name[20];
	float score;
	struct node *left;
	struct node *right;
} tnode;

void display(tnode *);
void insert(tnode **, char *, float);
void delete(tnode **, char *);
tnode *search(tnode *, char *);
void clean(tnode *);


#endif /* BST_H_ */
