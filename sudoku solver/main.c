#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int** sudoku_solver(int** matrix, int row,int col);
int** build(int** matrix);
int is_Valid(int** matrix, int row, int col,int num);


int main() {

    int** example = (int**)malloc(9 * sizeof(int*)+1);
    if (example == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < 9; i++) {
        example[i] = (int*)malloc(9 * sizeof(int)+1);
        if (example[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    int initial_values[9][9] = {
    {4, 0, 0, 8, 7, 0, 0, 2, 0},
    {0, 8, 0, 0, 0, 0, 4, 0, 0},
    {0, 0, 6, 3, 0, 0, 8, 0, 1},
    {7, 0, 0, 1, 0, 0, 0, 8, 0},
    {6, 1, 2, 0, 9, 8, 7, 3, 4},
    {0, 0, 0, 0, 6, 0, 0, 1, 9},
    {1, 9, 3, 4, 2, 7, 5, 0, 0},
    {8, 0, 7, 0, 1, 0, 3, 0, 2},
    {0, 2, 0, 0, 0, 3, 0, 0, 0}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            example[i][j] = initial_values[i][j]; 
    // Print the solved Sudoku grid
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", example[i][j]);
        }
        printf("\n");
    }

    int** solved_matrix = build(example);
    printf("-----------------\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", solved_matrix[i][j]);
        }
        printf("\n");
    }


    return 0;


}
int** build(int** matrix) {
    matrix = sudoku_solver(matrix, 0, 0);
    if (matrix != NULL)
        return matrix;
    printf("unable to solve\n");
}


int** sudoku_solver(int** matrix, int row, int col) {
    //system("cls");
    //printf("in soduko_solver row=%d and col=%d", row, col);
    //for (int i = 0; i < 9; i++) {
    //    for (int j = 0; j < 9; j++) {
    //        printf("%d ", matrix[i][j]);
    //    }
    //    printf("\n");
    //}
    if(row==9)
        return matrix;
    if (col == 9)
        return sudoku_solver(matrix, row + 1, 0);
    if (matrix[row][col] != 0)// in case theres already number in it
        if (col == 8)
            return sudoku_solver(matrix, row + 1, 0);
        else
            return sudoku_solver(matrix, row, col + 1);
    for (int i = 1; i <= 9; i++) {
        if (is_Valid(matrix, row, col, i)) {
            matrix[row][col] = i;
            int** temp = sudoku_solver(matrix, row, col + 1);
            if (temp != NULL) {
                return matrix;
            }
            matrix[row][col] = 0;
        }

    }
    return NULL;
} 

int is_Valid(int** matrix, int row, int col,int num) {

    int box_i, box_j;
    for (int i = 0; i < 9; i++) {
        if (i != row && matrix[i][col] == num)
            return 0;
    }
    for (int j = 0; j < 9; j++) {
        if (j != col && matrix[row][j] == num)
            return 0;
    }
    box_i = row/3;
    box_j = col/3;
    for (int i = box_i*3; i < box_i+3; i++) {
        for (int j = box_j*3; j < box_j+3; j++) {
            if (i != row && j != col) {
                if (matrix[i][j] == num)
                    return 0;
            }
        }
    }
    return 1;
}