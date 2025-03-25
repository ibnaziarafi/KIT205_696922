#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%d", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

void list_test() {
    printf("=== Starting Linked List Tests ===\n\n");

    // Test insert_at_front
    printf("Testing insert_at_front...\n");
    List front_list = new_list();
    insert_at_front(&front_list, 5);
    insert_at_front(&front_list, 3);
    insert_at_front(&front_list, 7);
    insert_at_front(&front_list, 2);
    insert_at_front(&front_list, 0);

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("  Result: ");
    print_list(&front_list);
    printf("\n");

    // Test insert_in_order
    printf("Testing insert_in_order...\n");
    List order_list = new_list();
    insert_in_order(&order_list, 5);
    insert_in_order(&order_list, 3);
    insert_in_order(&order_list, 7);
    insert_in_order(&order_list, 2);
    insert_in_order(&order_list, 0);

    printf("Expected: 0, 2, 3, 5, 7\n");
    printf("  Result: ");
    print_list(&order_list);
    printf("\n");

    // Test delete_list
    printf("Testing delete_list...\n");
    printf("Deleting 3...\n");
    delete_list(&order_list, 3);
    printf("Expected: 0, 2, 5, 7\n");
    printf("  Result: ");
    print_list(&order_list);

    printf("Deleting 0 (first element)...\n");
    delete_list(&order_list, 0);
    printf("Expected: 2, 5, 7\n");
    printf("  Result: ");
    print_list(&order_list);

    printf("Deleting 7 (last element)...\n");
    delete_list(&order_list, 7);
    printf("Expected: 2, 5\n");
    printf("  Result: ");
    print_list(&order_list);
    printf("\n");

    // Test edge cases
    printf("Testing edge cases...\n");
    printf("Deleting non-existent item (10)...\n");
    delete_list(&order_list, 10);
    printf("Expected: 2, 5\n");
    printf("  Result: ");
    print_list(&order_list);

    printf("Inserting into empty list...\n");
    List empty_list = new_list();
    insert_in_order(&empty_list, 10);
    printf("Expected: 10\n");
    printf("  Result: ");
    print_list(&empty_list);
    printf("\n");

    // Clean up
    destroy_list(&front_list);
    destroy_list(&order_list);
    destroy_list(&empty_list);

    printf("=== All Tests Completed ===\n");
}

// inserting a value
static void option_insert(List* self) {
    int data;
    printf("Enter value to insert: ");
    scanf_s("%d", &data);
    insert_at_front(self, data);
    printf("%d inserted at front.\n", data);
}

// deleting a value
static void option_delete(List* self) {
    int data;
    printf("Enter value to delete: ");
    scanf_s("%d", &data);
    delete_list(self, data);
    printf("Deleted first occurrence of %d (if it existed).\n", data);
}

// printing the list
static void option_print(List* self) {
    printf("Current list: ");
    print_list(self);
}

// test function 
void list_adhoc_test() {
    List my_list = new_list();
    int quit = 0;

    printf("\n=== Linked List Interactive Test ===\n");
    printf("0 - Quit\n");
    printf("1 - Insert at front\n");
    printf("2 - Delete value\n");
    printf("3 - Print list\n\n");

    while (!quit) {
        int option;
        printf("Enter option: ");
        scanf_s("%d", &option);

        switch (option) {
        case 0:
            quit = 1;
            break;
        case 1:
            option_insert(&my_list);
            break;
        case 2:
            option_delete(&my_list);
            break;
        case 3:
            option_print(&my_list);
            break;
        default:
            printf("Invalid option. Try again.\n");
        }
    }

    destroy_list(&my_list);
    printf("List destroyed. Exiting test.\n");
}