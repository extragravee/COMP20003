/*
Header file for bst.c includes bst dictionary structure and functions
Structure
Functions declarations
*/

#ifndef BST_H
#define BST_H

/*
structure of binary tree nodes
*/
struct bst{
	struct bst* left;
	struct bst* right;
	struct trip* trip;
	char* key;
	struct duplicate_ll* duplicates;
};

/*
Takes parent pointer (null for the root), and returns tree with the 
inserted node at the right position. Returns item in tree with it's
left and right pointers set to NULL
*/
struct bst* insert_node(struct bst* parent, struct trip* trip);

/*
Takes node pointer and frees all of its children and itself
by default (if pointer is NULL), does nothing
frees children recursively
*/
void free_tree(struct bst* parent);

/*
Find trip in dictionary, write results to output file and comparisons to stdout
*/
void find_in_bst(char* find_key, struct bst* bst, FILE *out_file);

#endif