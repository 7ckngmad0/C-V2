#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#define CHAR 13
#define TB 9
#define BSP 8

struct profile {
    char name[50];
    char phone_number[50];
    char email[50];
    char password[50];
    char username[50];
    char account_number[50];
    float account_balance;
};

    void userinput(char ch[50])
    {
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = '\0';
}

    void Usern(char email[50], char username[50])
    {
    for(int i = 0; i < strlen(email); i++)
    {
        if(email[i] == '@') break;
        else username[i] = email[i];
    }
    username[strlen(email)] = '\0';
}

    void passWord(char pw[50])
    {
    char ch;
    int i = 0;
    while(1){
        ch = getch();
        if(ch == CHAR || ch == TB)
        {
            pw[i] = '\0';
            break;
        }
        else if(ch == BSP)
        {
            if(i > 0){
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

    void Number(char num[50])
    {
        char nm;
        int i = 0;
        while(1){
            nm = getch();
            if(nm == CHAR || nm == TB)
            {
                num[i] = '\0';
                break;
            }
            else if(nm == BSP){
                if(i > 0){
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                num[i] = nm;
                i++;
                printf("* \b");
            }
        }
    }
int main(void)
{
    FILE *bank;
    struct profile p;
    int choice, deci, deposit, withdraw, track = 0;
    p.account_balance = 0.00;
    char password2[50];

    printf("BANK MANAGEMENT SHITTTTTTTTTTTTT\n\n");
    printf("1. Create an account\n");
    printf("2. Login to an account\n");
    printf("3. Exit the program\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    
    switch(choice)
    {
        case 1:
        {
            printf("Enter your name: ");
            userinput(p.name);
            printf("Enter your phone number: ");
            userinput(p.phone_number);
            printf("Enter your email: ");
            userinput(p.email);
            printf("Enter your password: ");
            passWord(p.password);
            printf("\nConfirm your password: ");
            passWord(password2);
            printf("\nEnter your account number: ");
            Number(p.account_number);
            getchar();
            

            if(!strcmp(p.password, password2)){
                Usern (p.email, p.username);
                bank = fopen("BANK MANAGEMENT SYSTEM.txt", "a+");
                fwrite(&p, sizeof(struct profile), 1, bank);
                if(fwrite != 0) {
                printf("\nAccount created successfully, your username is \033[1m%s\033[0m\n\n", p.username);
                printf("\t\t\t\t\tLogin to your bank account to continue\n\n");
                } 
                else{
                printf("Error creating account\n");
                }
                fclose(bank);
                } 
            else{
            printf("\nPassword does not match\n");
            Beep(900, 500); 
            break;
        }
        case 2:
        {
            char username[50], password[50];
            struct profile p2;

            printf("Enter your username: ");
            userinput(username);
            printf("Enter your password: ");
            passWord(password);

            bank = fopen("BANK MANAGEMENT SYSTEM.txt", "r");
            if (bank == NULL) {
                printf("Error opening file for reading.\n");
                return 1; 
            }

            while (fread(&p2, sizeof(struct profile), 1, bank)) 
            {
                if (!strcmp(p2.username, username) && !strcmp(p2.password, password)) 
                {
                    printf("|Name: %s\n", p2.name);
                    printf("|Phone number: %s\n", p2.phone_number);
                    printf("|Email: %s\n", p2.email);
                    printf("|Account number: %s\n", p2.account_number);
                    printf("|Account balance: %.2f\n", p2.account_balance); 

                    track = 1;

                    printf("Do you want to deposit or withdraw money?\n");
                    printf("1. Deposit\n");
                    printf("2. Withdraw\n");
                    printf("3. Exit\n");

                    printf("Enter your choice: ");
                    scanf("%d", &deci);

                    switch (deci) 
                    {
                        case 1: 
                        {
                            printf("Enter the amount you want to deposit: ");
                            scanf("%d", &deposit);
                            p2.account_balance += deposit;
                            printf("Your new account balance is: %.2f\n", p2.account_balance);
                            break;
                        }
                        case 2: 
                        {
                            printf("Enter the amount you want to withdraw: ");
                            scanf("%d", &withdraw);
                            if (withdraw > p2.account_balance) 
                            {
                                printf("Insufficient funds!\n");
                            } 
                            else 
                            {
                                p2.account_balance -= withdraw;
                                printf("Your new account balance is: %.2f\n", p2.account_balance);
                            }
                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                    break;
                }
            }
            fclose(bank);
        }
        case 3:
        {
            printf("\nThank you for using the program\n");
            return 0;
        }
        default:
        {
            printf("Invalid input\n");
            break;
        }
        }
    }
}