
#include "stack.h"

snode *new_node(int val, int type) {
	snode *np = (snode *) malloc(sizeof(snode));
	np->data = val;
	np->type = type;
	np->next = NULL;
	return np;
}

void push(snode **topp, snode *np) {
	if (*topp == NULL) {
		*topp = np;
		np->next = NULL;
	} else {
		np->next = *topp;
		*topp = np;
	}
}

snode *pop(snode **topp) {
	if (*topp) {
		snode *tmp = *topp;
		*topp = tmp->next;
		tmp->next = NULL;
		return tmp;

	} else
		return NULL;
}

void push_back(snode **topp, snode **bottom, snode *np) {
	if (*topp == NULL) {
		*topp = np;
		*bottom = np;
		np->next = NULL;
	} else {
		(*bottom)->next = np;
		*bottom = np;
	}
}



void clean(snode **topp) {
	snode *curr = *topp;
	while (curr) {
		snode *tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	*topp = NULL;
}

void display_stack(snode *top) {
	while (top) {
		if (top->type == 0)
			printf("%d ", top->data);
		else
			printf("%c ", top->data);

		top = top->next;
	}
}




