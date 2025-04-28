#ifndef PLAYERBST_H
#define PLAYERBST_H

typedef struct playerBSTNode {
    char* name;
    char* position;
    int age;
    float contractValue;
    struct playerBSTNode* left;
    struct playerBSTNode* right;
} PlayerBSTNode, * PlayerBSTNodePtr;

PlayerBSTNodePtr create_player_bst_node(const char* name, const char* position, int age, float contractValue);
PlayerBSTNodePtr insert_player_bst(PlayerBSTNodePtr root, PlayerBSTNodePtr newNode);
PlayerBSTNodePtr load_players(const char* filename);
void print_player_bst(const PlayerBSTNodePtr root);
void test_player_bst_module();

#endif
