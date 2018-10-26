#include "tldlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tldnode {
	int balance;
	int height;
	int node_count;
	char * tld_name;
	TLDNode *left;
	TLDNode *right;
	TLDNode *parent;
};

struct tldlist {
	Date *begin;
	Date *end;
	TLDNode *root;
	int list_count;
};

struct tlditerator{
	TLDNode *root;
	TLDNode **list;
	int next;
};

TLDNode * newNode(char * name, TLDNode * parent) {
	TLDNode * node = malloc(sizeof(TLDNode));
	node->tld_name = name;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;  // new node is initially added at leaf
	node->node_count++;
	return (node);
}

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int height(TLDNode * n) {
	if (n == NULL)
		return -1;
	return n->height;
}

void reheight(TLDNode * node) {
	if (node != NULL) {
		node->height = 1 + max(height(node->left), height(node->right));
	}
}
void setBalance(TLDNode * n) {
	reheight(n);
	n->balance = height(n->right) - height(n->left);
}

TLDNode * rotateLeft(TLDNode *a) {

	TLDNode *b = a->right;
	b->parent = a->parent;

	a->right = b->left;

	if (a->right != NULL)
		a->right->parent = a;

	b->left = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		} else {
			b->parent->left = b;
		}
	}

	setBalance(a);
	setBalance(b);

	return b;
}

void tree_to_array(TLDNode* tree, TLDNode *array, int  * index){
	 if (tree != NULL){
		 array[*index] = *tree;
		 *index=*index+1;
		 tree_to_array(tree->left, array, index);
		 tree_to_array(tree->right, array, index);
	 }
	 else{
		 return;
	 }
	}

TLDNode * rotateRight(TLDNode *a) {

	TLDNode * b = a->left;
	b->parent = a->parent;

	a->left = b->right;

	if (a->left != NULL)
		a->left->parent = a;

	b->right = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		} else {
			b->parent->left = b;
		}
	}

	setBalance(a);
	setBalance(b);

	return b;
}

TLDNode * rotateLeftThenRight(TLDNode * n) {
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

TLDNode * rotateRightThenLeft(TLDNode * n) {
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

void rebalance(TLDNode *n) {
	setBalance(n);

	if (n->balance == -2) {
		if (height(n->left->left) >= height(n->left->right))
			n = rotateRight(n);
		else
			n = rotateLeftThenRight(n);

	} else if (n->balance == 2) {
		if (height(n->right->right) >= height(n->right->left))
			n = rotateLeft(n);
		else
			n = rotateRightThenLeft(n);
	}

	if (n->parent != NULL) {
		rebalance(n->parent);
	}
}


//TLDNode * newNode(char * name) {
//	TLDNode * node = malloc(sizeof(TLDNode));
//    node->tld_name   = name;
//    node->left   = NULL;
//    node->right  = NULL;
//    node->height = 1;  // new node is initially added at leaf
//    node->node_count++;
//    return(node);
//}
//TLDNode *rightRotate(TLDNode *y)
//{
//	TLDNode *x = y->left;
//	TLDNode *T2 = x->right;
//
//    // Perform rotation
//    x->right = y;
//    y->left = T2;
//
//    // Update heights
//    y->height = max(height(y->left), height(y->right))+1;
//    x->height = max(height(x->left), height(x->right))+1;
//
//    // Return new root
//    return x;
//}
//
//// A utility function to left rotate subtree rooted with x
//// See the diagram given above.
//TLDNode *leftRotate(TLDNode *x)
//{
//	TLDNode *y = x->right;
//	TLDNode *T2 = y->left;
//
//    // Perform rotation
//    y->left = x;
//    x->right = T2;
//
//    //  Update heights
//    x->height = max(height(x->left), height(x->right))+1;
//    y->height = max(height(y->left), height(y->right))+1;
//
//    // Return new root
//    return y;
//}
//
//// Get Balance factor of node N
//int getBalance(TLDNode *N)
//{
//    if (N == NULL){
//        return 0;
//    return height(N->right) - height(N->left);
//	}
//}

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end) {
	TLDList *list = malloc(sizeof(TLDList));
	list->begin = begin;
	list->end = end;

	if (list) {
		return list;
	} else {
		return NULL;
	}
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld) {
	tld = NULL;
	free(tld);
}
/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d) {
	if (date_compare(tld->begin, d) < 0 && date_compare(tld->end, d) > 0) {

		if (tld->root == NULL) {

			TLDNode * root = newNode(hostname, NULL);
			tld->root = root;
			tld->list_count++;

			root = NULL;
			free(root);
			return 1;
		}
		TLDNode* n = tld->root;
		while (1) {
			if (n->tld_name == hostname) {
				n->node_count++;
				tld->list_count++;
				return 1;
			}

			TLDNode * parent = n;
			int goLeft = strcmp(n->tld_name, hostname);
			n = goLeft ? n->left : n->right;

			if (n == NULL) {
				if (goLeft) {
					parent->left = newNode(hostname, parent);

				} else {
					parent->right = newNode(hostname, parent);
				}
				tld->list_count++;
				rebalance(parent);
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}
/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld) {
	return (long) tld->list_count;
}
/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
	TLDIterator * iter = malloc(sizeof(TLDIterator));
	iter->root=tld->root;
	iter->list= malloc(sizeof(TLDNode) * tld->list_count);
	iter->next=1;
	tree_to_array(iter->root,*iter->list,&iter->next);
	return iter;

}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){

	TLDNode * next =iter->list[iter->next];

	if (next !=NULL){
		iter->next++;
		return next;
	}else{
		return NULL;
	}
}
/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
	int i =0;
	while(iter->list[i]){
		iter->list[i]=NULL;
		free(iter->list[i]);
		iter->list=NULL;
		free(iter->list);
		i++;
	}
	iter=NULL;
	free(iter);
}
/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node) {
	return node->tld_name;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
	return node->node_count;
}
