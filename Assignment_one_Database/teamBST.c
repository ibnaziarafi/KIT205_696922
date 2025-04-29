#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

TeamBSTNodePtr load_teams(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open team file '%s'.\n", filename);
        return NULL;
    }

    TeamBSTNodePtr root = NULL;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0) {
            TeamBSTNodePtr newTeam = create_team_bst_node(buffer);
            root = insert_team_bst(root, newTeam);
        }
    }

    fclose(file);
    return root;
}

void assign_players_to_teams(TeamBSTNodePtr teams) {
    if (teams == NULL) {
        return;
    }

    // Go to left subtree
    assign_players_to_teams(teams->left);

    // Assign players to this team
    teams->players = load_players("players.txt");

    // Go to right subtree
    assign_players_to_teams(teams->right);
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

//to test if each functions are working
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

void test_team_bst_module_from_external() {
    printf("\nRunning test_team_bst_module()...\n");
    clock_t start_ll, end_ll;
    double time_ll;

    start_ll = clock();

    TeamBSTNodePtr teams = load_teams("teams.txt");

    if (teams != NULL) {
        assign_players_to_teams(teams);
    }

    printf("\nTeams with players:\n");
    print_team_bst(teams);

    end_ll = clock();
    time_ll = ((double)(end_ll - start_ll)) / CLOCKS_PER_SEC;
    printf("Time taken for Linked List insertions: %.6f seconds\n", time_ll);
}

