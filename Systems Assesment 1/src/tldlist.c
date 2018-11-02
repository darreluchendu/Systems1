#include "tldlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

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
	TLDNode * next;
	int size;
};

TLDNode * newNode(char * name, TLDNode * parent) {
	TLDNode * node = (TLDNode*)  malloc(sizeof(TLDNode));
	int len=strlen(name);
	char *p = (char *) malloc(sizeof(char *)* (len+1));
	strcpy(p,name);
	node->tld_name = p;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	  // new node is initially added at leaf
	node->node_count=1;
	node->height=1;

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
	if (n == NULL){
		return -1;
	}
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

	//TLDNode *b = (TLDNode *) malloc(sizeof(TLDNode));
	TLDNode *b=a->right;
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
//
//void tree_to_array(TLDNode* tree, TLDNode *array, int  * index){
//		 if (tree != NULL){
//			// TLDNode * x =(TLDNode *) malloc(sizeof(TLDNode));
//			// *x =*tree;
//			 //printf("%s index: %d",tree->tld_name, *index);
//			 array[*index] = *tree;
//			 //printf("%s",array[*index].tld_name);
//			 *index=*index+1;
//			// x=NULL;
//			 //free(x);
//			 tree_to_array(tree->left, array, index);
//			 tree_to_array(tree->right, array, index);
//
//		 }
//		 else{
//			 return;
//		 }
//		}

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

void rebalance(TLDNode *n, TLDList* tld) {
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
		rebalance(n->parent,tld);
	} else {
		tld->root=n;
	}
}

TLDNode* search(TLDNode* node, char * tld_name){
	// Base Cases: node is null or tld_name is present at node
	if (node == NULL || strcmp(node->tld_name, tld_name)==0)
	   return node;

	// tld_name is greater than node's tld_name
	if (strcmp(tld_name,node->tld_name)) {
	   return search(node->right, tld_name);
	}

	// tld_name is smaller than node's tld_name
	return search(node->left, tld_name);
}


TLDList * tldlist_create(Date *begin, Date *end){
	TLDList *tld= malloc(sizeof(TLDList));
	tld->begin=date_duplicate(begin);
	tld->end=date_duplicate(end);
	tld->list_count=0;
	tld->root=NULL;

	return tld;
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
	hostname= hostname + strlen(hostname) - 3;
	if (hostname[0]=='.'){
		hostname= hostname + strlen(hostname) - 2;
	}
	if(d==NULL){
		return 0;
	}

	if (date_compare(tld->begin, d) < 0 && date_compare(d, tld->end) > 0) {
		return 0;
	}
		if (tld->root == NULL) {

			TLDNode * root = newNode(hostname, NULL);
			tld->list_count++;
			tld->root = root;
			//tld->list_count= tld->list_count+1;
			root = NULL;
			free(root);
			return 1;
		}
		TLDNode* n = tld->root;

		while (1) {
//			//printf ("%s current :%s\n",tldnode_tldname(n),hostname);
			if (strcmp(n->tld_name, hostname)==0) {
				n->node_count++;
				tld->list_count++;
				return 1;
			}

			// C function to search a given key in a given BST
//			TLDNode *dupe=search(tld->root, hostname);
//						if (dupe){
//
//							dupe->node_count++;
//							tld->list_count++;
//							return 1;
//						}


//			TLDNode *duplicate=search(n, hostname);
//			if (duplicate){
//
//				duplicate->node_count++;
//				tld->list_count++;
//				return 1;
//			}

			TLDNode * parent = n;
			int goLeft = strcmp(tldnode_tldname(n), hostname);
			if (goLeft>0){
				n=n->left;
			}else{
				n=n->right;
			}

			if (n == NULL) {
				if (goLeft>0) {
					parent->left = newNode(hostname, parent);

				} else {
					parent->right = newNode(hostname, parent);
				}
				tld->list_count++;

				rebalance(parent,tld);
				break;
			}

		}

		return 1;
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
	if (iter){
		iter->next = tld->root;
	}

	while (iter->next->left != NULL){
	   iter->next = iter->next->left;
	}
	iter->size=0;
	 return iter;

}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
	TLDNode * r;
	if (iter->next){
		r =iter->next;
	}else{
		return NULL;
	}

	if(iter->next->right != NULL) {
		iter->next = iter->next->right;
		while (iter->next->left != NULL)
			iter->next = iter->next->left;
		iter->size++;
		return r;
	}

	while(1) {
		if(iter->next->parent == NULL) {
			iter->next = NULL;
			iter->size++;
			return r;
		}
		if(iter->next->parent->left == iter->next) {
			iter->next = iter->next->parent;
			iter->size++;
		   return r;
		}

		iter->next = iter->next->parent;
	}
}
/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
//	int i =0;
//	while(iter->list[i]){
//		//iter->list[i]=NULL;
//		//free(iter->list[i]);
//		//free(iter->list);
//		i++;
//	}
	iter=NULL;
	free(iter);
}
/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node) {
	//int len=strlen(node->tld_name);
	//char *p = malloc(sizeof(char *)* (len+1));
	//strcpy(p,node->tld_name);
	return node->tld_name;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
	return node->node_count;
}
