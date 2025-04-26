#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teamBST.h"

static char* strdup_safe(const char* src) {
    char* dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

TeamBSTNodePtr create_team_bst_node(const char* teamName) {
    TeamBSTNodePtr newNode = malloc(sizeof(TeamBSTNode));
    newNode->teamName = strdup_safe(teamName);
    newNode->players = NULL;
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
    if (root->players == NULL) {
        printf("  No players.\n");
    }
    else {
        printf("  Players:\n");
        print_player_bst(root->players);
    }
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

    
    liverpool->players = insert_player_bst(liverpool->players, create_player_bst_node("Salah", "Forward", 31, 90.0));
    liverpool->players = insert_player_bst(liverpool->players, create_player_bst_node("Van Dijk", "Defender", 32, 75.0));

    arsenal->players = insert_player_bst(arsenal->players, create_player_bst_node("Saka", "Winger", 22, 100.0));
    arsenal->players = insert_player_bst(arsenal->players, create_player_bst_node("Odegaard", "Midfielder", 26, 80.0));

    barcelona->players = insert_player_bst(barcelona->players, create_player_bst_node("Lewandowski", "Striker", 36, 40.0));
    barcelona->players = insert_player_bst(barcelona->players, create_player_bst_node("Pedri", "Midfielder", 21, 85.0));

    printf("\nTest: Print team BST with teams and players:\n");
    print_team_bst(root);
}
