#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <math.h>
#include <float.h>
#define PI 3.14159265

int gaussian_length = 0;
double * gaussian = NULL;

void generateGaussianArray(int n) {
    srand(time(NULL));
    gaussian_length = n;
    if(gaussian != NULL){
        free(gaussian);
    }
    gaussian = (double*)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i += 2) {
        double u1, u2, z1, z2;
        
        do {
            u1 = (double)rand() / RAND_MAX;
        } while (u1 <= DBL_EPSILON); // Ensure u1 is not too close to zero
        
        u2 = (double)rand() / RAND_MAX;
        
        z1 = sqrt(-2 * log(u1)) * cos(2 * PI * u2);
        z2 = sqrt(-2 * log(u1)) * sin(2 * PI * u2);
        
        gaussian[i] = z1;
        if (i + 1 < n) {
            gaussian[i + 1] = z2;
        }
    }
}

void free_gaussian(){
    if(gaussian != NULL){
        free(gaussian);
    }
}



double RandnZeroDim(){
    double randNumber = (double)rand() / RAND_MAX;
    int randPos = round(randNumber * gaussian_length);
    if(isnan(gaussian[randPos]) || isinf(gaussian[randPos])){
        return RandnZeroDim();
    }
    return gaussian[randPos];
}

double * RandnOneDim(int n){
    double * arr = (double*)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++){
        arr[i] = RandnZeroDim();
    }

    return arr;
}

double ** RandomTwoDim(int m, int n){
    double ** arr = (double **)malloc(sizeof(double*) * m);
    for(int i = 0; i < m; i++){
        arr[i] = RandnOneDim(n);
    }

    return arr;
}