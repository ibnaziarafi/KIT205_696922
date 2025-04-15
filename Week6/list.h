#pragma once

#include <stdbool.h>

typedef char* String;

typedef struct listNode {
    String data;
    struct listNode* next;
} *ListNodePtr;

typedef struct list {
    ListNodePtr head;
} List;

List new_list();
void print_list(List* self);
void insert_at_front(List* self, String data);
void insert_in_order(List* self, String data);
void delete_from_list(List* self, String data);
void destroy_list(List* self);
List reverse(List* self);
List merge(List* list1, List* list2);
void list_test();
