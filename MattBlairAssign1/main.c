//
// Created by mattb on 2023-01-18.
// A program to validate a sudoku puzzle
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INPUT_MIN 1
#define INPUT_MAX 9
#define GRID_MAX 9

int sgrid[GRID_MAX][GRID_MAX]; // Had to create this to be able to use outputs from functions that couldn't be

// Check the flag in sudoku() for duplicates and print the according message
void flagCheck (int flagState)
{
    if (flagState == 1)
    {
        printf("The given puzzle is not valid\n");
    }
    else
    {
        printf("The given puzzle is valid\n");
    }
}

void printGrid(int grid[][GRID_MAX])
{
    int i, j;
    printf("---------- Sudoku Grid ----------\n");
    for (i=0; i<GRID_MAX; i++)
    {
        for (j=0; j<GRID_MAX; j++)
        {
            int val = grid[i][j];
            printf("%d   ", val);
        }
        printf("\n");
    }
    printf("\n");
}

void generateRandomPuzzle(int firstTwoRows[])
{
    int i, j;
    for (i=0; i<GRID_MAX; i++)
    {
        for (j=0; j<GRID_MAX; j++)
        {
            if (i==0)
            {
                sgrid[i][j] = firstTwoRows[j];
            } else if (i==1)
            {
                sgrid[i][j] = firstTwoRows[j+9];
            } else {
                sgrid[i][j] = (rand() % (INPUT_MAX - INPUT_MIN + 1)) + INPUT_MIN;;
            }
        }
    }
}

void getUserInput()
{
    int row = 1;
    printf("Enter the first row of your Sudoku grid\nEnter a number between 1-9 and press 'Enter'\n");
    printf("Please ensure you do not enter any duplicates\nEnter row %d now:\n", row);
    int userInput[18];
    int userInt, i=0, j;
    while (i<18) // Get list of ints from the user
    {
        scanf("%d", &userInt);
        if (i == 8) {
            row++;
            printf("Enter row %d now:\n", row);
        }
        if (userInt < INPUT_MIN || userInt > INPUT_MAX)
        {
            printf("Please enter a number between 1 and 9\n");
            i = 0;
            getUserInput();
        }
        userInput[i] = userInt;
        i++;
    }
    for (i=0; i<GRID_MAX; i++) // Check for duplicates in the list of ints from user
    {
        for (j=i+1; j<GRID_MAX-1; j++)
        {
            if (userInput[i] == userInput[j])
            {
                printf("You entered a duplicate number (%d)\n", userInput[j]);
            }
        }
    }
    generateRandomPuzzle(userInput);
}

void validateSudoku(int grid[GRID_MAX][GRID_MAX])
{
    int i, j, k, n, flag; // We will raise the flag if we find any duplicates

    for (i=0; i < 9; i++) // Iterate through each row in the puzzle
    {
        for (j=0; j < 9; j++) // Iterate through each row element
        {
            int val = grid[i][j]; // Store the current value that we are working with i.e. 5

            for (k = j+1; k < GRID_MAX-1; k++) // Check the row for duplicates
            {
                int nextInRow = grid[i][k]; // Get value of cell we are comparing val to
                if (val == nextInRow)
                {
                    flag = 1;
                    break;
                }
            }
            for (n=i+1; n<8; n++) // Check the Column for duplicates
            {
                int nextInCol = grid[n][j]; // Get value of cell we are comparing val to
                if (val == nextInCol)
                {
                    flag = 1;
                    break;
                }
            }
        }
    }
    flagCheck(flag);
    printGrid(grid);
}

int main (int argc, char** argv)
{
    int testGrid[ ][ 9 ] = {{5,3,4,6,7,8,9,1,2},
                            {6,7,2,1,9,5,3,4,8},
                            {1,9,8,3,4,2,5,6,7},
                            {8,5,9,7,6,1,4,2,3},
                            {4,2,6,8,5,3,7,9,1},
                            {7,1,3,9,2,4,8,5,6},
                            {9,6,1,5,3,7,2,8,4},
                            {2,8,7,4,1,9,6,3,5},
                            {3,4,5,2,8,6,1,7,9}
                            };

    validateSudoku(testGrid);
    getUserInput();
    validateSudoku(sgrid);
}
