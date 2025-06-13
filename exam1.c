#include <stdio.h>
#include <conio.h>
#include <string.h>

#define COMP_PARTS 5

struct inv_part
{
    int ID;
    char name[50];
    int part_number;
    int quantity;
    int ppU;
};

void addParts (struct inv_part parts[], int *count, FILE *inventory);
void dispParts (struct inv_part parts[], int count);
void updateParts (struct inv_part parts[], int id, int count, FILE *inventory);
void sortParts (struct inv_part parts[], int count);
void saveToFile(struct inv_part parts[], int count, FILE *inventory);

int main()
{
    FILE* inventory;
    struct inv_part parts[COMP_PARTS];
    int choice, count = 0, id;

    inventory = fopen("inventory.txt", "a");
    if (inventory == NULL) {
        printf("Error: Could not open inventory file.\n");
        return 1;
    }

    printf("Welcome to the Inventory System for Computer Parts.\n");

    do {
        printf("Please choose in the option:\n1. Add computer part\n2. Display all the computer parts\n3. Update a part\n4. Exit...\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addParts(parts, &count, inventory);
                break;
            case 2:
                dispParts(parts, count);
                break;
            case 3:
                updateParts(parts, id, count, inventory);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Exiting...\n");
                break;
        }
    } while (choice != 4);

    fclose(inventory);
    return 0;
}

void saveToFile(struct inv_part parts[], int count, FILE *inventory) 
{
    fseek(inventory, 0, SEEK_SET);
    for(int i = 0; i < count; i++) 
    {
        fprintf(inventory, "%d,%s,%d,%d,%d\n", 
            parts[i].ID, parts[i].name, parts[i].part_number, 
            parts[i].quantity, parts[i].ppU);
    }
    fflush(inventory);
}

void addParts (struct inv_part parts[], int *count, FILE *inventory)
{
    if(*count >= COMP_PARTS)
    {
        printf("Sorry you've reached the maximum parts.\n");
        return;
    }

    while(getchar() != '\n');

    while (*count < COMP_PARTS)
    {
    printf("Enter the details for Part %d\n", *count + 1);

    printf("Enter item ID: ");
    scanf("%d", &parts[*count].ID);
    while (getchar() != '\n');

    printf("Enter name: ");
    fgets(parts[*count].name, 50, stdin);
    parts[*count].name[strcspn(parts[*count].name, "\n")] = '\0';

    printf("Enter part number: ");
    scanf("%d", &parts[*count].part_number);
    while (getchar() != '\n');

    printf("Enter quantity: ");
    scanf("%d", &parts[*count].quantity);
    while (getchar() != '\n');

    printf("Enter price per unit: ");
    scanf("%d", &parts[*count].ppU);
    while (getchar() != '\n');

    (*count)++;
    saveToFile(parts, *count, inventory);
    printf("Part added successfully!\n\n");
    }
    printf("The inventory is full.\n");
}

void dispParts (struct inv_part parts[], int count)
{
    if(count == 0)
    {
        printf("There are no parts to display.");
        return;
    }

    printf("%-5s %-15s %-12s %-10s %-8s\n", "ID", "Part Name", "Part Number", "Quantity", "Price");

    for(int i = 0; i < count; i++) 
    {
        printf("%-5d %-15s %-12d %-10d %-8d\n", 
        parts[i].ID, parts[i].name, parts[i].part_number, parts[i].quantity, parts[i].ppU);
    }

    printf("Press '1' if you want to sort the parts by their price per unit: ");
    char ch = getch();
    if(ch == '1')
    {
        sortParts(parts, count);
        printf("\nParts sorted by their price per unit (ppu):\n");
        printf("%-5s %-15s %-12s %-10s %-8s\n", "ID", "Part Name", "Part Number", "Quantity", "Price");
        for(int i = 0; i < count; i++) 
        {
            printf("%-5d %-15s %-12d %-10d %-8d\n", 
            parts[i].ID, parts[i].name, parts[i].part_number, parts[i].quantity, parts[i].ppU);
        }
    }
}   

void updateParts (struct inv_part parts[], int id, int count, FILE *inventory)
{
    printf("Enter the ID of the part: ");
    scanf("%d", &id);
    while(getchar() != '\n');

    for (int i = 0; i < count; i++)
    {
        if (parts[i].ID == id)
        {
            printf("Updating part of the ID %d\n", id);

            printf("Enter new name: ");
            fgets(parts[i].name, 50, stdin);
            parts[i].name[strcspn(parts[i].name, "\n")] = '\0';

            printf("Enter new part number: ");
            scanf("%d", &parts[i].part_number);
            while (getchar() != '\n');

            printf("Enter new quantity: ");
            scanf("%d", &parts[i].quantity);
            while (getchar() != '\n');

            printf("Enter new price per unit: ");
            scanf("%d", &parts[i].ppU);
            while (getchar() != '\n');

            saveToFile(parts, count, inventory);
            printf("Part updated successfully!\n");
            return;
        }
    }
    printf("Part with ID %d not found.\n", id);
}

void sortParts (struct inv_part parts[], int count)
{
    struct inv_part temp;
    for(int i = 0; i < count - 1; i++)
    {
        for (int j = 0; i < count - i - 1; i++)
        {
            if(parts[j].ppU > parts[j+1].ppU)
            {
                temp = parts[j];
                parts[j] = parts[j+1];
                parts[j+1] = temp;
            }
        }
    }
}