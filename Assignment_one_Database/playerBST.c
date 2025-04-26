#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerBST.h"

static char* strdup_safe(const char* src) {
    char* dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

PlayerBSTNodePtr create_player_bst_node(const char* name, const char* position, int age, float contractValue) {
    PlayerBSTNodePtr newNode = malloc(sizeof(PlayerBSTNode));
    newNode->name = strdup_safe(name);
    newNode->position = strdup_safe(position);
    newNode->age = age;
    newNode->contractValue = contractValue;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

PlayerBSTNodePtr insert_player_bst(PlayerBSTNodePtr root, PlayerBSTNodePtr newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (strcmp(newNode->name, root->name) < 0) {
        root->left = insert_player_bst(root->left, newNode);
    }
    else {
        root->right = insert_player_bst(root->right, newNode);
    }
    return root;
}

void print_player_bst(const PlayerBSTNodePtr root) {
    if (root == NULL) {
        return;
    }
    print_player_bst(root->left);
    printf("Player: %s (%s), Age: %d, Value: $%.2fM\n",
        root->name, root->position, root->age, root->contractValue);
    print_player_bst(root->right);
}


void test_player_bst_module() {
    printf("\nRunning test_player_bst_module()...\n");

    PlayerBSTNodePtr root = NULL;

    printf("Test: Print empty player BST:\n");
    print_player_bst(root);

    
    PlayerBSTNodePtr messi = create_player_bst_node("Messi", "Forward", 36, 50.0);
    PlayerBSTNodePtr neuer = create_player_bst_node("Neuer", "Goalkeeper", 38, 20.0);
    PlayerBSTNodePtr salah = create_player_bst_node("Salah", "Forward", 31, 90.0);

    root = insert_player_bst(root, messi);
    root = insert_player_bst(root, neuer);
    root = insert_player_bst(root, salah);

    printf("\nTest: Print player BST with entries:\n");
    print_player_bst(root);
}
