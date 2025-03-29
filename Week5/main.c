#include <stdio.h>
#include "bst.h"

void bst_adhoc_test() {
    BST tree = new_bst();
    int quit = 0;
    int data;

    while (quit == 0) {
        printf("Enter some data (0 to stop): ");
        scanf_s("%d", &data);
        if (data != 0) {
            insert_bst(&tree, data);
        }
        else {
            quit = 1;
        }
    }

    printf("In-order traversal: ");
    print_in_order_bst(&tree);
    printf("\n");

    destroy_bst(&tree);
}


void bst_test() {
    BST tree = new_bst();

    // Insert test values
    insert_bst(&tree, 50);
    insert_bst(&tree, 30);
    insert_bst(&tree, 70);
    insert_bst(&tree, 20);
    insert_bst(&tree, 40);
    insert_bst(&tree, 60);
    insert_bst(&tree, 80);

    printf("\nBST In-Order Traversal (should be sorted): ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("\nBST Pre-Order Traversal: ");
    print_pre_order_bst(&tree);
    printf("\n");

    printf("\nBST Post-Order Traversal: ");
    print_post_order_bst(&tree);
    printf("\n");

    // Test search function
    int search_val = 40;
    if (find_bst(&tree, search_val)) {
        printf("\n%d is found in the BST.\n", search_val);
    }
    else {
        printf("\n%d is not in the BST.\n", search_val);
    }

    // Test delete operation
    printf("\nDeleting node 50 (root)...\n");
    delete_bst(&tree, 50);

    printf("\nBST In-Order Traversal after deletion: ");
    print_in_order_bst(&tree);
    printf("\n");

    // Destroy tree
    destroy_bst(&tree);
}

int main() {
    printf("Running Ad-hoc Test...\n");
    bst_adhoc_test();

    printf("\n=============================\n");
    printf("Running Structured Unit Test...\n");
    bst_test();

    return 0;
}
