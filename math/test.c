#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <math.h>
#define PI 3.14159265

int gaussian_length = 0;
double * gaussian = NULL;

void generateGaussianArray(int n) {
    srand(time(NULL));
    gaussian_length = n;
    gaussian = (double*)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i += 2) {
        double u1 = (double)rand() / RAND_MAX;
        double u2 = (double)rand() / RAND_MAX;
        
        double z1 = sqrt(-2 * log(u1)) * cos(2 * PI * u2);
        double z2 = sqrt(-2 * log(u1)) * sin(2 * PI * u2);
        
        gaussian[i] = z1;
        if (i + 1 < n) {
            gaussian[i + 1] = z2;
        }
    }
}




double RandnZeroDim(int updateCache, int n){
    if(updateCache){
        generateGaussianArray(n);
    }

    double randNumber = (double)rand() / RAND_MAX;
    int randPos = round(randNumber * gaussian_length);
    return gaussian[randPos];
}

double * RandnOneDim(int x, int updateCache, int n){
    if(updateCache){
        generateGaussianArray(n);
    }

    double * arr = (double*)malloc(sizeof(double) * x);
    for(int i = 0; i < x; i++){
        arr[i] = RandnZeroDim(updateCache = 0, n = -1);
    }

    return arr;
}

double ** RandomTwoDim(int x, int y, int updateCache, int n){
    if(updateCache){
        generateGaussianArray(n);
    }

    double ** arr = (double **)malloc(sizeof(double*) * y);
    for(int i = 0; i < y; i++){
        arr[i] = RandnOneDim(x, updateCache = 0, n = -1);
    }

    return arr;
}

int main() {
    int n = 10;
    double * arr = RandnOneDim(n, 1, 320);
    if (arr != NULL) {
        for (int i = 0; i < n; i++) {
            printf("%f\n", arr[i]);
        }
        free(arr);
    }
    return 0;
}
