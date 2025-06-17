#include <stdio.h>
#include <conio.h>
#include <string.h>

#define INVENTORY 5

struct inventory
{
	int id;
	char item_name[50];
	int part_number[50];
	int quantity;
	float ppU;
}

void userInp (struct inventory inv[], int *count, FILE *ifile);
void dispInp (struct inventory inv[], int count);

int main()
{
	FILE* ifile = fopen("inventory.txt", "a");
	struct inventory inv[INVENTORY];
	int choice, count = 0;
	
	if(ifile == NULL)
	{
		printf("Sorry, can't open this file");
		return 1;
	}
}

void userInp (struct inventory inv[], int *count, FILE *ifile)
{
	if (count >= INVENTORY)
	{
		printf("Sorry, you've reached the maximum count.\n");
		return;
	}
	
	printf("enter the ID: ");;
	scanf("%d", &inv[*count].id)
}

void dispInp (struct inventory inv[], int count)
{
	
}


