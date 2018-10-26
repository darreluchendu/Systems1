#include "tldlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tldnode{
    int height;
	int node_count;
	char * tld_name;
	TLDNode *left;
	TLDNode *right;
};

struct tldlist{
	Date *begin;
	Date *end;
	TLDNode *root;
	int list_count;
};

int max(int a, int b){
	if (a>b){
		return a;
	}else{
		return b;
	}
}

int height(TLDNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
TLDNode * newNode(char * name) {
	TLDNode * node = malloc(sizeof(TLDNode));
    node->tld_name   = name;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->node_count++;
    return(node);
}
TLDNode *rightRotate(TLDNode *y)
{
	TLDNode *x = y->left;
	TLDNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TLDNode *leftRotate(TLDNode *x)
{
	TLDNode *y = x->right;
	TLDNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(TLDNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end){
	TLDList *list=malloc(sizeof(TLDList));
	list->begin=begin;
	list->end=end;

	if (list){
		return list;
	}else{
		return NULL;
	}
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld){
	tld=NULL;
	free(tld);
}
/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
	if (date_compare(tld->begin,d)<0 && date_compare(tld->end,d)>0 ){

		if (tld->root == NULL){

			TLDNode * node = newNode(hostname);
			tld->root = node;
			tld->list_count++;

			node= NULL;
			free(node);
			return 1;
		}
		TLDNode* n = tld->root;




	}else{
		return 0;
	}
}
/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
	return (long) tld->list_count;
}
/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld);

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter);

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter);

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
	return node->tld_name;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
	return node->node_count;
}
