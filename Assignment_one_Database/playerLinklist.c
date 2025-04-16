#define _CRT_SECURE_NO_WARNINGS
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

void test_player_module() {
    printf("Running test_player_module()...\n");

    PlayerList testList = { NULL };

    // Test printing empty list
    printf("Test: Print empty player list:\n");
    print_players(&testList);

    // Add players
    PlayerNodePtr p1 = create_player("Messi", "Forward", 36, 50.0);
    PlayerNodePtr p2 = create_player("Neuer", "Goalkeeper", 38, 20.0);

    add_player(&testList, p1);
    add_player(&testList, p2);

    // Test printing filled list
    printf("\nTest: Print player list with entries:\n");
    print_players(&testList);
}
