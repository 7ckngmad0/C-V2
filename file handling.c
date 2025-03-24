#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 256

void addNote();
void viewNotes();
void deleteNote();

void addNote() {
    FILE *file = fopen("ekup.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char note[LENGTH];
    printf("Enter your note: ");
    getchar();
    fgets(note, LENGTH, stdin);
    note[strcspn(note, "\n")] = 0; // pang tanggal lang to ng newline character

    fprintf(file, "%s\n", note); // pag mag lalagay ka ng shits sa file
    fclose(file);
    printf("Note added successfully!\n");
}

void viewNotes() {
    FILE *file = fopen("ekup.txt", "r"); // if babasahin lang yung file
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char note[LENGTH];
    printf("\nYour Notes:\n");
    while (fgets(note, LENGTH, file) != NULL) {
        printf("%s", note); // printing ng note
    }

    fclose(file);
}

void deleteNote() {
    FILE *file = fopen("ekup.txt", "w"); // clearing ng file
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fclose(file);
    printf("All notes deleted successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nNote-Taking Application:\n");
        printf("1. Add Note\n");
        printf("2. View Notes\n");
        printf("3. Delete All Notes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                viewNotes();
                break;
            case 3:
                deleteNote();
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