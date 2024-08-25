#include<stdlib.h>
#include<stdio.h>
#include <math.h>

//2D matrix
typedef struct Matrix{
    int m;
    int n;
    double ** arr;
}Matrix;

/**
 * Prints the matrix to the standard output.
 * @param A A pointer to the matrix to be printed.
 */
void print_matrix(Matrix * A){
    printf("\n");
    for(int i = 0; i < A->m; i++){
        printf("| ");
        for(int j = 0; j < A->n; j++){
            printf("%lf ", A->arr[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}


/**
 * Creates a new matrix in memory.
 *
 * The created matrix has the provided number of rows and columns.
 * The matrix->arr is equal to NULL.
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 * @return A pointer to the newly created matrix.
 */
Matrix * create_matrix(int m, int n){
    Matrix * matrix = (Matrix*)malloc(sizeof(Matrix));

    matrix->n = n;
    matrix->m = m;
    matrix->arr = NULL;

    return matrix;
}


/**
 * Initializes the matrix in-place.
 *
 * This function doesn't change the value of matrix->arr.
 * It's used to initialize the matrix with the provided number of rows and columns.
 * @param matrix A pointer to the matrix to be initialized.
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 */
void initialize_matrix(Matrix* matrix, int m, int n){
    matrix->n = n;
    matrix->m = m;
}

/**
 * Frees the memory of the matrix.
 *
 * If onlyValues is not 0, the memory of the matrix itself is not freed.
 * This is used when the matrix is stored in an array of matrices as values.
 * @param matrix The matrix to free.
 * @param onlyValues If not 0, the matrix itself is not freed.
 */
void free_matrix(Matrix * matrix, int onlyValues){
    if(matrix->arr != NULL){
        // Free the memory of the matrix elements
        for(int i = 0; i < matrix->m; i++){
            free(matrix->arr[i]);
            matrix->arr[i] = NULL;
        }
        // Free the memory of the matrix array
        free(matrix->arr);
        matrix->arr = NULL;
    }
    if(!onlyValues){
        // Free the memory of the matrix itself
        free(matrix);
    }
}


/**
 * Makes a copy of an existing matrix.
 *
 * This function creates a new matrix and copies the values of the old matrix into the new one.
 * @param old The matrix to be copied.
 * @return A new matrix with the same values as the old one.
 */
Matrix * copy_matrix(Matrix * old){
    Matrix * new = create_matrix(old->m, old->n);
    new->arr= (double **)malloc(sizeof(double) * new->m);
    for(int i = 0; i < new->m; i++){
        new->arr[i] = (double*)malloc(sizeof(double) * new->n);
        for(int j = 0; j < new->n; j++){
            new->arr[i][j] = old->arr[i][j];
        }
    }
    return new;
}


/**
 * Creates a matrix of zeros with the specified dimensions.
 *
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 * @return A new matrix filled with zeros.
 */
Matrix * zeros(int m, int n){
    Matrix * matrix = (Matrix*)malloc(sizeof(Matrix));

    matrix->n = n;
    matrix->m = m;

    matrix->arr = (double**)malloc(sizeof(double) * m);
    for(int i = 0; i < m; i++){
        matrix->arr[i] = (double*)malloc(sizeof(double) * n);
        for(int j = 0; j < n; j++){
            matrix->arr[i][j] = 0.0;
        }
    }

    return matrix;
}

     



/**
 * Multiply matrices A and B in-place and store the result in matrix C.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The matrix where the result will be stored.
 */
void dot_product_inplace(Matrix * A, Matrix * B, Matrix * C){
    // Iterate over the rows of A and the columns of B
    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < B->n; j++){
            // Compute the dot product of the i-th row of A and the j-th column of B
            C->arr[i][j] = 0.0;
            for(int k = 0; k < A->n; k++){
                C->arr[i][j] += A->arr[i][k] * B->arr[k][j];
            }
        }
    }
}



/**
 * Multiply matrices A and B. Returns the result as a new matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix multiplication as a new matrix.
 */
Matrix * dot_product(Matrix * A, Matrix *B){
    Matrix * C = zeros(A->m, B->n);

    // Compute the dot product of the matrices A and B and store the result in matrix C
    dot_product_inplace(A, B, C);

    return C;
}

/**
 * Adds seconds matrix to the first.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 */
void matrix_increase_by(Matrix * A, Matrix *B){
    int i, j;
    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            A->arr[i][j] += B->arr[i][j];
        }
    }
}



/**
 * Returns new matrix C as the sum of matrices A and B.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix addition as a new matrix.
 */
Matrix * matrix_add(Matrix * A, Matrix * B){
    Matrix * C = zeros(A->m, A->n);

    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            C->arr[i][j] = A->arr[i][j] + B->arr[i][j];
        }
    }
}


/**
 * Returns difference(A-B) of two matrices as a new matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix subtraction as a new matrix.
 */
Matrix * matrix_dif(Matrix * A, Matrix * B){
    Matrix * C = zeros(A->m, A->n);
    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            C->arr[i][j] = A->arr[i][j] - B->arr[i][j];
        }
    }
    
    return C;
}

/**
 * Computes the Hadamard product (element-wise product) of two matrices
 * and stores the result in the first matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 */
void hadamard_product_inplace(Matrix * A, Matrix * B){
    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            A->arr[i][j] *= B->arr[i][j];
        }
    }
}


/**
 * Transposes the matrix in-place and returns the result.
 *
 * @param A The matrix to be transposed.
 * @return The transposed matrix.
 */
Matrix * inplace_transpose(Matrix * A){
    Matrix * result = (Matrix *)malloc(sizeof(Matrix));
    result->m = A->n;
    result->n = A->m;
    
    // Create a 2D array with the same size as the matrix
    result->arr = (double **)malloc(result->m * sizeof(double *));
    
    for (int i = 0; i < result->m; i++) {
        result->arr[i] = (double *)malloc(result->n * sizeof(double));
    }
    
    // Perform the transpose operation
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            result->arr[j][i] = A->arr[i][j];
        }
    }
    
    // Free the memory of the original matrix
    free_matrix(A, 0);
    
    return result;
}


/**
 * Creates a new matrix which is the transpose of the given matrix.
 *
 * @param A The matrix to be transposed.
 * @return A new matrix which is the transpose of the given matrix.
 */
Matrix * transpose(Matrix * A){
    Matrix * result = (Matrix *)malloc(sizeof(Matrix));
    result->m = A->n;
    result->n = A->m;
    
    // Create a 2D array with the same size as the matrix
    result->arr = (double **)malloc(result->m * sizeof(double *));
    
    for (int i = 0; i < result->m; i++) {
        result->arr[i] = (double *)malloc(result->n * sizeof(double));
    }
    
    // Perform the transpose operation
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            // Swap the indices of the elements to get the transpose
            result->arr[j][i] = A->arr[i][j];
        }
    }
    
    return result;
}

