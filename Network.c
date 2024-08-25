#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "./math/Random.h"
#include "./math/Sigmoid.h"
#include "./math/Matrix.h"
#include "./dataframe/dataframe.h"

typedef struct Network{
    int num_layers;
    int * sizes;
    Matrix * biases;
    Matrix * weights;
}Network;

Network * create_network(int num_layers, int * sizes){
    Network * network = (Network*)malloc(sizeof(Network));
    network->num_layers = num_layers;
    network->sizes = (int*)malloc(sizeof(int) * num_layers);
    for(int i = 0; i < num_layers; i++){
        network->sizes[i] = sizes[i];
    }

    network->biases = (Matrix *)malloc(sizeof(Matrix) * (num_layers-1));
    network->weights = (Matrix *)malloc(sizeof(Matrix) * (num_layers-1));


    //Initialize matrices of bias
    for(int i = 0; i < (num_layers-1); i++){
        int m = network->sizes[i+1];
        int n = 1;
        
        initialize_matrix(&(network->biases[i]), m, n);
        network->biases[i].arr = RandomTwoDim(m, n);
    }

    
    
    //Initialize matrices of weights
    for(int i = 0; i < (num_layers-1); i++){
        int m = network->sizes[i+1];
        int n = network->sizes[i];
        
        initialize_matrix(&(network->weights[i]), m, n);
        network->weights[i].arr = RandomTwoDim(m, n);
    }


    return network;
}


Matrix * feed_forward(Network * network, Matrix * input, Matrix ** activations, Matrix ** zs){
    Matrix * a = copy_matrix(input);

    for(int i = 0; i < network->num_layers-1; i++){
        Matrix * tmp = dot_product(&(network->weights[i]), a);
        matrix_increase_by(tmp, &(network->biases[i]));
        if(activations == NULL){
            free_matrix(a, 0);
        }
        else{
            activations[i] = a;
            zs[i] = copy_matrix(tmp);
        }
        a = tmp;
        sigmoid(a);
    }

    if(activations != NULL){
        activations[network->num_layers-1] = a;
    }
    return a;
}

double C(Network * network, Matrix ** X, Matrix ** y, int num_samples){
    double c = 0;
    for(int i = 0; i < num_samples; i++){
        Matrix * res = feed_forward(network, X[i], NULL, NULL);
        Matrix * tmp = matrix_dif(res, y[i]);
        free(res);

        res = tmp;
        Matrix * res_tr = transpose(res);
        Matrix * number = dot_product(res, res_tr);
        free(res);
        free(res_tr);
        free(number);
        c+=number->arr[0][0];
    }
    return c/2;
}



void backprop(Network * network, Matrix * X, Matrix * y, Matrix ** nabla_w, Matrix ** nabla_b){
    for(int i = 0; i < network->num_layers-1; i++){
        nabla_w[i] = zeros(network->weights[i].m, network->weights[i].n);
        nabla_b[i] = zeros(network->biases[i].m, network->biases[i].n);
    }

    Matrix ** activations = (Matrix **)malloc(sizeof(Matrix *) * (network->num_layers));
    Matrix ** zs = (Matrix **)malloc(sizeof(Matrix *) * (network->num_layers));
    feed_forward(network, X, activations, zs);

    // //Estimates delta for last layer
    // //Delta is partial derivative dC/dz = dC/da * da/dz
    // //So, for last layer activations[-1] - y is dc/da as far as C = 1/2(a[-1] - y)^2
    int activation_layer = network->num_layers-1;
    Matrix * delta = matrix_dif(activations[activation_layer], y);
    sigmoid_derivative(zs[activation_layer-1]);
    hadamard_product_inplace(delta, zs[activation_layer-1]);

    free_matrix(nabla_b[network->num_layers - 2], 0);
    nabla_b[network->num_layers - 2] = copy_matrix(delta);
    activations[activation_layer-1] = inplace_transpose(activations[activation_layer-1]);
    free_matrix(nabla_w[network->num_layers - 2], 0);
    nabla_w[network->num_layers - 2] = dot_product(delta, activations[activation_layer-1]);

    for(int i = 2; i < network->num_layers; i++){
        Matrix * transposed_weights = transpose(&(network->weights[network->num_layers - i]));
        Matrix * delta_ = dot_product(transposed_weights, delta);
        free_matrix(transposed_weights, 0);
        free_matrix(delta, 0);
        delta = delta_;

        sigmoid_derivative(zs[network->num_layers - i - 1]);
        hadamard_product_inplace(delta, zs[network->num_layers - i - 1]);

        free_matrix(nabla_b[network->num_layers - 1 - i], 0);
        nabla_b[network->num_layers - i - 1] = copy_matrix(delta);
        activations[activation_layer-i] = inplace_transpose(activations[activation_layer-i]);
        free_matrix(nabla_w[network->num_layers - 1 - i], 0);
        nabla_w[network->num_layers- i - 1] = dot_product(delta, activations[activation_layer-i]);
    }

    free_matrix(delta, 0);

    for(int i = 0; i < (network->num_layers); i++){
        free_matrix(activations[i], 0);
    }

    for(int i = 0; i < (network->num_layers-1); i++){
        free_matrix(zs[i], 0);
    }

    free(activations);
    free(zs);
} 

