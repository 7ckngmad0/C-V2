#include <stdio.h>
#include <conio.h>
#include <string.h>

#define DAYS 5

struct weather
{
    int temp;
    int humi;
    char loc[50];
    char day[10];
};

void saveToFile(struct weather w[], int count, FILE *weather_data);
void userInp(struct weather w[], int *count, FILE *weather_data);
void dispWeather(struct weather w[], int count);
void aveData(struct weather w[], int count);
void sortData(struct weather w[], int count);
void deleteData(struct weather w[], int *count, FILE *weather_data);

int main()
{
    FILE* weather_data;
    struct weather w[DAYS];
    int count = 0, choice;

    weather_data = fopen("weather_data.txt", "a+");
    if (weather_data == NULL) {
        printf("Error: Could not open weather data file.\n");
        return 1;
    }

    do {
        printf("\nWelcome to Weather Data Analyzer!\n\n");
        printf("Choose an option:\n1. Add weather data\n2. Display data\n3. Delete all data\n4. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice)
        {
            case 1:
                userInp(w, &count, weather_data);
                break;
            case 2:
                dispWeather(w, count);
                break;
            case 3: 
                deleteData(w, &count, weather_data);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid input, please try again.\n");
                break;
        }
    } while(choice != 4);

    fclose(weather_data);
    return 0;
}

void saveToFile(struct weather w[], int count, FILE *weather_data) 
{
    fclose(weather_data);
    weather_data = freopen("weather_data.txt", "w", weather_data);
    
    for(int i = 0; i < count; i++) 
    {
        fprintf(weather_data, "%d,%d,%s,%s\n", 
            w[i].temp, w[i].humi, w[i].loc, w[i].day);
    }
    fflush(weather_data);
}

void userInp(struct weather w[], int *count, FILE *weather_data)
{
    if (*count >= DAYS)
    {
        printf("Sorry the input count is already on maximum.");
        return;
    }
    while (*count < DAYS)
    {
        printf("Enter weather temperature(celcius): ");
        scanf("%d", &w[*count].temp);
        while(getchar() != '\n');

        printf("Enter weather humidity: ");
        scanf("%d", &w[*count].humi);
        while(getchar() != '\n');

        printf("Enter the location of the weather: ");
        fgets(w[*count].loc, 50, stdin);
        w[*count].loc[strcspn(w[*count].loc, "\n")] = '\0';

        printf("Enter the day of this weather: ");
        fgets(w[*count].day, 10, stdin);
        w[*count].day[strcspn(w[*count].day, "\n")] = '\0';

        (*count)++;
        saveToFile(w, *count, weather_data);
        printf("File added successfully!\n");
    }
    printf("The weather data is full\n");
}

void dispWeather(struct weather w[], int count)
{
    if (count == 0)
    {
        printf("There is no data in this file.\n");
        return;
    }

    printf("%-15s %-12s %-12s %-5s\n", "Temperature", "Humidity", "Location", "Day");

    for (int i = 0; i < count; i++)
    {
        printf("%-15d %-12d %-12s %-5s\n", 
                w[i].temp, w[i].humi, w[i].loc, w[i].day);
    }

    printf("press 1 to display the average of the temperature and humidity.\n");
    printf("press 2 to display the highest and lowest recorded temperature.\n");

    char ch = getch();
    if (ch == '1')
    {
        aveData(w, count);
    }
    else if (ch == '2')
    {
        sortData(w, count);
    }
}

void aveData(struct weather w[], int count)
{
    if (count == 0)
    {
        printf("There is no data in this file.\n");
        return;
    }

    float sumTemp = 0, sumHumi = 0;

    for(int i = 0; i < count; i++)
    {
        sumTemp += w[i].temp;
        sumHumi += w[i].humi;
    }

    float avgTemp = sumTemp / count;
    float avgHumi = sumHumi / count;

    printf("\nWeather Data Averages:\n");
    printf("Average Temperature: %.2f°C\n", avgTemp);
    printf("Average Humidity: %.2f%\n", avgHumi);
}

void sortData(struct weather w[], int count)
{
    struct weather stor;
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(w[j].temp > w[j+1].temp)
            {
                stor = w[j];
                w[j] = w[j+1];
                w[j+1] = stor;
            }
        }
    }
    printf("The lowest recorded temperature is %d°C\n", w[0].temp);
    printf("The highest recorded temperature is %d°C\n", w[count-1].temp);
}

void deleteData(struct weather w[], int *count, FILE *weather_data)
{
    char confirm;
    printf("Do you want to delete all the weather data? (y/n): ");
    scanf(" %c", &confirm);
    while(getchar() != '\n');

    if (confirm == 'y' || confirm == 'Y')
    {
        fclose(weather_data);
        weather_data = fopen("weather_data.txt", "w");
        if (weather_data != NULL)
        {
            *count = 0;
            printf("All weather data has been deleted successfully!\n");
        }
        else
        {
            printf("Error: Could not open the file.\n");
        }
    }
    else
    {
        printf("Operation cancelled.\n");
    }
}
