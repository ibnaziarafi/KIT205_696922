#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teamlinklist.h"

static char* strdup_safe(const char* src) {
    char* dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

TeamNodePtr create_team(const char* name) {
    TeamNodePtr newTeam = malloc(sizeof(TeamNode));
    newTeam->teamName = strdup_safe(name);
    newTeam->players.head = NULL;
    newTeam->next = NULL;
    return newTeam;
}

void add_team(TeamList* list, TeamNodePtr team) {
    team->next = list->head;
    list->head = team;
}

void print_teams(const TeamList* list) {
    if (list->head == NULL) {
        printf("No teams available.\n");
        return;
    }

    TeamNodePtr curr = list->head;
    while (curr) {
        printf("Team: %s\n", curr->teamName);
        print_players(&curr->players);
        printf("\n");
        curr = curr->next;
    }
}


void test_team_module() {
    printf("\nRunning test_team_module()...\n");

    TeamList testLeague = { NULL };

    
    printf("Test: Print empty team list:\n");
    print_teams(&testLeague);

    // Create team and add players
    TeamNodePtr liverpool = create_team("Liverpool");
    add_player(&liverpool->players, create_player("Salah", "Forward", 31, 90.0));
    add_player(&liverpool->players, create_player("Alisson", "Goalkeeper", 32, 40.0));
    add_team(&testLeague, liverpool);

    // Another team
    TeamNodePtr arsenal = create_team("Arsenal");
    add_team(&testLeague, arsenal);

    
    printf("\nTest: Print teams and players:\n");
    print_teams(&testLeague);
}

