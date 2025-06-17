#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10

struct student
{
    char st_name [100];
    int st_id;
    char st_grade [50];
    char st_course [50];
};

void add_student (struct student students[], int *count);
void disp_students (struct student students[], int count);
int search_students (struct student students[], int count, int id);

int main()
{
    struct student students[MAX_STUDENTS];
    int count = 0;
    int choice, id;

do
{
    printf("\n==Welcome to students checklist/attendance list==\n1.Add Student\n2.Display All the students\n3.Search a student by ID\n4.Exit the program\n\n");
    printf("please choose an option: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            add_student(students, &count);
            break;
        case 2:
            disp_students(students, count);
            break;
        case 3:
            printf("Please enter the student id: \n");
            scanf("%d", &id);
            int index = search_students(students, count, id);
            if (index != -1)
            {
                printf("Student Found: ID: %d, Name: %s, Grade: %s, Course: %s\n", 
                       students[index].st_id, students[index].st_name, students[index].st_grade, students[index].st_course);
            }
            else
            {
               printf("student with the ID %d, not found.\n", id);
            }
            break;
        case 4:
            printf("Exit...\n");
            break;
        default:
            break;
    }
} while (choice != 4);

return 0;
}

void add_student (struct student students[], int *count)
{
    if (*count >= MAX_STUDENTS)
    {
        printf("Sorry, you can't add more students.\n");
        return;
    }

    while (getchar() != '\n');

    printf("Enter student name: ");
    fgets(students[*count].st_name, 100, stdin);
    students[*count].st_name[strcspn(students[*count].st_name, "\n")] = '\0';
    
    printf("Enter student ID: ");
    scanf("%d", &students[*count].st_id);
    while (getchar() != '\n'); 
    
    printf("Enter student grade: ");
    fgets(students[*count].st_grade, 50, stdin);
    students[*count].st_grade[strcspn(students[*count].st_grade, "\n")] = '\0';
    
    printf("Enter student course: ");
    fgets(students[*count].st_course, 50, stdin);
    students[*count].st_course[strcspn(students[*count].st_course, "\n")] = '\0';
    
    (*count)++;
    printf("Student added successfully!\n");
}

void disp_students (struct student students[], int count)
{
    if (count == 0)
    {
        printf("There's no students to display.\n");
        return;
    }

    printf("Student Name\tStudent ID\tStudent Grade\tStudent Course\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s\t\t%d\t\t%s\t%s\n", students[i].st_name, students[i].st_id, students[i].st_grade, students[i].st_course);
    }
}

int search_students (struct student students[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].st_id == id)
        {
            return i;
        }
    }
    return -1;
}

