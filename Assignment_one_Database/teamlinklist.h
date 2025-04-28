
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
TeamList load_teams_linklist(const char* filename);
void assign_players_to_teams_linklist(TeamList* teams, const char* playersFile);
void print_teams(const TeamList* list);
void test_team_module();
void test_team_module_from_external();

#endif
