#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** head_ref, int new_data);
void deleteNode(struct Node** head_ref, int key);
void displayList(struct Node* node);

void insertAtEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
    struct Node* last = *head_ref; 

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) { // yung node yung gagawing head pag empty yung list
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) { // Traverse to the last node
        last = last->next;
    }

    last->next = new_node; // Link the new node at the end
}

// function para mag delete ng node sa linked list
void deleteNode(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    // if yung head node mismo yung tatanggalin
    if (temp != NULL && temp->data == key) 
    {
        *head_ref = temp->next;
        free(temp); 
        return;
    }

    while (temp != NULL && temp->data != key) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with data %d not found.\n", key);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void displayList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }

    // visualization of the last node
    printf("NULL\n"); 
}

int main() 
{
    struct Node* head = NULL; 
    int choice, data;

    while (1) 
    {
        printf("\nLinked List Operations:\n");
        printf("1. Insert at end\n");
        printf("2. Delete a node\n");
        printf("3. Display the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                printf("Inserted %d at the end of the list.\n", data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 3:
                printf("Current Linked List: ");
                displayList(head);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}