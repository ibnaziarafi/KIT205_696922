#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

TeamList load_teams_linklist(const char* filename) {
    TeamList list = { NULL };
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        return list;
    }

    char teamName[100];

    while (fgets(teamName, sizeof(teamName), file)) {
        // Remove trailing newline
        teamName[strcspn(teamName, "\r\n")] = 0;
        if (strlen(teamName) > 0) {
            TeamNodePtr team = create_team(teamName);
            add_team(&list, team);
        }
    }

    fclose(file);
    return list;
}

void assign_players_to_teams_linklist(TeamList* teams, const char* playersFile) {
    PlayerList players = load_players_linklist(playersFile);

    if (teams->head == NULL) {
        printf("No teams to assign players.\n");
        return;
    }

    TeamNodePtr curr = teams->head;
    while (curr) {
        // Clone all players into each team
        PlayerNodePtr p = players.head;
        while (p) {
            PlayerNodePtr newPlayer = create_player(p->name, p->position, p->age, p->contractValue);
            add_player(&curr->players, newPlayer);
            p = p->next;
        }
        curr = curr->next;
    }
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

void test_team_module_from_external() {
    printf("\nRunning test_team_module()...\n");

    clock_t start_ll, end_ll;
    double time_ll;

    start_ll = clock();

    TeamList league = load_teams_linklist("teams.txt");

    printf("Test: Print teams BEFORE assigning players:\n");
    print_teams(&league);

    assign_players_to_teams_linklist(&league, "players.txt");

    printf("\nTest: Print teams AFTER assigning players:\n");
    print_teams(&league);

    end_ll = clock();
    time_ll = ((double)(end_ll - start_ll)) / CLOCKS_PER_SEC;
    printf("Time taken for Linked List insertions: %.6f seconds\n", time_ll);
}


