
#ifndef TEAM_H
#define TEAM_H

#include "playerLinklist.h"

typedef struct teamNode {
    char* teamName;
    PlayerList players;
    struct teamNode* next;
} TeamNode, * TeamNodePtr;

typedef struct teamList {
    TeamNodePtr head;
} TeamList;

// Function declarations
TeamNodePtr create_team(const char* name);
void add_team(TeamList* list, TeamNodePtr team);
void print_teams(const TeamList* list);
void test_team_module();

#endif
