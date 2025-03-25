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

// Reverses a list efficiently by building the new list node by node
List reverse(List* self) {
    List result = new_list();
    ListNodePtr current = self->head;

    while (current != NULL) {
        insert_at_front(&result, current->data);
        current = current->next;
    }

    return result;
}

// Merges two ordered lists efficiently by walking through both lists
List merge(List* list1, List* list2) {
    List result = new_list();
    ListNodePtr p1 = list1->head;
    ListNodePtr p2 = list2->head;
    ListNodePtr tail = NULL;

    while (p1 != NULL || p2 != NULL) {
        ListNodePtr next_node = NULL;

        if (p1 == NULL) {
            next_node = p2;
            p2 = p2->next;
        }
        else if (p2 == NULL) {
            next_node = p1;
            p1 = p1->next;
        }
        else if (p1->data <= p2->data) {
            next_node = p1;
            p1 = p1->next;
        }
        else {
            next_node = p2;
            p2 = p2->next;
        }

        if (result.head == NULL) {
            result.head = next_node;
            tail = next_node;
        }
        else {
            tail->next = next_node;
            tail = tail->next;
        }
    }

    // Clear the input lists to prevent accidental double-free
    list1->head = NULL;
    list2->head = NULL;

    return result;
}

// Helper function for testing sublists
static void list_adhoc_test_sublist(List* sublist) {
    int sub_quit = 0;
    while (!sub_quit) {
        printf("\n=== Second List Operations ===\n");
        printf("0 - Return to main menu\n");
        printf("1 - Insert at front\n");
        printf("2 - Print list\n");
        printf("Enter option: ");

        int option;
        scanf_s("%d", &option);

        switch (option) {
        case 0: sub_quit = 1; break;
        case 1: option_insert(sublist); break;
        case 2: option_print(sublist); break;
        default: printf("Invalid option\n");
        }
    }
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

    // Test reverse function
    printf("\nTesting reverse...\n");
    List to_reverse = new_list();
    insert_in_order(&to_reverse, 1);
    insert_in_order(&to_reverse, 3);
    insert_in_order(&to_reverse, 5);

    printf("Original list: ");
    print_list(&to_reverse);

    List reversed = reverse(&to_reverse);
    printf("Reversed list: ");
    print_list(&reversed);
    printf("Expected: 5, 3, 1\n");

    destroy_list(&to_reverse);
    destroy_list(&reversed);

    // Test merge function
    printf("\nTesting merge...\n");
    List list1 = new_list();
    List list2 = new_list();

    insert_in_order(&list1, 1);
    insert_in_order(&list1, 3);
    insert_in_order(&list1, 5);

    insert_in_order(&list2, 2);
    insert_in_order(&list2, 4);
    insert_in_order(&list2, 6);

    printf("List 1: ");
    print_list(&list1);
    printf("List 2: ");
    print_list(&list2);

    List merged = merge(&list1, &list2);
    printf("Merged list: ");
    print_list(&merged);
    printf("Expected: 1, 2, 3, 4, 5, 6\n");

    destroy_list(&merged);

    printf("=== All Tests Completed ===\n");
}


// adhoc test function 
void list_adhoc_test() {
    List my_list = new_list();
    List second_list = new_list(); // For merge testing
    int quit = 0;

    printf("\n=== Linked List Interactive Test ===\n");
    printf("0 - Quit\n");
    printf("1 - Insert at front\n");
    printf("2 - Delete value\n");
    printf("3 - Print list\n");
    printf("4 - Reverse list\n");
    printf("5 - Create second list for merge\n");
    printf("6 - Merge lists\n\n");

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
        case 4: {
            List reversed = reverse(&my_list);
            printf("Reversed list: ");
            print_list(&reversed);
            destroy_list(&my_list);
            my_list = reversed;
            break;
        }
        case 5: {
            printf("Creating second list (will clear current second list)\n");
            destroy_list(&second_list);
            second_list = new_list();
            list_adhoc_test_sublist(&second_list);
            break;
        }
        case 6: {
            List merged = merge(&my_list, &second_list);
            printf("Merged list: ");
            print_list(&merged);
            destroy_list(&my_list);
            my_list = merged;
            second_list = new_list(); // Reset second list
            break;
        }
        default:
            printf("Invalid option. Try again.\n");
        }
    }

    destroy_list(&my_list);
    destroy_list(&second_list);
    printf("List destroyed. Exiting test.\n");
}

