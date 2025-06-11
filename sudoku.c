#include <stdio.h>

#define N 9

void displayGrid (int grid[N][N]);
int userInp (int grid[N][N], int* rowIn, int* colIn, int* numIn);
int validationGrid (int grid[N][N], int row, int col, int num);
int gameChecker (int grid[N][N]);

int main()
{
    int grid[N][N] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                       { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                       { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                       { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                       { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                       { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                       { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                       { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                       { 0, 0, 0, 0, 8, 0, 0, 7, 9 } }; 
    int runningGame = 1;
    int row, col, num;

    while (runningGame)
    {
        displayGrid (grid);
        int result = userInp (grid, &row, &col, &num);
        int valid = validationGrid(grid, row, col, num);

        if (result == -1)
        {
            printf("Thank you for playing the game!");
            return 0;
        }

        if (result && valid)
        {
            grid[row][col] = num;
            if(gameChecker(grid))
            {
                printf("Congratulations! You won the game!");
                runningGame = 0;
            }
        }

    }
}



void displayGrid (int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int userInp (int grid[N][N], int* rowIn, int* colIn, int* numIn)
{
    int valid_input = 0;
    int change;

    printf("\nEnter -1 to exit.\n");
    printf("Enter the row, column, and the number that you want to put.\n\n");

    do
    {
        valid_input = 1;

        printf("Row: ");
        scanf("%d", rowIn);
        printf("Col: ");
        scanf("%d", colIn);
        printf("Num: ");
        scanf("%d", numIn);

            if (*rowIn == -1)
            {
                printf("Thank you for playing the game!");
                return 0;
            }

            if (*rowIn > 9 || *rowIn < 1)
            {
                printf("You can only input the value 1-9.\n");
                valid_input = 0;
            }

            if (*colIn > 9 || *colIn < 1)
            {
                printf("You can only input the value 1-9.\n");
                valid_input = 0;
            }

            if (*numIn > 9 || *numIn < 1)
            {
                printf("You can only input the value 1-9.\n");
                valid_input = 0;
            }

            if (grid[*rowIn - 1][*colIn - 1] != 0)
            {
                printf("Do you want to replace this number (1 - Yes, 2 - No): \n");
                scanf("%d", &change);
                if (change == 1)
                {
                    // temporary store
                    int original_number = grid[*rowIn - 1][*colIn - 1];
                    //temporary set
                    grid[*rowIn - 1][*colIn - 1] = 0;

                    if (validationGrid (grid, *rowIn, *colIn, *numIn))
                    {
                        valid_input = 1;
                    }
                    else
                    {
                        grid[*rowIn - 1][*colIn - 1] = original_number;
                        valid_input = 0; 
                    }
                }
                else if (change == 2)
                {
                    valid_input = 0;
                }
                else
                {
                    printf("This is an invalid input.");
                    valid_input = 0;
                }
            }
    }

    while (valid_input == 0);
    *rowIn = *rowIn - 1;
    *colIn = *colIn - 1;
    return 1;
}

int validationGrid (int grid[N][N], int row, int col, int num)
{
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num)
        {
            printf("This number already exists in this row.\n");
            return 0;
        }
    }

    for (int y = 0; y < N; y++)
    {
        if(grid[y][col] == num)
        {
            printf("This number already exists in this column.\n");
            return 0;
        }
    }

    int rowCube = row - row % 3, colCube = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + rowCube][j + colCube] == num)
            {
                printf("this number is already in this cube.\n");
                return 0;
            }
        }
    } 
    return 1;
}

int gameChecker (int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}