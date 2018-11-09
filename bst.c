/*
-------------------------------------
File:    bst.c
Project: nich4770_a7
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-03
-------------------------------------
 */

#include "bst.h"

void display(tnode *root) {
	if (root) {
		if (root->left)
			display(root->left);
		printf("%s\t%6.1f\n", root->name, root->score);
		if (root->right)
			display(root->right);
	}
}

void insert(tnode **treepp, char *name, float score) {
	tnode *np = (tnode *) malloc(sizeof(tnode));
	if (np == NULL)
		return;

	strcpy(np->name, name);
	np->score = score;
	np->left = NULL;
	np->right = NULL;

	if (*treepp == NULL) {
		*treepp = np;
		return;
	}

	if (strcmp(name, (*treepp)->name) < 0)
		insert(&(*treepp)->left, name, score);
	else if (strcmp(name, (*treepp)->name) > 0)
		insert(&(*treepp)->right, name, score);
	else {
		printf("node of the value exits\n");
		free(np);
	}


}

void delete(tnode **treepp, char *name) {
	tnode *root = *treepp;
	tnode* np;

	if (root == NULL)
		return;

	if (strcmp(name, root->name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*treepp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*treepp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*treepp = np;
		} else if (root->left != NULL && root->right != NULL) {
			tnode* temp = (tnode*) get_smallest_element(root->right);
			strcpy(root->name, temp->name);
			root->score = temp->score;
			delete(&root->right, temp->name);
		}
	} else {
		if (strcmp(name, root->name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}
}




tnode* search(tnode *root, char *name) {
	tnode *tp = root;
	while (tp) {
		if (strcmp(name, tp->name) == 0) {
			return tp;
		} else if (strcmp(name, tp->name) < 0)
			tp = tp->left;
		else
			tp = tp->right;
	}

	return NULL;

}

void clean(tnode *root) {
	tnode *temp = NULL;

	if (root->left != NULL) {
		clean(root->left);
	}

	if (root->right != NULL) {
		clean(root->right);
	}

	free(root);
}
