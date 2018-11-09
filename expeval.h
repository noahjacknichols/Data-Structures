/*
-------------------------------------
File:    expeval.h
Project: nich4770_a9
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-21
-------------------------------------
 */
#ifndef EXPEVAL_H_
#define EXPEVAL_H_

#include "hash.h"
#include "stack.h"

int getPriority(char opr);
int isOperator(char op);
int isSymbol(char s);

void trim_space(char *s);
int infix_eval(hashdata *hashmap[], char *infixstr);
int statement_process(hashdata *hashmap[], char* statement);




#endif /* EXPEVAL_H_ */
