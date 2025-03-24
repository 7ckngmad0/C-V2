#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

struct Student 
{
    int id;
    char name[NAME_LENGTH]; 
    float grade;
};

// prototypes ng mga functions para tawagin sa main
void addStudent(struct Student students[], int *count);
void displayStudents(struct Student students[], int count);
int searchStudent(struct Student students[], int count, int id);

void addStudent(struct Student students[], int *count) 
{
    if (*count >= MAX_STUDENTS) 
    {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    struct Student new_student;

    printf("Enter Student ID: ");
    scanf("%d", &new_student.id);
    printf("Enter Student Name: ");
    getchar();
    fgets(new_student.name, NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0; 
    printf("Enter Student Grade: ");
    scanf("%f", &new_student.grade);

    students[*count] = new_student; 
    (*count)++;
    printf("Student added successfully!\n");
}

void displayStudents(struct Student students[], int count) 
{
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nList of Students:\n");
    printf("ID\tName\t\tGrade\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < count; i++) 
    {
        printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].grade);
    }
}

int searchStudent(struct Student students[], int count, int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (students[i].id == id) 
        {
            return i; 
        }
    }
    return -1; 
}

int main() {
    struct Student students[MAX_STUDENTS]; // array ng mga tanga
    int count = 0; // bilang ng tanga
    int choice, id, index;

    while (1) 
    {
        // user interface
        printf("\nStudent Management System:\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                index = searchStudent(students, count, id);
                if (index != -1) 
                {
                    printf("Student found: ID: %d, Name: %s, Grade: %.2f\n", 
                           students[index].id, students[index].name, students[index].grade);
                } 
                else 
                {
                    printf("Student with ID %d not found.\n", id);
                }
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