#include <stdlib.h>
#include <stdio.h>
#include "../math/Matrix.h"

typedef struct Dataframe{
    int num_samples;
    Matrix ** X;
    Matrix ** y;
}Dataframe;

//Creates new dataframe. 
//It is implied that all dataframes store 2D matrices 
//and all matrices are actually 1D, so X have shape (shape_x,1) and y (shape_y, 1)
Dataframe * create_df(int num_samples, int rows, int shape_x, int shape_y){
    Dataframe * df = (Dataframe*)malloc(sizeof(Dataframe));

    df->num_samples = num_samples;
    df->X = (Matrix **)malloc(sizeof(Matrix*) * rows);
    df->y = (Matrix **)malloc(sizeof(Matrix*) * rows);

    for(int i = 0; i < num_samples; i++){
        Matrix * X = zeros(shape_x, 1);
        Matrix * y = zeros(shape_y, 1);

        df->X[i] = X;
        df->y[i] = y;
    }

    return df;
}


/// @brief Reads dataframe in csv without column names
/// @param filename path to file
/// @param rows number of rows in csv file
/// @param cols number of columns in csv file
/// @param shape_x number of columns witch should be read in X
/// @param shape_y number of columns witch should be read in y
/// @return Read dataframe
Dataframe * read_csv(char filename[], int rows, int cols, int shape_x, int shape_y){
    Dataframe * df = create_df(rows, rows, shape_x, shape_y);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }


    double val;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%lf,", &val) != 1) {
                fprintf(stderr, "Error reading file\n");
                return NULL;
            }
            
            if(j < shape_x){
                df->X[i]->arr[j][0] = val;
            }else{
                df->y[i]->arr[j-shape_x][0] = val;
            }
        }
    }

    fclose(file);

    return df;
}