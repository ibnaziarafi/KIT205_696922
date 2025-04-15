#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

// Function prototype for quicksort
void quicksort(String* a, int first, int last);

// Swap helper function
void swap(String* a, String* b) {
    String temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    String* strings;
    char buffer[100];  // Enough to store 99 character strings
    int n;

    // Prompt for number of strings
    printf("Enter number of strings: ");
    scanf("%d", &n);

    // Allocate memory for array of strings
    strings = malloc(n * sizeof(String));
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    // Read each string into the buffer, then allocate and copy into array
    for (int i = 0; i < n; i++) {
        scanf("%s", buffer);

        strings[i] = malloc(strlen(buffer) + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            return 1;
        }

        strcpy(strings[i], buffer);
    }

    // Sort the strings using quicksort
    quicksort(strings, 0, n - 1);

    // Print sorted strings
    printf("\nSorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}

void quicksort(String* a, int first, int last) {
    if (first < last) {
        int i = first, j = last - 1;
        String pivot = a[last];

        while (i <= j) {
            while (i < last && strcmp(a[i], pivot) <= 0) {
                i++;
            }
            while (j >= first && strcmp(a[j], pivot) > 0) {
                j--;
            }
            if (i < j) {
                swap(&a[i], &a[j]);
            }
        }

        swap(&a[i], &a[last]);

        quicksort(a, first, j);
        quicksort(a, i + 1, last);
    }
}
