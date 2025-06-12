#include <stdio.h>
#include <conio.h>
#include <string.h>

#define CHAR 13
#define BSP 8

struct user
{
    char name [50];
    char email [50];
    char password [50];
    char number [50];
    float account_balance;
};

void userInp (char ch[50]);
void passWord (char pw[50]);

int main()
{
    FILE *bank;
    struct user u;
    int choice, choice2, choice3, track = 0;
    float withdraw, deposit;
    memset(&u, 0, sizeof(struct user));  // Initialize all fields to 0
    u.account_balance = 0.0;  // Explicitly set initial balance
    char password2[50];

    printf("==Welcome to my bank management==\n\n");
    printf("Choose what do you want to do:\n");
    printf("1. Register\n2. Login\n3. Exit\n");
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    switch (choice)
    {
    case 1:
        printf("Enter your name: ");
        userInp(u.name);
        printf("Enter your email: ");
        userInp(u.email);
        printf("Enter your phone number: ");
        userInp(u.number);
        printf("Enter your password: ");
        passWord(u.password);
        printf("Confirm password: ");
        passWord(password2);

        if (!strcmp(u.password, password2))
        {
            bank = fopen("BANK MANAGEMENT.txt", "a+");
            fwrite(&u, sizeof(struct user), 1, bank);
            if(fwrite != 0)
            {
                printf("Your account has been created successfully!\n");
                printf("Good day, %s!\n\n", u.name);
                printf("Choose what do you want to do:\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice2);

                switch (choice2)
                {
                case 1:
                    printf("Enter the amount that you want to deposit: ");
                    scanf("%f", &deposit);
                    printf("Current balance before deposit: %.2f\n", u.account_balance);
                    printf("Depositing amount: %.2f\n", deposit);
                    u.account_balance += deposit;
                    printf("New balance after deposit: %.2f\n", u.account_balance);
                    bank = freopen("BANK MANAGEMENT.txt", "r+", bank);
                    fseek(bank, -(long)sizeof(struct user), SEEK_CUR);
                    fwrite(&u, sizeof(struct user), 1, bank);
                    fflush(bank);
                    break;

                case 2:
                    printf("Enter the amount that you want to withdraw: ");
                    scanf("%f", &withdraw);
                    if (withdraw > u.account_balance)
                    {
                        printf("You don't have enough balance for this amount.\n");
                    }
                    else
                    {
                        u.account_balance -= withdraw;
                        fseek(bank, -(long)sizeof(struct user), SEEK_CUR);
                        fwrite(&u, sizeof(struct user), 1, bank);
                        printf("You successfully withdrawed %.2f\n", withdraw);
                        printf("Your new account balance is %.2f\n", u.account_balance);
                    }
                    break;

                case 3:
                    printf("Your account balance is %.2f\n", u.account_balance);
                    break;
                
                case 4:
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
            }
            else
            {
                printf("Error creating an account");
            }
            fclose(bank);
        }
        else
        {
            printf("Password does not match!");
        }
        break;
    case 2:
        char email[50], password[50];
        struct user u2;

        printf("Enter your email: ");
        userInp(email);
        printf("Enter your password: ");
        passWord(password);

        bank = fopen("BANK MANAGEMENT.txt", "r");
        while (fread(&u2, sizeof(struct user), 1, bank))
        {
            if (!strcmp(u2.email, email) && !strcmp(u2.password, password))
            {
                printf("\n\nLogin Sucessful!\n\n");
                printf("Name: %s\n", u2.name);
                printf("Email: %s\n", u2.email);
                printf("Number: %s\n", u2.number);

                printf("What do you want to do:\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice3);

                switch (choice3)
                {
                case 1:
                    printf("Enter the amount that you want to deposit: ");
                    scanf("%f", &deposit);
                    printf("Current balance before deposit: %.2f\n", u2.account_balance);
                    printf("Depositing amount: %.2f\n", deposit);
                    u2.account_balance += deposit;
                    printf("New balance after deposit: %.2f\n", u2.account_balance);
                    bank = freopen("BANK MANAGEMENT.txt", "r+", bank);
                    fseek(bank, -(long)sizeof(struct user), SEEK_CUR);
                    fwrite(&u2, sizeof(struct user), 1, bank);
                    fflush(bank);
                    break;

                case 2:
                    printf("Enter the amount that you want to withdraw: ");
                    scanf("%f", &withdraw);
                    if (withdraw > u2.account_balance)
                    {
                        printf("You don't have enough balance for this amount.\n");
                    }
                    else
                    {
                        u2.account_balance -= withdraw;
                        fseek(bank, -(long)sizeof(struct user), SEEK_CUR);
                        fwrite(&u2, sizeof(struct user), 1, bank);
                        printf("You successfully withdrawed %.2f\n", withdraw);
                        printf("Your new account balance is %.2f\n", u2.account_balance);
                    }
                    break;

                case 3:
                    printf("Your account balance is %.2f\n", u2.account_balance);
                    break;
                
                case 4:
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
                track = 1;
                break;
            }
        }
        fclose(bank);
        if (!track)
        {
            printf("Login Failed");
        }
        break;

    case 3:
        printf("Thank you for using our service!\n");
        return 0;

    default:
        printf("Invalid choice!\n");
        break;
    }
    return 0;
}

void userInp (char ch[50])
{
    fflush(stdin);  // Clear input buffer
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = '\0';
}

void passWord (char pw[50])
{
    int ch;
    int i = 0;
    while(1)
    {
        ch = getch();
        if (ch == CHAR)
        {
            pw[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == BSP)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else 
        {
            pw[i] = ch;
            i++;
            printf("* \b");
        }
    }
}
