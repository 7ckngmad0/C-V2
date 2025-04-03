#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100 // for maximum number of students
#define NAME_LENGTH 50 // for student name length
#define DOG "students.txt" // for file handling

struct StudentID
{
    int id;
    char name[50];
    float grade;
};

void AddiStudent(struct StudentID students[], int *count) // Function to add a student
{
    if (*count >= MAX_STUDENTS) // Check if the maximum number of students has been reached
    {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    struct StudentID new_student; // Create a new student structure
    printf("Enter Student ID: ");
    scanf("%d", &new_student.id);
    printf("Enter Student Name: ");
    getchar();
    fgets(new_student.name, NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;
    printf("Enter Student Grade: ");
    scanf("%f", &new_student.grade);

    students[(*count)++] = new_student; // Add the new student to the array and increment the count
    printf("Student added successfully!\n");
    }

void Display(struct StudentID students[], int count) // function to display all students
    {
        if (count == 0) // Check if there are no students to display
        {
            printf("No students to display.\n");
            return;
        }
            printf("\nList of Students:\nID\tName\tGrade\n-----------------------------------\n");
            for (int i = 0; i < count; i++)
        {
            printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].grade);
        }
    }

int Search(struct StudentID students[], int count, int id) // function to search for a student by ID
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id) return i;
    }
    return -1;
}

void FileSaving (struct StudentID students[], int count) // saving the student data
{
    FILE *file = fopen(DOG, "w"); // w means it's opened in write mode
    if (file == NULL) // Checker if the file was opened successfully
    {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < count; i++) // Looping sa lahat ng students
    {
        fprintf(file, "%d %s %d", students[i].id, students[i].name, students[i].grade); // Write the student data sa file
    }
    fclose(file); // Close the file
    printf("Data was saved to the file successfully.\n"); // Assurance lang boss
}

void DeleteStudent (struct StudentID students[], int *count, int id) //function for deletion of an ID
{
    int index = Search (students, *count, id); //call for the search function para mahanap yung student na ide-delete yung ID
    if (index == -1) //this is for checking again
    {
        printf("Student with ID %d not found.\n", id); // If the id was not found
        return;
    }
    for (int i = index; i < *count - 1; i++)
    {
        students[i] = students[i + 1]; // Shifting
    }
    (*count)--; // Decrease the count of students
    printf("Student with ID %d deleted successfully.\n", id); // Assurance lang ulit
}

void FileLoading (struct StudentID students[], int *count) // Loading the student data galing sa file na sinave
{
    FILE *file = fopen(DOG, "r"); // r means it's opened in read mode
    if (file == NULL) // Chechker if the file was opened successfully
    {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(file, "%d %s %d", &students[*count].id, students[*count].name, &students[*count].grade) == 3) // Looping sa file until the end of the file
    {
        (*count)++; //pandagdag sa bilang
    }
}

int main()
{
    struct StudentID students[MAX_STUDENTS]; // Array to hold student records
    int count = 0, choice, id; // Variables to keep track of the number of students and user choice

    FileLoading(students, &count); // Load existing student data from file

    while (1) // Infinite loop to keep the program running hanggang sa mag exit si user
    {
        printf("\nMenu:\n1. Add Student\n2. DIsplay the list of students\n3. Search Student using their ID\n4. Delete a student\n5. Save and Exit\nEnter your choice: ");
        scanf("%d", &choice); 
        
        switch (choice)
        {
            case 1: AddiStudent(students, &count); break; // calling the void function to add a student
            case 2: Display (students, count); break; // calling the void function to display all students
            case 3:
                printf("Enther the ID of the student you want to search for: ");
                scanf("%d", &id); // Get the ID of the student to search for
                int index = Search(students, count, id); // Call the search function
                if (index != -1) // for checking if the student was found
                {
                    printf("Student found: ID: %d, Name: %s, Grade: %.2f\n", students[index].id, students[index].name, students[index].grade);
                }
                else
                {
                    printf("Student with ID %d not found.\n", id); // If the student was not found
                }
                break;
            case 4: //delete an ID
                printf("Enter the ID of the student that you want to delete: ");
                scanf("%d", &id); // Get the ID of the student to delete
                DeleteStudent(students, &count, id); // Call the function to delete the student
                break;
            case 5: //Save and Exit
                FileSaving(students, count); // Call the function to save data to file  
                printf("Exiting...\n"); // Message to indicate exit
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please try again.\n"); // If the user enters an invalid choice
        }
    }
}