#include <stdio.h>
#include <conio.h>
#include <string.h>

#define PATIENT 5

struct patient
	{
		char name[50];
		int age;
		char condition[50];
	};
	
struct doctor
	{
		char name[50];
		char specialty[50];
	};

void userInp(struct patient p[], struct doctor d[], int *count, FILE *pfile);
void dispList(struct patient p[], struct doctor d[], int count);
void filter(struct patient p[], struct doctor d[], int count);
void search (struct patient p[], struct doctor d[], int count);
void delete (struct patient p[], struct doctor d[], int *count, FILE *pfile);

int main()
{
	FILE* pfile = fopen("patients.txt", "a+");
	struct patient p[PATIENT];
	struct doctor d[PATIENT];
	int choice, count = 0;

	if (pfile == NULL)
	{
		perror("Error opening file");
		return 1;
	}
	
	rewind(pfile);
	while (fgets(p[count].name, sizeof(p[count].name), pfile) != NULL) 
	{
		p[count].name[strcspn(p[count].name, "\n")] = '\0';
		if (fscanf(pfile, "%d", &p[count].age) != 1) break;
		while(getchar() != '\n'); // Clear newline
		
		if (fgets(p[count].condition, sizeof(p[count].condition), pfile) == NULL) break;
		p[count].condition[strcspn(p[count].condition, "\n")] = '\0';
		
		if (fgets(d[count].name, sizeof(d[count].name), pfile) == NULL) break;
		d[count].name[strcspn(d[count].name, "\n")] = '\0';
		
		if (fgets(d[count].specialty, sizeof(d[count].specialty), pfile) == NULL) break;
		d[count].specialty[strcspn(d[count].specialty, "\n")] = '\0';
		
		count++;
		if (count >= PATIENT) break;
	}
	
	printf("Welcome to Patient Information System!\n");

	do
	{
	printf("Choose an option\n1. Add patient(w/doctor)\n2. Display list\n3. Search patient\n4. Delete all record\n5. Exit\n");
	printf("Enter your choice: ");
	fflush(stdout);
	scanf("%d", &choice);
	while(getchar() != '\n');
	
	switch(choice)
	{
		case 1:
			userInp(p, d, &count, pfile);
			break;
		case 2:
			dispList(p, d, count);
			break;
		case 3:
			search(p, d, count);
			break;
		case 4:
			delete(p, d, &count, pfile);
			break;
		case 5:
			printf("Exiting...");
			break;
		default:
			printf("Wrong input, exiting...");
	}
	} while (choice != 4);
	fclose(pfile);
	printf("Press any key to exit...\n");
	getchar();
	return 0;
}

void userInp(struct patient p[], struct doctor d[], int *count, FILE *pfile)
{
	if (*count >= PATIENT)
	{
		printf("You've reached the maximum input!\n");
		return;	
	}
	
	printf("Enter patient's name: ");
	fgets(p[*count].name, sizeof(p[*count].name), stdin);
	p[*count].name[strcspn(p[*count].name, "\n")] = '\0';
	
	printf("Enter patient age: ");
	scanf("%d", &p[*count].age);
	while(getchar() != '\n');
	
	printf("Enter patient's condition: ");
	fgets(p[*count].condition, sizeof(p[*count].condition), stdin);
	p[*count].condition[strcspn(p[*count].condition, "\n")] = '\0';
	
	printf("Enter doctor's name: ");
	fgets(d[*count].name, sizeof(d[*count].name), stdin);
	d[*count].name[strcspn(d[*count].name, "\n")] = '\0';
	
	printf("Enter doctor's specialty: ");
	fgets(d[*count].specialty, sizeof(d[*count].specialty), stdin);
	d[*count].specialty[strcspn(d[*count].specialty, "\n")] = '\0';
	
	fprintf(pfile, "%s\n%d\n%s\n%s\n%s\n", 
		p[*count].name, 
		p[*count].age, 
		p[*count].condition, 
		d[*count].name, 
		d[*count].specialty);
	fflush(pfile);
	
	(*count)++;
	printf("Patient w/ doctor added successfully!\n\n");
}

void dispList(struct patient p[], struct doctor d[], int count)
{
	if(count == 0)
	{
		printf("There's no data");
		return;
	}
	
	printf("PATIENT:\n");
	printf("%-20s %-5s %-20s\n", "NAME", "AGE", "CONDITION");
	
	for(int i = 0; i < count; i++)
	{
		printf("%-20s %-5d %-20s\n",
				p[i].name, p[i].age, p[i].condition);
	}
	printf("\n");
	
	printf("DOCTOR:\n");
	printf("%-20s %-20s\n", "NAME", "SPECIALTY");
	
	for(int i = 0; i < count; i++)
	{
		printf("%-20s %-20s\n",
				d[i].name, d[i].specialty);
	}
	printf("\n");
	
	printf("press 1 to filter out the patient with a doctor that has surgery, as their specialty.\n");
	int ch = getch();
	if (ch == '1')
	{
		filter(p, d, count);
	}
}

void filter(struct patient p[], struct doctor d[], int count)
{
	char target[] = "surgery";
	
	for (int i = 0; i < count; i++)
	{
		if (strcmp(d[i].specialty, target) == 0)
		{
			printf("PATIENT:\n");
			printf("%-20s %-5s %-20s\n", "NAME", "AGE", "CONDITION");
			printf("%-20s %-5d %-20s\n", p[i].name, p[i].age, p[i].condition);
			printf("\n");
			
			printf("DOCTOR:\n");
			printf("%-20s %-20s\n", "NAME", "SPECIALTY");
			printf("%-20s %-20s\n", d[i].name, d[i].specialty);
			printf("\n");
		}
	}
}

void search (struct patient p[], struct doctor d[], int count)
{
	char seek[50];
	printf("Enter the name of the patient to search: ");
	scanf("%49s", seek);
	
	int found = 0;
	for(int i = 0; i < count; i++)
	{
		if (strcmp(p[i].name, seek) == 0)
		{
			printf("PATIENT:\n");
			printf("%-20s %-5s %-20s\n", "NAME", "AGE", "CONDITION");
			printf("%-20s %-5d %-20s\n", p[i].name, p[i].age, p[i].condition);
			printf("\n");
			
			printf("DOCTOR:\n");
			printf("%-20s %-20s\n", "NAME", "SPECIALTY");
			printf("%-20s %-20s\n", d[i].name, d[i].specialty);
			printf("\n");
			found = 1;
		}
	}
	if (!found)
		printf("Patient not found");
}

void delete (struct patient p[], struct doctor d[], int *count, FILE *pfile)
{
	char confirm;
	
	printf("Are you sure you want to delete all data? (y\n)\n");
	
	if (confirm == 'y')
	{
		fclose(pfile);
		pfile = fopen("patients.txt", "w");
		if(pfile != NULL)
		{
			*count = 0;
			printf("All data has been deleted successfully!\n");
		}
		else
		{
			printf("Error, could not delete data.\n");
		}
	}
	else
	{
		printf("Operation Cancelled.\n");
	}
}