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



