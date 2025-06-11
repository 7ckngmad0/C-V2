#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "userlog.h"

struct Seat 
{
    int is_booked;
};

void DispSeats(struct Seat seats[5][4]) 
{
    printf("\nCurrent seat availability:\n");
    for (int row = 0; row < 5; row++) 
    {
        printf("%d ", row + 1);
        for (int col = 0; col < 4; col++) 
        {
            char seat_letter = 'A' + col;
            if (seats[row][col].is_booked) 
            {
                printf("\033[1mX \033[0m");
            }
            else 
            {
                printf("%c ", seat_letter);
            }
        }
        printf("\n");
    }
}

int for_input(const char *input, int *row, int *col) 
{
    if (strlen(input) < 1) return 0;

    char *endr;
    long row_num = strtol(input, &endr, 10);
    if (row_num < 1 || row_num > 5) return 0;

    *row = (int)(row_num - 1);

    if (*endr == '\0') return 0;
    char seat_char = *endr;

    if (seat_char >= 'a' && seat_char <= 'd') 
    {
        seat_char = seat_char - 'a' + 'A';
    }
    
    if (seat_char < 'A' || seat_char > 'D') return 0;
    
    *col = seat_char - 'A';
    return 1;
}

void handle_admin_menu(struct UserSystem *system) 
{
    printf("\n=== Admin Menu ===\n");
    printf("1. View all reservations\n");
    printf("2. View specific seat details\n");
    printf("3. Delete passenger record\n");
    printf("4. Exit admin menu\n");
    
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch(choice) 
    {
        case 1:
            printf("\nAll Reservations:\n");
            for (int i = 0; i < system->user_count; i++) 
            {
                if (system->users[i].has_reservation) {
                    printf("User: %s, Seat: %s, Age: %d, Address: %s, %s\n",
                           system->users[i].username,
                           system->users[i].reserved_seat,
                           system->users[i].age,
                           system->users[i].address.street,
                           system->users[i].address.city);
                }
            }
            break;
        case 2:
            {
                char seat[10];
                printf("Enter seat number (e.g., 1A): ");
                scanf("%s", seat);
                getchar();
                display_user_details(system, seat);
            }
            break;
        case 3:
            {
                char username[MAX_STRING];
                printf("Enter username to delete record: ");
                fgets(username, MAX_STRING, stdin);
                username[strcspn(username, "\n")] = 0;
                
                int user_index = get_user_index(system, username);
                if (user_index >= 0 && !system->users[user_index].is_admin) {
                    // Clear the reservation
                    system->users[user_index].has_reservation = 0;
                    system->users[user_index].reserved_seat[0] = '\0';
                    
                    // Update the passenger list file
                    save_passenger_list(system);
                    printf("Successful deletion of record for user: %s\n", username);
                } else {
                    printf("User not found or is an admin.\n");
                }
            }
            break;
        case 4:
            return;
        default:
            printf("Invalid choice!\n");
    }
}

