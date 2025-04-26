#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teamBST.h"
#include "playerBST.h"

static char* strdup_safe(const char* src) {
    char* dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

TeamBSTNodePtr create_team_bst_node(const char* teamName) {
    TeamBSTNodePtr newNode = malloc(sizeof(TeamBSTNode));
    newNode->teamName = strdup_safe(teamName);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TeamBSTNodePtr insert_team_bst(TeamBSTNodePtr root, TeamBSTNodePtr newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (strcmp(newNode->teamName, root->teamName) < 0) {
        root->left = insert_team_bst(root->left, newNode);
    }
    else {
        root->right = insert_team_bst(root->right, newNode);
    }
    return root;
}

void print_team_bst(const TeamBSTNodePtr root) {
    if (root == NULL) {
        return;
    }
    print_team_bst(root->left);
    printf("Team: %s\n", root->teamName);
    print_team_bst(root->right);
}


void test_team_bst_module() {
    printf("\nRunning test_team_bst_module()...\n");

    TeamBSTNodePtr root = NULL;

    printf("Test: Print empty team BST:\n");
    print_team_bst(root);

    
    TeamBSTNodePtr liverpool = create_team_bst_node("Liverpool");
    TeamBSTNodePtr arsenal = create_team_bst_node("Arsenal");
    TeamBSTNodePtr barcelona = create_team_bst_node("Barcelona");

    root = insert_team_bst(root, liverpool);
    root = insert_team_bst(root, arsenal);
    root = insert_team_bst(root, barcelona);

    printf("\nTest: Print team BST with entries:\n");
    print_team_bst(root);
}
