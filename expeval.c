/*
-------------------------------------
File:    expeval.c
Project: nich4770_a9

-------------------------------------
Author:  noah nichols
ID:      160554770
Email:   nich4770@mylaurier.ca
Version  2018-03-23
-------------------------------------
 */

#include "expeval.h"

int getPriority(char op) {
	if (op == '/' || op == '*' || op == '%')
		return 1;
	else if (op == '+' || op == '-')
		return 0;
	return 0;
}

int isOperator(char op) {
	if (op == '/' || op == '*' || op == '%' || op == '+' || op == '-')
		return 1;
	else
		return 0;
}

int isSymbol(char s) {
	if (!isOperator(s) && !isdigit(s) && s != ')' && s != '(') {
		return 1;
	} else
		return 0;
}

int infix_eval(hashdata *hashmap[], char *infixstr) {
	int result = 0;
	snode *numstack;
	snode *opstack;


	while (*infixstr != '\0') {
		if (!isOperator(*infixstr)) {
			if (*infixstr == '(') {

				snode *np = new_node(*infixstr, 3);
				push(&opstack, np);
			} else {
				if (*infixstr >= 'a' && *infixstr <= 'z') {
					char *letter = infixstr;

					int value = get(hashmap, letter);
					if (value != -1) {
						snode *np = new_node(value, 0);
						push(&numstack, np);
					}
				} else {
					snode *np = new_node(*infixstr, 0);
					push(&numstack, np);
				}
			}
		} else if (isOperator(*infixstr)) {
			snode *temp = pop(&opstack);
			int prec;

			if (temp == NULL) {
				snode *np = new_node(*infixstr, 1);
				push(&opstack, np);
			} else {
				if (getPriority(*infixstr) == 1) {
					if (temp->type < 2) {
						snode *np = new_node(*infixstr, 1);
						push(&opstack, np);
					} else if (*infixstr == '(') {
						snode *np = new_node(*infixstr, 3);
						push(&opstack, np);
					} else if (*infixstr == ')') {
						int val1 = pop(&numstack)->data;
						int val2 = pop(&numstack)->data;
						if (temp->data == '*') {
							result = val1 * val2;
						} else if (temp->data == '/') {
							result = val1 / val2;
						} else if (temp->data == '%') {
							result = val1 % val2;
						} else if (temp->data == '+') {
							result = val1 + val2;
						} else if (temp->data == '-') {
							result = val1 - val2;
						}
						snode *np = new_node(val1, 0);
						push(&numstack, np);
					} else {
						int val1 = pop(&numstack)->data;
						int val2 = pop(&numstack)->data;
						if (temp->data == '*') {
							result = val1 * val2;
						} else if (temp->data == '/') {
							result = val1 / val2;
						} else if (temp->data == '%') {
							result = val1 % val2;
						} else if (temp->data == '+') {
							result = val1 + val2;
						} else if (temp->data == '-') {
							result = val1 - val2;
						}
						snode *np = new_node(result, 0);
						push(&numstack, np);
					}
				}
			}
		} else {
			snode *temp = pop(&opstack);
			int val1 = pop(&numstack)->data;
			int val2 = pop(&numstack)->data;
			if (temp->data == '*') {
				result = val1 * val2;
			} else if (temp->data == '/') {
				result = val1 / val2;
			} else if (temp->data == '%') {
				result = val1 % val2;
			} else if (temp->data == '+') {
				result = val1 + val2;
			} else if (temp->data == '-') {
				result = val1 - val2;
			}

		}
		infixstr = infixstr + 1;
	}


	//convert prefix to postfix expression using stack as working data structure and queue to hold postfix expression
	//using the existing values of symbols from hashtab to do evaluation, return the final evaluation result
	return result;
}

int statement_process(hashdata *hashmap[], char* statement) {
	char s[10] = { 0 };
	char *dest = strstr(statement, "=");
	if (dest)
		*dest = '\0';
	else
		dest = statement;
	strcpy(s, statement);
	//printf("s: %s", dest + 1);
	if (isSymbol(s[0])) {
		put(hashmap, s, infix_eval(hashmap, dest + 1));
		return 1;
	}
	return 0;
}

void trim_space(char *s) {
	if (s == NULL || *s == '\0')
		return;
	char *p = s, *dp = s;
	while (*p) {
		if (*p != ' ')
			*dp++ = *p;
		p++;
	}
	*dp = '\0';
}

