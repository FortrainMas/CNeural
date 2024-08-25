#ifndef RANDOM_HEADER
#define RANDOM_HEADER

void generateGaussianArray(int n);
void free_gaussian();

double RandnZeroDim();
double * RandnOneDim(int n);
double ** RandomTwoDim(int m, int n);

#endif