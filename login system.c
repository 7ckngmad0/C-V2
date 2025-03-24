#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#define CHAR 13
#define TB 9
#define BSP 8

struct user {
    char Name[50];
    char email[50];
    char password[50];
    char username[50];
    char number[50];
};

void userinput(char ch[50]){
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = '\0';
}

void genUser(char email[50], char username[50]){
    for(int i = 0; i<strlen(email); i++){
        if(email[i] == '@') break;
        else username[i] = email[i];
    }
}

void passWord(char pw[50]){
    char ch;
    int i = 0;
    while(1){
        ch = getch();
        if(ch == CHAR || ch == TB){
            pw[i] = '\0';
            break;
        }
        else if(ch == BSP){
            if(i > 0){
                i--;
                printf("\b \b");
            }
        }
        else{
            pw[i] = ch;
            i++;
            printf("* \b");
        }
    }
}

int main(void){

    FILE *pussy;
    struct user u;
    int choice, track = 0;
    char password2[50];
    
    printf("\n\t\t\t\t\tWelcome to my mema login system\n\n");
    printf("Choose what do you want to do:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

    printf("\nEnter your choice: ");      
    scanf("%d", &choice);
    fgetc(stdin);
    
    switch(choice){
        case 1:
        {
            printf("\nEnter your name: ");
            userinput(u.Name);
            printf("Enter your email: ");
            userinput(u.email);
            printf("Enter your password: ");
            passWord(u.password);
            printf("\nConfirm your password: ");
            passWord(password2);
            printf("\nEnter your phone number: ");
            userinput(u.number);

            if(!strcmp(u.password, password2)){
            genUser (u.email, u.username);
             pussy = fopen("MY LOGIN SYSTEM.txt", "a+");
            fwrite(&u, sizeof(struct user), 1, pussy);
                if(fwrite != 0) {
                printf("\nAccount created successfully, your username is \033[1m%s\033[0m\n\n", u.username);
                printf("\t\t\t\t\tLogin your account to continue\n\n");
                } 
                else{
                printf("Error creating account\n");
                }
                fclose(pussy);
                } 
            else{
            printf("\nPassword does not match\n");
            Beep(900, 500); 
            break;
            
            }
        }   
        
        case 2:
        {
            char username[50], password[50];
            struct user u2;

            printf("Enter your username: ");
            userinput(username);
            printf("Enter your password: ");
            passWord(password);

            pussy = fopen("MY LOGIN SYSTEM.txt", "r");
            while(fread(&u2, sizeof(struct user), 1, pussy)){
                if(!strcmp(u2.username, username) && !strcmp(u2.password, password)){
                    printf("\n\nLogin successful, Welcome \033[1m%s\033[0m\n", u2.Name);
                    printf("|Full name: %s\n", u2.Name);
                    printf("|Username: %s\n", u2.username);
                    printf("|Email: %s\n", u2.email);
                    printf("|Phone Number: %s\n", u2.number);
                    track = 1;
                    break;
                }
                }   
                if (!track) {
                printf("\n\033[41mLogin failed\033[0m\n");
                Beep(900, 500);     
                }
        }    
        fclose(pussy);
        break;
        }
    }