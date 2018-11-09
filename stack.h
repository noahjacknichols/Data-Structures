/*
-------------------------------------
File:    stack.h
Project: nich4770_a9
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-21
-------------------------------------
 */
#ifndef STACK_H_
#define STACK_H_


#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "hash.h"

typedef struct node {
	int data;
	int type; //0:integer number; 1:opeator;2:symbol; 3:( ; 4:symbol
	struct node *next;
} snode;

snode *new_node(int, int);
void push(snode **, snode *);
snode *pop(snode **);
void push_back(snode **, snode **, snode *);
void clean(snode **);
void display_stack(snode *top);


#endif /* STACK_H_ */
