/*
-------------------------------------
File:    avl.h
Project: nich4770_a8
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-06
-------------------------------------
 */
#ifndef AVL_H_
#define AVL_H_


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
	char name[20];
	float score;
	int height;
	struct node *left;
	struct node *right;

} tnode;

tnode *new_node(char *, float);
tnode *rotate_left(tnode *);
tnode *rotate_right(tnode *);
void insert(tnode **, char *, float);
void delete(tnode **, char *);
tnode *extract_smallest_node(tnode **rootp);
tnode *search(tnode *, char *);
void clean_tree(tnode **);

void merge_tree(tnode **, tnode *); //merge tree of root2 into root1,

int height(tnode *);
int get_height(tnode *);
int balance_factor(tnode *);
void display_inorder(tnode *);
void display_tree(tnode *root, int prelen);

int max(int a, int b); //return a>=b?a:b;

#endif /* AVL_H_ */
