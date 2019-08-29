/*
Header file for bst.c includes bst dictionary structure and functions
Structure
Functions declarations
*/

/*
defines structure of binary tree nodes
*/
struct bst; 

/*
Takes parent pointer (null for the root), and returns tree with the 
inserted node at the right position. Returns item in tree with it's
left and right pointers set to NULL
*/
struct bst* insert_node(struct bst* parent, struct trip* new_trip);

/*
Takes node pointer and frees all of its children and itself
by default (if pointer is NULL), does nothing
frees children recursively
*/
void free_tree(struct bst* parent);

