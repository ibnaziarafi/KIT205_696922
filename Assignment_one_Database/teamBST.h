#ifndef TEAMBST_H
#define TEAMBST_H

typedef struct teamBSTNode {
    char* teamName;
    struct teamBSTNode* left;
    struct teamBSTNode* right;
} TeamBSTNode, * TeamBSTNodePtr;


TeamBSTNodePtr create_team_bst_node(const char* teamName);
TeamBSTNodePtr insert_team_bst(TeamBSTNodePtr root, TeamBSTNodePtr newNode);
void print_team_bst(const TeamBSTNodePtr root);
void test_team_bst_module();

#endif
