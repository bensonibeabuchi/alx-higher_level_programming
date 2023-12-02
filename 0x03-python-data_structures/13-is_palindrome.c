#include <stdio.h>
#include <stdlib.h>

/* Definition for singly-linked list node */
typedef struct listint_t {
    int data;
    struct listint_t* next;
} listint_t;

/* Function to check if a linked list is a palindrome */
int is_palindrome(listint_t **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return 1;  // An empty list or a single-node list is a palindrome
    }

    listint_t *slow = *head, *fast = *head;
    
    // Move 'fast' to the end and 'slow' to the middle of the list
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Reverse the second half of the list
    listint_t *prev = NULL, *curr = slow, *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Compare the first and reversed second halves
    listint_t *first = *head, *second = prev;
    while (second != NULL) {
        if (first->data != second->data) {
            return 0;  // Not a palindrome
        }
        first = first->next;
        second = second->next;
    }

    return 1;  // Palindrome
}

/* Function to create a new node with given data */
listint_t *createNode(int data) {
    listint_t *newNode = (listint_t *)malloc(sizeof(listint_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/* Function to print the linked list */
void printList(listint_t *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/* Function to free the memory allocated for the linked list */
void freeList(listint_t *head) {
    listint_t *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* Example usage */
int main() {
    listint_t *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(1);

    printf("Original list: ");
    printList(head);

    if (is_palindrome(&head)) {
        printf("The list is a palindrome.\n");
    } else {
        printf("The list is not a palindrome.\n");
    }

    // Free the allocated memory
    freeList(head);

    return 0;
}

