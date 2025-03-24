#include <stdio.h>
#include <string.h>

#define MAX_STUDENT_NAME 50
#define MAX_BOOKS 10

struct Description
{
    char title[100];
    char author[100];
    int date;
    char link[500];
};

struct Student 
{
    char name[MAX_STUDENT_NAME];
    long long phone_number;
    long long student_id;
};

int main(void)
{
    int i, book_number;
    int books;
    int borrowed_books[MAX_BOOKS];
    struct Description description [MAX_BOOKS];
    struct Student student;

    printf("\033[1m\033[3mThis is a library sample program\033[0m\n\n");

    printf("State your name: ");
    printf("\033[1m");
    scanf(" %49s", student.name);
    printf("\033[0m");
    printf("Enter your phone number: ");
    printf("\033[1m");
    scanf("%lld", &student.phone_number);
    printf("\033[0m");
    printf("Enter your student id: ");
    printf("\033[1m");
    scanf("%lld", &student.student_id);
    printf("\033[0m");

    printf("\nEnter number 1 if you want to see the list of books.\n");
    printf("Enter number 0 if you want to exit the program\n");

    printf("Enter number: ");
    scanf(" %d", &i);

    if (i==1)
    {
        strcpy(description[0].title, "\033[34m\033[3mCode Complete\033[0m");
        strcpy(description[0].author, "Steve McConnell");
        strcpy(description[0].link, "https://people.engr.tamu.edu/slupoli/notes/ProgrammingStudio/supplements/Code%20Complete%202nd.pdf");
        strcpy(description[1].title, "\033[34m\033[3mClean Code: A Handbook of Agile Software Craftsmanship\033[0m");
        strcpy(description[1].author, "Robert C. Martin");
        strcpy(description[1].link, "https://github.com/sdcuike/Clean-Code-Collection-Books/blob/master/The.Robert.C.Martin.Clean.Code.Collection.2011.11.pdf");
        strcpy(description[2].title, "\033[34m\033[3mIntroduction to Algorithms\033[0m");
        strcpy(description[2].author, "Thomas H. Cormen");
        strcpy(description[2].link, "https://dl.ebooksworld.ir/books/Introduction.to.Algorithms.4th.Leiserson.Stein.Rivest.Cormen.MIT.Press.9780262046305.EBooksWorld.ir.pdf");
        strcpy(description[3].title, "\033[34m\033[3mThe Hacker's Handbook: The Essential Guide to Computer Security\033[0m");
        strcpy(description[3].author, "Hugo Cornwall");
        strcpy(description[3].link, "https://theswissbay.ch/pdf/Gentoomen%20Library/Security/%28eBook%20-%20PDF%29%20Hugo%20Cornwall%20-%20The%20Hacker%27s%20Handbook%20.pdf");
        strcpy(description[4].title, "\033[34m\033[3mGray Hat Hacking: The Ethical Hacker's Handbook\033[0m");
        strcpy(description[4].author, "Shon Harris");
        strcpy(description[4].link, "https://pages.cs.wisc.edu/~ace/media/gray-hat-hacking.pdf");
        strcpy(description[5].title, "\033[34m\033[3mWeb Application Hackers Handbook: Finding and Exploiting Security Flaws\033[0m");
        strcpy(description[5].author, "Dafydd Stuttard and Marcus Pinto");
        strcpy(description[5].link, "https://www.beiruteyecenter.com/uploads/3794_1008_4334.pdf");
        strcpy(description[6].title, "\033[34m\033[3mPython Crash Course: A Hands-on, Project-Based Introduction to Programming\033[0m");
        strcpy(description[6].author, "Eric Matthes");
        strcpy(description[6].link, "https://khwarizmi.org/wp-content/uploads/2021/04/Eric_Matthes_Python_Crash_Course_A_Hands.pdf");
        strcpy(description[7].title, "\033[34m\033[3mDeep Learning with Python\033[0m");
        strcpy(description[7].author, "François Chollet");
        strcpy(description[7].link, "https://sourestdeeds.github.io/pdf/Deep%20Learning%20with%20Python.pdf");
        strcpy(description[8].title, "\033[34m\033[3mCompilers: Principles, Techniques, and Tools\033[0m");
        strcpy(description[8].author, "Alfred Aho, Monica Lam, Ravi Sethi, and Jeffrey Ullman");
        strcpy(description[8].link, "https://repository.unikom.ac.id/50738/1/Compilers%20-%20Principles,%20Techniques,%20and%20Tools%20(2006).pdf");
        strcpy(description[9].title, "\033[34m\033[3mBlack Hat Python: Python Programming for Hackers and Pentesters\033[0m");
        strcpy(description[9].author, "Justin Seitz");
        strcpy(description[9].link, "https://olinux.net/wp-content/uploads/2019/01/python.pdf");

        for (int j = 0; j < MAX_BOOKS; j++)
        {
            printf("%d. Title: %s\n", j + 1, description[j].title);
            printf("Author: %s\n\n", description[j].author);
        }

        printf("How many books do you want to read: ");
        scanf("%d", &books);
        if (books > MAX_BOOKS)
        {   
            printf("You can only read a maximum of 10 books.\n");
            return 0;
        }
            printf("what are the books that you want to read?\n");
        for (int book_number = 0; book_number < books; book_number++)
        {
            printf("Enter the number of the book: ");
            scanf("%d", &borrowed_books[book_number]); 

            if (borrowed_books[book_number] < 1 || borrowed_books[book_number] > 10)
            {
                printf("Invalid book number. Please try again.\n");
                book_number--;
            }
        }

        printf("\n----------------Library Management System----------------\n");
        printf("Student Name: \033[1m%s\n", student.name);
        printf("Phone Number: \033[1m%lld\n", student.phone_number);
        printf("Student ID: \033[1m%lld\n\n", student.student_id);
        printf("\033[1m\033[3m%s, Here are the books that you choose:\n\n\033[0m", student.name);

        for (int book_number = 0; book_number < books; book_number++)
        {       
            if (borrowed_books[book_number] >= 1 && borrowed_books[book_number] <= 10)
            {
                printf("%d. \033]8;;%s\033\\%s\033]8;;\033\\\n", book_number + 1, description[borrowed_books[book_number] - 1].link, description[borrowed_books[book_number] - 1].title);
                printf("\033[1m\033[3mAuthor: \033[0m%s\n\n", description[borrowed_books[book_number] - 1].author);
            }
            else
            {
                printf("Invalid book number. Please try again.\n");
            }   
        }

        printf("The title of the book is clickable, it will redirect to the pdf of the book.");
    }
    else if (i == 0)
    {
        printf("Thank you for using the program\n");
        return 0;
    }
    else
    {
        printf("Invalid input\n");
    }
}