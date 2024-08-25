#ifndef MATRIX_HEADER
#define MATRIX_HEADER
#include<stdio.h>
#include<stdlib.h>

//2D matrix
typedef struct Matrix{
    int m;
    int n;
    double ** arr;
}Matrix;

/**
 * Creates a new matrix in memory.
 *
 * The created matrix has the provided number of rows and columns.
 * The matrix->arr is equal to NULL.
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 * @return A pointer to the newly created matrix.
 */
Matrix * create_matrix(int m, int n);

/**
 * Initializes the matrix in-place.
 *
 * This function doesn't change the value of matrix->arr.
 * It's used to initialize the matrix with the provided number of rows and columns.
 * @param matrix A pointer to the matrix to be initialized.
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 */
void initialize_matrix(Matrix* matrix, int m, int n);

/**
 * Frees the memory of the matrix.
 *
 * If onlyValues is not 0, the memory of the matrix itself is not freed.
 * This is used when the matrix is stored in an array of matrices as values.
 * @param matrix The matrix to free.
 * @param onlyValues If not 0, the matrix itself is not freed.
 */
void free_matrix(Matrix * matrix, int onlyValues);

/**
 * Makes a copy of an existing matrix.
 *
 * This function creates a new matrix and copies the values of the old matrix into the new one.
 * @param old The matrix to be copied.
 * @return A new matrix with the same values as the old one.
 */
Matrix * copy_matrix(Matrix * old);

/**
 * Creates a matrix of zeros with the specified dimensions.
 *
 * @param m The number of rows in the matrix.
 * @param n The number of columns in the matrix.
 * @return A new matrix filled with zeros.
 */
Matrix * zeros(int m, int n);

/**
 * Multiply matrices A and B in-place and store the result in matrix C.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The matrix where the result will be stored.
 */
void dot_product_inplace(Matrix * A, Matrix * B, Matrix * C);

/**
 * Multiply matrices A and B. Returns the result as a new matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix multiplication as a new matrix.
 */
Matrix * dot_product(Matrix * A, Matrix *B);

/**
 * Adds seconds matrix to the first.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 */
void matrix_increase_by(Matrix * A, Matrix *B);


/**
 * Returns new matrix C as the sum of matrices A and B.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix addition as a new matrix.
 */
Matrix * matrix_add(Matrix * A, Matrix * B);

/**
 * Returns difference(A-B) of two matrices as a new matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The result of the matrix subtraction as a new matrix.
 */
Matrix * matrix_dif(Matrix * A, Matrix * B);


/**
 * Computes the Hadamard product (element-wise product) of two matrices
 * and stores the result in the first matrix.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 */
void hadamard_product_inplace(Matrix * A, Matrix * B);

/**
 * Transposes the matrix in-place and returns the result.
 *
 * @param A The matrix to be transposed.
 * @return The transposed matrix.
 */
Matrix * inplace_transpose(Matrix * A);

/**
 * Creates a new matrix which is the transpose of the given matrix.
 *
 * @param A The matrix to be transposed.
 * @return A new matrix which is the transpose of the given matrix.
 */
Matrix * transpose(Matrix * A);


/**
 * Prints the matrix to the standard output.
 * @param A A pointer to the matrix to be printed.
 */
void print_matrix(Matrix * A);

#endif



