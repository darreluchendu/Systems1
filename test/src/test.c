
#include "date.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	int next;
	TLDNode nodes[];
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

TLDIterator *tldlist_iter_create(TLDList *tld){
	TLDIterator * iter = malloc(sizeof(TLDIterator));
	iter->root=tld->root;
	iter->nodes[0]=*iter->root;
	iter->next=1;
	return iter;

}


TLDNode getNodes(TLDIterator * iter){
//	if (iter->nodes[1]==NULL){
//		i= 1;
//	}
	//printf("%s", iter->root->tld_name);
	TLDNode nodes(TLDNode *root, int i){
		if (root->tld_name!= NULL){
		iter->nodes[i]=nodes(iter->root->left,i+1);
		//iter->nodes[i+1]=nodes(iter->root->right,i+1);
		}
		return *iter->nodes;
	}
	nodes(iter->root,1);
	return *iter->nodes;

}
int main(){
	TLDNode **list=malloc(sizeof(TLDNode) * 50);;
	TLDList * test = malloc(sizeof(TLDList));
	//char * a,b,c,d,e= "a","b","c","d","e";
	char * a ="a";
	char * b ="b";
	char * c ="c";
	char * d ="d";
	char * e ="e";
	test->root=newNode(a, NULL);
	test->root->left=newNode(b, test->root);
	test->root->right=newNode(c, test->root);
	test->root->left->right=newNode(d, test->root->left);
	test->root->right->left=newNode(e, test->root->right);

	//TLDIterator *iter= tldlist_iter_create(test);
	//printf ("%s", test->root->tld_name);
	TLDNode i;
	//list[7]=&i;
	//list[7] = NULL;


	void tree_to_array(TLDNode* tree, TLDNode *array, int *index){
	     if (tree != NULL){
	    	 array[*index] = *tree;
	    	 //printf("%s ",tree->tld_name);
	    	 //printf("%d ",index);
	    	 *index=*index+1;
	    	 tree_to_array(tree->left, array, index);
			 tree_to_array(tree->right, array, index);
	     }
	     else{
	    	 return;
	     }
	}
	//ree_to_array(test->root, *list,&i);

	if (list[7]){
		printf("red");
	}
	else{
		printf("reeeeeeeeeee");
	}
	return 0;
}