int handle_login_menu(struct UserSystem *system) 
{
    while (1) 
    {
        printf("\n=== Login Menu ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        if (choice == 3) return -1;

        if (choice == 1) 
        {
            char username[MAX_STRING], password[MAX_STRING];
            printf("Enter username: ");
            fgets(username, MAX_STRING, stdin);
            username[strcspn(username, "\n")] = 0;
            
            printf("Enter password: ");
            fgets(password, MAX_STRING, stdin);
            password[strcspn(password, "\n")] = 0;

            int user_index = login_user(system, username, password);
            if (user_index >= 0) {
                printf("Login successful!\n");
                return user_index;
            }
            else 
            {
                printf("Invalid username or password!\n");
            }
        }
        else if (choice == 2) 
        {
            char username[MAX_STRING], password[MAX_STRING], street[MAX_STRING], city[MAX_STRING];
            int age;

            printf("Enter username: ");
            fgets(username, MAX_STRING, stdin);
            username[strcspn(username, "\n")] = 0;
            
            printf("Enter password: ");
            fgets(password, MAX_STRING, stdin);
            password[strcspn(password, "\n")] = 0;
            
            printf("Enter age: ");
            scanf("%d", &age);
            getchar(); // Clear newline
            
            printf("Enter street: ");
            fgets(street, MAX_STRING, stdin);
            street[strcspn(street, "\n")] = 0;
            
            printf("Enter city/province: ");
            fgets(city, MAX_STRING, stdin);
            city[strcspn(city, "\n")] = 0;

            if (register_user(system, username, password, age, street, city, 0)) 
            {
                printf("Registration successful! Please login.\n");
            } 
            else 
            {
                printf("Registration failed. Username might already exist.\n");
            }
        }
    }
}

int main() 
{
    struct Seat seats[5][4] = {{{0}}};
    struct UserSystem system;
    init_user_system(&system);
    
    char input[20];
    int booked_count = 0;
    const int total_seats = 5 * 4;

    while (1) 
    {
        int user_index = handle_login_menu(&system);
        if (user_index < 0) break;

        struct User *current_user = &system.users[user_index];
        
        if (current_user->is_admin) 
        {
            handle_admin_menu(&system);
            continue;
        }

        while (1) {
            DispSeats(seats);

            printf("\n\033[1mEnter a command:\n");
            printf("- book seat (ex: 1A)\n");
            printf("- cancel (cancel 1A)\n");
            printf("- change (change 1A 1B)\n");
            printf("- logout\n");
            printf("Command: \033[0m");
            
            if (fgets(input, sizeof(input), stdin) == NULL) break;
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "logout") == 0) {
                printf("Logging out...\n");
                break;
            }

            else if (strncmp(input, "cancel ", 7) == 0) 
            {
                char *Scancel = input + 7;
                int row, col;
                if (!for_input(Scancel, &row, &col)) 
                {
                    printf("Invalid input. Usage (cancel SEAT ex: cancel 1A).\n");
                    continue;
                }

                char seat_str[10];
                sprintf(seat_str, "%d%c", row + 1, 'A' + col);
                if (!current_user->has_reservation || 
                    strcmp(current_user->reserved_seat, seat_str) != 0) 
                    {
                    printf("You can only cancel your own reservation.\n");
                    continue;
                }

                seats[row][col].is_booked = 0;
                current_user->has_reservation = 0;
                current_user->reserved_seat[0] = '\0';
                booked_count--;
                printf("Seat %s cancelled successfully.\n", Scancel);
                save_passenger_list(&system);
            }
            
            else if (strncmp(input, "change ", 7) == 0) 
            {
                char *book = input + 7;
                char *from = book;
                char *space = strchr(from, ' ');
                if (!space) 
                {
                    printf("Invalid change command. Usage (change OLDSEAT NEWSEAT ex: change 1A 1B)\n");
                    continue;
                }

                *space = '\0';
                char *to = space + 1;

                int old_row, old_col, new_row, new_col;

                if (!for_input(from, &old_row, &old_col)) 
                {
                    printf("Invalid old seat: %s\n", from);
                    continue;
                }
                if (!for_input(to, &new_row, &new_col)) 
                {
                    printf("Invalid new seat: %s\n", to);
                    continue;
                }

                char old_seat_str[10];
                sprintf(old_seat_str, "%d%c", old_row + 1, 'A' + old_col);
                if (!current_user->has_reservation || 
                    strcmp(current_user->reserved_seat, old_seat_str) != 0) 
                    {
                    printf("You can only change your own reservation.\n");
                    continue;
                }

                if (seats[new_row][new_col].is_booked) 
                {
                    char new_seat_str[10];
                    sprintf(new_seat_str, "%d%c", new_row + 1, 'A' + new_col);
                    display_user_details(&system, new_seat_str);
                    printf("Please choose another seat.\n");
                    continue;
                }

                seats[old_row][old_col].is_booked = 0;
                seats[new_row][new_col].is_booked = 1;
                
                // Update user's reservation
                sprintf(current_user->reserved_seat, "%d%c", new_row + 1, 'A' + new_col);
                printf("Seat %s changed to %s successfully.\n", from, to);
                save_passenger_list(&system);
            }
            else
            {
                int row, col;
                if (!for_input(input, &row, &col)) 
                {
                    printf("Invalid input. Please try again.\n");
                    continue;
                }
                
                if (seats[row][col].is_booked) 
                {
                    char seat_str[10];
                    sprintf(seat_str, "%d%c", row + 1, 'A' + col);
                    display_user_details(&system, seat_str);
                    printf("Please choose another seat.\n");
                }
                else
                {
                    if (current_user->has_reservation) 
                    {
                        printf("You already have a reservation. Please cancel or change it first.\n");
                        continue;
                    }

                    seats[row][col].is_booked = 1;
                    booked_count++;

                    current_user->has_reservation = 1;
                    sprintf(current_user->reserved_seat, "%d%c", row + 1, 'A' + col);
                    
                    printf("\nSeat %s booked successfully.\n", input);
                    if (booked_count == total_seats) 
                    {
                        printf("All seats are booked!\n");
                        break;
                    }
                    save_passenger_list(&system);
                }
            }
        }
    }
    return 0;
}