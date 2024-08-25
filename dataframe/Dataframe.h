#ifndef DATAFRAME_HEADER
#define DATAFRAME_HEADER

#include "../math/Matrix.h"
typedef struct Dataframe{
    int num_samples;
    Matrix ** X;
    Matrix ** y;
}Dataframe;

//Creates new dataframe. 
//It is implied that all dataframes store 2D matrices 
//and all matrices are actually 1D, so X have shape (shape_x,1) and y (shape_y, 1)
Dataframe * create_df(int num_samples, int shape_x, int shape_y);


/// @brief Reads dataframe in csv without column names
/// @param filename path to file
/// @param rows number of rows in csv file
/// @param cols number of columns in csv file
/// @param shape_x number of columns witch should be read in X
/// @param shape_y number of columns witch should be read in y
/// @return Read dataframe
Dataframe * read_csv(char filename[], int rows, int cols, int shape_x, int shape_y);

#endif