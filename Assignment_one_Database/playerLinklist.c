#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerLinklist.h"

static char* strdup_safe(const char* src) {
    char* dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

PlayerNodePtr create_player(const char* name, const char* position, int age, float contractValue) {
    PlayerNodePtr newPlayer = malloc(sizeof(PlayerNode));
    newPlayer->name = strdup_safe(name);
    newPlayer->position = strdup_safe(position);
    newPlayer->age = age;
    newPlayer->contractValue = contractValue;
    newPlayer->next = NULL;
    return newPlayer;
}

void add_player(PlayerList* list, PlayerNodePtr player) {
    player->next = list->head;
    list->head = player;
}

void print_players(const PlayerList* list) {
    PlayerNodePtr curr = list->head;
    while (curr) {
        printf("  - %s (%s), Age: %d, Value: $%.2fM\n",
            curr->name, curr->position, curr->age, curr->contractValue);
        curr = curr->next;
    }
}
