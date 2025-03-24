#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** head_ref, int new_data) 
{
    // allocation ng memory for new nodes
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) 
    {
        *head_ref = new_node;
        return;
    }

    struct Node* last = *head_ref;
    while (last->next) last = last->next;
    last->next = new_node;
}

void deleteNode(struct Node** head_ref, int key) //self-explanatory na
{
    struct Node *temp = *head_ref, *prev = NULL;

    if (temp && temp->data == key) // for deleting the first node or yung head
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp && temp->data != key) // for searching ng node na ide-delete
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) 
    {
        printf("Node with data %d not found.\n", key);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void displayList(struct Node* node) 
{
    while (node) 
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data;

    while (1) {
        printf("\nLinked List Operations:\n1. Insert at end\n2. Delete a node\n3. Display the list\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}