void update_parameters(Network * network, Matrix ** X, Matrix ** y, int samples_number, double eta){
    Matrix ** nabla_w = (Matrix**)malloc(sizeof(Matrix*) * (network->num_layers - 1));
    Matrix ** nabla_b = (Matrix**)malloc(sizeof(Matrix*) * (network->num_layers - 1));
    for(int i = 0; i < (network->num_layers - 1); i++){
        nabla_w[i] = zeros(network->sizes[i+1], network->sizes[i]);
        nabla_b[i] = zeros(network->sizes[i+1], 1);
    }

    for(int i = 0; i < samples_number; i++){
        //Estimates nabla for certain examples
        Matrix ** nabla_w_local = (Matrix**)malloc(sizeof(Matrix*) * (network->num_layers - 1));
        Matrix ** nabla_b_local = (Matrix**)malloc(sizeof(Matrix*) * (network->num_layers - 1));
        backprop(network, X[i], y[i], nabla_w_local, nabla_b_local);

        for(int j = 0; j < network->num_layers-1; j++){
            matrix_increase_by(nabla_w[j], nabla_w_local[j]);
            matrix_increase_by(nabla_b[j], nabla_b_local[j]);
        }
        

        for(int j = 0; j < network->num_layers-1; j++){
            free_matrix(nabla_w_local[j], 0);
            free_matrix(nabla_b_local[j], 0);
        }
        free(nabla_w_local);
        free(nabla_b_local);
    }


    for(int i = 0; i < network->num_layers - 1; i++){
        for(int j = 0; j < network->weights[i].m; j++){
            for(int k = 0; k < network->weights[i].n; k++){
                network->weights[i].arr[j][k] -= (eta/samples_number) * nabla_w[i]->arr[j][k];
            }
        }
    }

    for(int i = 0; i < network->num_layers - 1; i++){
        for(int j = 0; j < network->biases[i].m; j++){
            for(int k = 0; k < network->biases[i].n; k++){
                network->biases[i].arr[j][k] -= (eta/samples_number) * nabla_b[i]->arr[j][k];
            }
        }
    }

    for(int j = 0; j < network->num_layers-1; j++){
        free_matrix(nabla_w[j], 0);
        free_matrix(nabla_b[j], 0);
    }
    free(nabla_w);
    free(nabla_b);
}




void shuffleArrays(struct Matrix **training_X, struct Matrix **training_y, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        Matrix *temp_X = training_X[j];
        training_X[j] = training_X[i];
        training_X[i] = temp_X;

        Matrix *temp_y = training_y[j];
        training_y[j] = training_y[i];
        training_y[i] = temp_y;
    }
}


void SGD(Network * network, 
        Matrix ** training_X, 
        Matrix ** training_y, 
        int samples_number, 
        int epochs,
        int mini_batch_size,
        int eta)
{
    int c = 0;
    for(int i = 0; i < epochs; i++){

        double before_many = C(network, training_X, training_y, samples_number/10);
        shuffleArrays(training_X, training_y, samples_number);
        for(int j = 0; j < samples_number-mini_batch_size; j+=mini_batch_size){
            Matrix ** batch_X = &(training_X[j]);
            Matrix ** batch_y = &(training_y[j]);
            
            double before = C(network, batch_X, batch_y, mini_batch_size);
            update_parameters(network, batch_X, batch_y, mini_batch_size, eta);
            double after  = C(network, batch_X, batch_y, mini_batch_size);
        }
        
        double after_many = C(network, training_X, training_y, samples_number/10);
        printf("EPOCH %d FINISHED. C(before) = %lf; C(after) = %lf\n",i, before_many, after_many);
    }
}


void evaluate(Network * network, int samples, Matrix ** X, Matrix ** y){
    for(int i = 0; i < samples; i++){
        Matrix * res = feed_forward(network, X[i], NULL, NULL);
        
        for(int j = 0; j < res->m; j++){
            printf("%lf ", res->arr[j][0]);
        }
        printf("\n");
        for(int j = 0; j < y[i]->m; j++){
            printf("%lf ", y[i]->arr[j][0]);
        }
        printf("\n");
        
    }
}


char *create_absolute_path(const char *relative_path) {
    char *executable_path = _pgmptr; // Get executable path using _pgmptr
    char *absolute_path = NULL;

    // Calculate the length of the absolute path
    size_t executable_length = strlen(executable_path);
    size_t relative_length = strlen(relative_path);
    size_t total_length = executable_length + relative_length + 2; // +2 for '/' and '\0'

    // Allocate memory for the absolute path
    absolute_path = malloc(total_length);
    if (absolute_path == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Construct the absolute path
    snprintf(absolute_path, total_length, "%s/%s", executable_path, relative_path);

    printf("%s\n", absolute_path);
    return absolute_path;
}



// Usage example
int main(){

    char *executable_path = _pgmptr;
    printf("Executable path: %s\n", executable_path);
    create_absolute_path("../../mnist/data.csv");

    //freopen("logs.txt", "w", stdout);

    
    generateGaussianArray(65536);
    int sizes[3] = {784,100,10};
    Network * network = create_network(3, sizes);


    int rows = 10000;
    int cols = 794;

    // "./mnist/data.csv" "D:/Z/Programming/_Univeristy/NSU/ML_C/mnist/data.csv"
    // "/mnt/d/Z/programming/_univeristy/nsu/ML_C/mnist/data.csv"
    Dataframe * df = read_csv("D:/Z/Programming/_Univeristy/NSU/ML_C/mnist/data.csv", rows, cols, 784, 10);

    printf("HERE WE GO\n");
    SGD(network, df->X, df->y, rows, 10, 10, 1);
    printf("HERE WE FINISHED\n");

    printf("On train: \n");
    evaluate(network, 10, df->X, df->y);


    for(int i = 0; i < df->num_samples; i++){
        free_matrix(df->X[i], 0);
        free_matrix(df->y[i], 0);
    }
    free(df->X);
    free(df->y);
    free(df);


    for(int i = 0; i < network->num_layers-1; i++){
        free_matrix(&(network->weights[i]), 0);
        free_matrix(&(network->biases[i]), 0);
    }

    free(network->biases);
    free(network->weights);
    free(network->sizes);
    free(network);

    free_gaussian();
}