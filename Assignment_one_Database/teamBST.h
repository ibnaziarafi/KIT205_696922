#ifndef TEAMBST_H
#define TEAMBST_H
#include "playerBST.h" 

typedef struct teamBSTNode {
    char* teamName;
    PlayerBSTNodePtr players; 
    struct teamBSTNode* left;
    struct teamBSTNode* right;
} TeamBSTNode, * TeamBSTNodePtr;

TeamBSTNodePtr create_team_bst_node(const char* teamName);
TeamBSTNodePtr insert_team_bst(TeamBSTNodePtr root, TeamBSTNodePtr newNode);
TeamBSTNodePtr load_teams(const char* filename);
void print_team_bst(const TeamBSTNodePtr root);
void test_team_bst_module();
void test_team_bst_module_from_external();

#endif
