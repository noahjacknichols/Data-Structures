/*
-------------------------------------
File:    avl.c
Project: nich4770_a8
file description
-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-06
-------------------------------------
 */

//avl.c
#include "avl.h"

// A utility functions
int height(tnode *np) {
	if (np == NULL)
		return 0;
	return np->height;
}



tnode* new_node(char *name, float score) {
	tnode *np = (tnode*) malloc(sizeof(tnode));
	strcpy(np->name, name);
	np->score = score;
	np->height = 1;  // new node is initially added at leaf
	np->left = NULL;
	np->right = NULL;
	return np;
}

int get_height(tnode *root) {
	return root->height;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}

}

tnode *rotate_right(tnode *y) {
	tnode *x = y->left;
	tnode *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + max(height(y->left), height(y->right));
	x->height = 1 + max(height(x->left), height(x->right));
	return x;
}

tnode *rotate_left(tnode *x) {
	tnode *y = x->right;
	tnode *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return y;
}

void insert(tnode **rootp, char *name, float score) {
	tnode *np = new_node(name, score);
	if (np == NULL) {
		return;
	}

	if (*rootp == NULL) {

		*rootp = np;
		return;
	}

	if (strcmp(name, (*rootp)->name) <= 0)
		insert(&(*rootp)->left, name, score);
	else if (strcmp(name, (*rootp)->name) >= 0)
		insert(&(*rootp)->right, name, score);
	else {
		printf("node of the value exists\n");
		free(np);

	}

	tnode *root = *rootp;
	root->height = 1 + max(height(root->left), height(root->right));
	//printf("node: %s |", root->name);
	int balance = balance_factor(root);

	if (balance > 1) {
		printf("a");
		if (balance_factor(root->left) >= 0) {
			printf("c");
			*rootp = rotate_right(root);
		} else {
			root->left = rotate_left(root->left);
			*rootp = rotate_right(root);
		}
	} else if (balance < -1) {
		//printf("b");
		if (balance_factor(root->left) <= 0) {
			printf("d");
			*rootp = rotate_left(root);
		} else {
			//printf("e");
			root->right = rotate_right(root->right);
			*rootp = rotate_left(root);
		}
	}


}

tnode *extract_smallest_node(tnode **rootp) {
	tnode *tnp = *rootp;
	tnode *parent = NULL;
	if (tnp == NULL) {
		return NULL;
	} else {
		while (tnp->left) {
			parent = tnp;
			tnp = tnp->left;
		}
		if (parent == NULL)
			*rootp = tnp->right;
		else
			parent->left = tnp->right;
		tnp->left = NULL;
		tnp->right = NULL;
		return tnp;
	}
}

tnode *search(tnode *root, char *name) {
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

void delete(tnode **rootp, char *name) {
	tnode *root = *rootp;
	tnode *np;

	if (!root) {
		return;
	}
	if (strcmp(name, root->name) == 0) {

		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {
		if (strcmp(name, root->name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}

}

void clean_tree(tnode **rootp) {
	if (*rootp) {
		tnode *np = *rootp;
		if (np->left)
			clean_tree(&np->left);
		if (np->right)
			clean_tree(&np->right);
		free(np);
	}
	*rootp = NULL;

}

void merge_tree(tnode **rootp1, tnode *root2) {
	tnode *np = root2;

	if (np == NULL) {
		return;
	} else {
		if (np->left) {
			merge_tree(rootp1, np->left);
		}
		if (np->right) {
			merge_tree(rootp1, np->right);
		}

		insert(rootp1, np->name, np->score);

	}




}

int balance_factor(tnode* np) {
	int balance = 0;
	if (np != NULL) {
		if (np->left != NULL) {
			//printf("left");
			balance = balance + height(np->left);
		}
		if (np->right != NULL) {
			//printf("right	");
			balance = balance - height(np->right);
		}
	}
	return balance;
}

void display_inorder(tnode *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("%-22s%3.1f\n", root->name, root->score);
		if (root->right)
			display_inorder(root->right);
	}
}

void display_tree(tnode *root, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++)
			printf("%c", ' ');
		printf("%s", "|___");
		printf("%s %3.1f %d %d\n", root->name, root->score, get_height(root),
				balance_factor(root));
		display_tree(root->left, prelen + 4);
		display_tree(root->right, prelen + 4);
	}
}

