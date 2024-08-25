#include<math.h>
#include "./Matrix.h"

double sigmoid_numerical(double z){
    return 1.0 / (1.0 + exp(-z));
}
double sigmoid_derivative_numerical(double z){
    return sigmoid_numerical(z) * (1-sigmoid_numerical(z));
}

void sigmoid(Matrix * matrix){
    for(int i = 0; i < matrix->m; i++){
        for(int j = 0; j < matrix->n; j++){
            matrix->arr[i][j] = sigmoid_numerical(matrix->arr[i][j]); 
        }
    }
}


void sigmoid_derivative(Matrix* matrix){
    for(int i = 0; i < matrix->m; i++){
        for(int j = 0; j < matrix->n; j++){
            matrix->arr[i][j] = sigmoid_derivative_numerical(matrix->arr[i][j]);
        }
    }
}