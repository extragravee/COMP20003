/*
Created by Sidakpreet Mann - 921322
sidakpreetm@student.unimelb.edu.au

Header file for bst.c includes bst dictionary structure and functions.
Includes:
Bst node structure
Function declarations from 'bst.c'
Constants used by files that reference bst.c
*/

#ifndef BST_H

#define BST_H
#define MAXFIELDSIZE 128
#define MAXBUFFERSIZE 256
#define END_OF_LINE -1
#define OUTFILE_ARG 2
#define NULLBYTE_SPACE 1
#define NEWLINE '\n'
#define EMPTY_STRING_LEN 0
#define LAST_CHAR 1
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
Constructs the entire BST dictionary
*/
struct bst* construct_bst(char **argv);
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

/*
Traverses the BST dictionary using PULocationID as a search key, writes 
the matching PUDatetimes to the output file and comprisons to stdout
*/
void traverse_bst(char* key, struct bst* bst, FILE* out_file);

/*
Check if a match was found during the traversal. Returns found_match flag variable
*/
int get_match_found();

/*
Return the number of searches performed during the traversal
*/
int get_search_count();

/*
Resets the the match_found flag and the number of searches performed during traversal
*/
void reset_static_vars();

#endif
