#include <stdio.h>
#include <stdlib.h>
#include "../dataframe/Dataframe.h"


#define ROWS 70000
#define COLS 785

/**
 * The main entry point of the program.
 * 
 * This function reads a CSV file into a Dataframe, then prints the first 20 rows of the dataframe.
 * 
 * Parameters: None
 * 
 * Returns: An integer indicating the program's exit status (0 for success).
 */
int main() {
    int rows = 70000;
    int cols = 794;
    Dataframe * df = read_csv("data.csv", rows, cols, 784, 10);

    for(int i=0; i<20; i++){
        printf("%d ", i);
        for(int j = 0; j < 10; j++){
            printf("%llf ", df->y[i]->arr[j][0]);
        }
        printf("\n");
    }

    return 0;
}
