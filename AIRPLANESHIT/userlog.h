#ifndef USERLOG_H
#define USERLOG_H

#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_STRING 100

struct Address 
{
    char street[MAX_STRING];
    char city[MAX_STRING];
};

struct User 
{
    char username[MAX_STRING];
    char password[MAX_STRING];
    int age;
    struct Address address;
    int is_admin;
    char reserved_seat[10];
    int has_reservation;
};

struct UserSystem 
{
    struct User users[MAX_USERS];
    int user_count;
};

int register_user(struct UserSystem *system, const char *username, const char *password, 
                 int age, const char *street, const char *city, int is_admin);
int login_user(struct UserSystem *system, const char *username, const char *password);
void display_user_details(struct UserSystem *system, const char *seat);
int get_user_index(struct UserSystem *system, const char *username);
void init_user_system(struct UserSystem *system);
void save_passenger_list(struct UserSystem *system);

#endif 