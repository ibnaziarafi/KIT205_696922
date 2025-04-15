#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

void print_list(List* self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        printf("%s", current->data);
        current = current->next;
        if (current != NULL) printf(", ");
    }
    printf("\n");
}

void insert_at_front(List* self, String data) {
    ListNodePtr new_node = malloc(sizeof * new_node);
    new_node->data = malloc(strlen(data) + 1);
    strcpy(new_node->data, data);
    new_node->next = self->head;
    self->head = new_node;
}

void insert_in_order(List* self, String data) {
    ListNodePtr new_node = malloc(sizeof * new_node);
    new_node->data = malloc(strlen(data) + 1);
    strcpy(new_node->data, data);
    new_node->next = NULL;

    if (self->head == NULL || strcmp(data, self->head->data) < 0) {
        new_node->next = self->head;
        self->head = new_node;
        return;
    }

    ListNodePtr current = self->head;
    while (current->next != NULL && strcmp(current->next->data, data) < 0) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

void delete_from_list(List* self, String data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) {
                self->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current->data);
            free(current);
            return;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

void destroy_list(List* self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free->data);
        free(to_free);
    }
    self->head = NULL;
}

List reverse(List* self) {
    List reversed = new_list();
    ListNodePtr current = self->head;

    while (current != NULL) {
        insert_at_front(&reversed, current->data);
        current = current->next;
    }
    return reversed;
}

List merge(List* list1, List* list2) {
    List merged = new_list();
    ListNodePtr curr1 = list1->head;
    ListNodePtr curr2 = list2->head;

    while (curr1 != NULL && curr2 != NULL) {
        if (strcmp(curr1->data, curr2->data) < 0) {
            insert_in_order(&merged, curr1->data);
            curr1 = curr1->next;
        }
        else {
            insert_in_order(&merged, curr2->data);
            curr2 = curr2->next;
        }
    }

    while (curr1 != NULL) {
        insert_in_order(&merged, curr1->data);
        curr1 = curr1->next;
    }

    while (curr2 != NULL) {
        insert_in_order(&merged, curr2->data);
        curr2 = curr2->next;
    }

    return merged;
}
void list_test() {
    printf("=== Starting Linked List Tests ===\n\n");

   
    printf("Testing insert_at_front...\n");
    List front_list = new_list();
    insert_at_front(&front_list, "five");
    insert_at_front(&front_list, "three");
    insert_at_front(&front_list, "seven");
    insert_at_front(&front_list, "two");
    insert_at_front(&front_list, "zero");

    printf("Expected: zero, two, seven, three, five\n");
    printf("  Result: ");
    print_list(&front_list);
    printf("\n");

    
    printf("Testing insert_in_order...\n");
    List order_list = new_list();
    insert_in_order(&order_list, "five");
    insert_in_order(&order_list, "three");
    insert_in_order(&order_list, "seven");
    insert_in_order(&order_list, "two");
    insert_in_order(&order_list, "zero");

    printf("Expected: five, seven, three, two, zero (alphabetical)\n");
    printf("  Result: ");
    print_list(&order_list);
    printf("\n");

 
    printf("Testing delete_list...\n");
    printf("Deleting 'three'...\n");
    delete_from_list(&order_list, "three");
    printf("Expected: five, seven, two, zero\n");
    printf("  Result: ");
    print_list(&order_list);

    printf("Deleting 'five' (first element)...\n");
    delete_from_list(&order_list, "five");
    printf("Expected: seven, two, zero\n");
    print_list(&order_list);

    printf("Deleting 'zero' (last element)...\n");
    delete_from_list(&order_list, "zero");
    printf("Expected: seven, two\n");
    print_list(&order_list);
    printf("\n");


    printf("Deleting non-existent item 'ten'...\n");
    delete_from_list(&order_list, "ten");
    printf("Expected: seven, two\n");
    print_list(&order_list);

    printf("Inserting into empty list...\n");
    List empty_list = new_list();
    insert_in_order(&empty_list, "apple");
    printf("Expected: apple\n");
    print_list(&empty_list);
    printf("\n");

    destroy_list(&front_list);
    destroy_list(&order_list);
    destroy_list(&empty_list);

    printf("Testing reverse...\n");
    List to_reverse = new_list();
    insert_in_order(&to_reverse, "a");
    insert_in_order(&to_reverse, "c");
    insert_in_order(&to_reverse, "e");

    printf("Original: ");
    print_list(&to_reverse);

    List reversed = reverse(&to_reverse);
    printf("Reversed: ");
    print_list(&reversed);
    printf("Expected: e, c, a\n");

    destroy_list(&to_reverse);
    destroy_list(&reversed);


    printf("Testing merge...\n");
    List list1 = new_list();
    List list2 = new_list();

    insert_in_order(&list1, "a");
    insert_in_order(&list1, "c");
    insert_in_order(&list1, "e");

    insert_in_order(&list2, "b");
    insert_in_order(&list2, "d");
    insert_in_order(&list2, "f");

    List merged = merge(&list1, &list2);
    printf("Merged: ");
    print_list(&merged);
    printf("Expected: a, b, c, d, e, f\n");

    destroy_list(&merged);
    destroy_list(&list1);
    destroy_list(&list2);

    printf("=== All Tests Completed ===\n");
}