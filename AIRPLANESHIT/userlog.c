#include "userlog.h"
#include <stdio.h>
#include <string.h>

void init_user_system(struct UserSystem *system) 
{
    system->user_count = 0;
    register_user(system, "admin", "admin123", 0, "admin", "admin", 1);
}

int register_user(struct UserSystem *system, const char *username, const char *password, 
                 int age, const char *street, const char *city, int is_admin) 
                 {
    if (system->user_count >= MAX_USERS) 
    {
        return 0;  // System full
    }

    for (int i = 0; i < system->user_count; i++) 
    {
        if (strcmp(system->users[i].username, username) == 0) 
        {
            return 0;
        }
    }

    struct User *new_user = &system->users[system->user_count];
    strncpy(new_user->username, username, MAX_STRING - 1);
    strncpy(new_user->password, password, MAX_STRING - 1);
    new_user->age = age;
    strncpy(new_user->address.street, street, MAX_STRING - 1);
    strncpy(new_user->address.city, city, MAX_STRING - 1);
    new_user->is_admin = is_admin;
    new_user->has_reservation = 0;
    new_user->reserved_seat[0] = '\0';

    system->user_count++;
    return 1;
}

int login_user(struct UserSystem *system, const char *username, const char *password) 
{
    for (int i = 0; i < system->user_count; i++) 
    {
        if (strcmp(system->users[i].username, username) == 0 &&
            strcmp(system->users[i].password, password) == 0) 
            {
            return i;
        }
    }
    return -1;
}

void display_user_details(struct UserSystem *system, const char *seat) 
{
    // Convert input seat to uppercase
    char uppercase_seat[10];
    strncpy(uppercase_seat, seat, sizeof(uppercase_seat) - 1);
    uppercase_seat[sizeof(uppercase_seat) - 1] = '\0';
    
    // Convert letter to uppercase if it's lowercase
    int len = strlen(uppercase_seat);
    if (len > 0 && uppercase_seat[len-1] >= 'a' && uppercase_seat[len-1] <= 'z') {
        uppercase_seat[len-1] = uppercase_seat[len-1] - 'a' + 'A';
    }

    for (int i = 0; i < system->user_count; i++) 
    {
        if (system->users[i].has_reservation && 
            strcmp(system->users[i].reserved_seat, uppercase_seat) == 0) 
            {
            printf("Seat %s is taken by %s\n", uppercase_seat, system->users[i].username);
            return;
        }
    }
    printf("No user found for seat %s\n", seat);
}

int get_user_index(struct UserSystem *system, const char *username) 
{
    for (int i = 0; i < system->user_count; i++) 
    {
        if (strcmp(system->users[i].username, username) == 0) 
        {
            return i;
        }
    }
    return -1;
}

void save_passenger_list(struct UserSystem *system) 
{
    FILE *file = fopen("plist.txt", "w");
    if (file == NULL) 
    {
        printf("Error: Could not open plist.txt for writing\n");
        return;
    }

    fprintf(file, "Passenger List\n");
    fprintf(file, "==============\n\n");

    for (int i = 0; i < system->user_count; i++) 
    {
        if (system->users[i].has_reservation && !system->users[i].is_admin) 
        {
            fprintf(file, "Seat Number: %s\n", system->users[i].reserved_seat);
            fprintf(file, "Name: %s\n", system->users[i].username);
            fprintf(file, "Age: %d\n", system->users[i].age);
            fprintf(file, "Address: %s, %s\n", 
                    system->users[i].address.street,
                    system->users[i].address.city);
            fprintf(file, "-------------------\n\n");
        }
    }

    fclose(file);
    printf("Passenger list has been saved to plist.txt\n");
} 