#ifndef PLAYER_H
#define PLAYER_H

typedef struct playerNode {
    char* name;
    char* position;
    int age;
    float contractValue;
    struct playerNode* next;
} PlayerNode, * PlayerNodePtr;

typedef struct playerList {
    PlayerNodePtr head;
} PlayerList;

// Function declarations
PlayerNodePtr create_player(const char* name, const char* position, int age, float contractValue);
void add_player(PlayerList* list, PlayerNodePtr player);
void print_players(const PlayerList* list);

#endif
