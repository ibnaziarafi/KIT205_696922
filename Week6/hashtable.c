#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

HashTable create_hashtable(int n) {
    HashTable newtable;
    newtable.size = n;
    newtable.table = malloc(n * sizeof(List));
    for (int i = 0; i < n; i++) {
        newtable.table[i] = new_list();
    }
    return newtable;
}

int hash(String key, int size) {
    unsigned long h = 0;
    int n = strlen(key);
    for (int i = 0; i < n; i++) {
        h = (h << 5) + (int)(key[i]);
    }
    return h % size;
}

void hash_insert(HashTable* self, String key) {
    int index = hash(key, self->size);
    insert_in_order(&self->table[index], key);
}

void hash_remove(HashTable* self, String key) {
    int index = hash(key, self->size);
    delete_from_list(&self->table[index], key);
}

void hash_print(HashTable* self) {
    for (int i = 0; i < self->size; i++) {
        printf("%d: ", i);
        print_list(&self->table[i]);
    }
}

void hash_destroy(HashTable* self) {
    for (int i = 0; i < self->size; i++) {
        destroy_list(&self->table[i]);
    }
    free(self->table);
    self->table = NULL;
    self->size = 0;
}

void hash_adhoc_test() {
    int command = 1;
    HashTable table = create_hashtable(11);
    char buffer[100];

    while (command) {
        printf("1: insert, 2: remove, 3: print, 0: exit\n> ");
        scanf("%d", &command);
        switch (command) {
        case 1:
            scanf("%s", buffer);
            hash_insert(&table, buffer);
            break;
        case 2:
            scanf("%s", buffer);
            hash_remove(&table, buffer);
            break;
        case 3:
            hash_print(&table);
            break;
        }
        printf("\n");
    }

    hash_destroy(&table);
}
