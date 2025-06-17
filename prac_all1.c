#include <stdio.h>
#include <conio.h>
#include <string.h>

#define VEHICLE 5

struct vehicles
{
    int plate_num;
    char owner_name[50];
    char service_type[50];
};

struct services
{
    int date;
    float service_cost;
};

void v_input(struct vehicles v[], int *count, FILE *veService);
void s_input(struct services s[], int *count1, FILE *veService);
void printInv(struct vehicles v[], int count, struct services s[], int count1);
void filterIn(struct vehicles v[], struct services s[], int count, int count1);

int main()
{
    FILE* veService = fopen("Vehicle_Service.txt", "a");
    struct vehicles v[VEHICLE];
    struct services s[VEHICLE];
    int choice, count = 0, count1 = 0;

    if (veService == NULL)
    {
        printf("File can't be opened.\n");
        return 1;
    }

    printf("Welcome to vehicle service system!\n");
    do
    {
        printf("Choose an option\n1. Add vehicle\n2.Display vehicle\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice)
        {
            case 1:
                v_input(v, &count, veService);
                s_input(s, &count1, veService);
                break;
            case 2:
                printInv(v, count, s, count1);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Not an option.\n");
        }

    } while (choice != 3);
    fclose(veService);
    return 0; 
}

void v_input(struct vehicles v[], int *count, FILE *veService)
{
    if (*count >= VEHICLE)
    {
        printf("You've reached the maximum input.\n");
        return;
    }

    printf("Enter the plate number: ");
    scanf("%d", &v[*count].plate_num);
    while(getchar() != '\n');
    
    printf("Enter owner name: ");
    fgets(v[*count].owner_name, sizeof(v[*count].owner_name), stdin);
    v[*count].owner_name[strcspn(v[*count].owner_name, "\n")] = '\0';
    
    printf("Enter service type: ");
    fgets(v[*count].service_type, sizeof(v[*count].service_type), stdin);
    v[*count].service_type[strcspn(v[*count].service_type, "\n")] = '\0';

    fprintf(veService, "%d %s %s\n", v[*count].plate_num, v[*count].owner_name, v[*count].service_type);
    
    (*count)++;
    printf("vehicle entered successfully!\n");
}

void s_input(struct services s[], int *count1, FILE *veService)
{
    if (*count1 >= VEHICLE)
    {
        printf("You've reached the maximum input.\n");
        return;
    }

    printf("Enter the date: ");
    scanf("%d", &s[*count1].date);
    while(getchar() != '\n');
    
    printf("Enter service cost: ");
    scanf("%f", &s[*count1].service_cost);
    while(getchar() != '\n');

    fprintf(veService, "%d %.2f\n", s[*count1].date, s[*count1].service_cost);

    (*count1)++;
    printf("service entered successfully!\n");
}

void printInv(struct vehicles v[], int count, struct services s[], int count1)
{
    if (count == 0 || count1 == 0)
    {
        printf("There's no data to display.\n");
        return;
    }

    printf("%-12s %-15s %-15s %-8s %-12s\n", "PLATE NUMBER", "OWNER NAME", "SERVICE TYPE", "DATE", "SERVICE COST");
    for (int i = 0; i < count && i < count1; i++)
    {
        printf("%-12d %-15s %-15s %-8d %-12.2f\n",
            v[i].plate_num, v[i].owner_name, v[i].service_type,
            s[i].date, s[i].service_cost);
    }
    printf("\n");

    printf("press 1 to display the vehicles that have service cost that is greater than 500\n");
    char ch = getch();
    if (ch == '1')
    {
        filterIn(v, s, count, count1);
    }
}

void filterIn(struct vehicles v[], struct services s[], int count, int count1)
{
    int target = 500;
    for (int i = 0; i < count && i < count1; i++)
    {
        if (s[i].service_cost > target)
        {
            printf("%-12d %-15s %-15s %-8d %-12.2f\n",
            v[i].plate_num, v[i].owner_name, v[i].service_type,
            s[i].date, s[i].service_cost);
        }
    }
}
