#pragma once

/**
 * @struct bstNode
 * @brief Represents a single node in a binary search tree.
 */
typedef struct bstNode {
    int data_item;
    struct bstNode* left;
    struct bstNode* right;
} *BSTNodePtr;

/**
 * @struct bst
 * @brief Represents a binary search tree.
 */
typedef struct bst {
    BSTNodePtr root;
} BST;

/**
 * @brief Creates a new, empty binary search tree.
 */
BST new_bst();

/**
 * @brief Finds a node with a given data item in a binary search tree.
 */
BSTNodePtr find_bst(BST* self, int n);

/**
 * @brief Inserts a node with a given data item into a binary search tree.
 */
void insert_bst(BST* self, int n);

/**
 * @brief Deletes a node with a given data item from a binary search tree.
 */
void delete_bst(BST* self, int n);

/**
 * @brief Prints the BST in in-order traversal.
 */
void print_in_order_bst(BST* self);

/**
 * @brief Prints the BST in pre-order traversal.
 */
void print_pre_order_bst(BST* self);

/**
 * @brief Prints the BST in post-order traversal.
 */
void print_post_order_bst(BST* self);

/**
 * @brief Frees all memory allocated for a binary search tree.
 */
void destroy_bst(BST* self);


