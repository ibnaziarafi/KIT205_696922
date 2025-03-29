#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// Create an empty BST
BST new_bst() {
    BST temp;
    temp.root = NULL;
    return temp;
}

// Recursive function to find a value
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
    if (self == NULL || self->data_item == n) {
        return self;
    }
    return (n < self->data_item) ? find_bst_node(self->left, n) : find_bst_node(self->right, n);
}

// Find a value in the tree
BSTNodePtr find_bst(BST* self, int n) {
    return find_bst_node(self->root, n);
}

// Recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
    if (self == NULL) {
        self = malloc(sizeof(*self));
        self->data_item = n;
        self->left = self->right = NULL;
    }
    else if (n < self->data_item) {
        self->left = insert_bst_node(self->left, n);
    }
    else if (n > self->data_item) {
        self->right = insert_bst_node(self->right, n);
    }
    return self;
}

// Insert a value into the tree
void insert_bst(BST* self, int n) {
    self->root = insert_bst_node(self->root, n);
}

// Helper function to find the minimum node
BSTNodePtr min_node(BSTNodePtr self) {
    while (self && self->left != NULL) {
        self = self->left;
    }
    return self;
}

// Recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
    if (self == NULL) return self;

    if (n < self->data_item) {
        self->left = delete_bst_node(self->left, n);
    }
    else if (n > self->data_item) {
        self->right = delete_bst_node(self->right, n);
    }
    else {
        if (self->left == NULL) {
            BSTNodePtr temp = self->right;
            free(self);
            return temp;
        }
        else if (self->right == NULL) {
            BSTNodePtr temp = self->left;
            free(self);
            return temp;
        }

        BSTNodePtr temp = min_node(self->right);
        self->data_item = temp->data_item;
        self->right = delete_bst_node(self->right, temp->data_item);
    }
    return self;
}

// Delete a value from the tree
void delete_bst(BST* self, int n) {
    self->root = delete_bst_node(self->root, n);
}

// Recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        print_in_order_bst_node(self->left);
        printf("%d ", self->data_item);
        print_in_order_bst_node(self->right);
    }
}

// Print in-order traversal
void print_in_order_bst(BST* self) {
    print_in_order_bst_node(self->root);
    printf("\n");
}

// Recursive function to print pre-order
void print_pre_order_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        printf("%d ", self->data_item);
        print_pre_order_bst_node(self->left);
        print_pre_order_bst_node(self->right);
    }
}

// Print pre-order traversal
void print_pre_order_bst(BST* self) {
    print_pre_order_bst_node(self->root);
    printf("\n");
}

// Recursive function to print post-order
void print_post_order_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        print_post_order_bst_node(self->left);
        print_post_order_bst_node(self->right);
        printf("%d ", self->data_item);
    }
}

// Print post-order traversal
void print_post_order_bst(BST* self) {
    print_post_order_bst_node(self->root);
    printf("\n");
}

// Recursive function to destroy the tree
void destroy_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        destroy_bst_node(self->left);
        destroy_bst_node(self->right);
        free(self);
    }
}

// Destroy the BST
void destroy_bst(BST* self) {
    destroy_bst_node(self->root);
    self->root = NULL;
}

