#include "matrix.h"
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>


void matprint(const double *a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", a[i*n+j]);
        }
        printf("\n");
    }
}

void mattrans(const double *a,  double *b, int m, int n) {
#pragma omp parallel for
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[j*m+i] = a[i*n+j];
        }
    }
}

void matmul(const double *a, const double *b, double *c, int m, int n, int p) {
#pragma omp parallel for
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < p; k++) {
            double temp = 0.0;//can't i just remove this
            for (int j = 0; j < n; j++) {
                temp += a[i * n + j] * b[j * p + k];
            }
            c[i * p + k] = temp;
        }
    }
}
void transmul(const double *B, const double *u, double *w, int m, int n) {
    //for our case only, general no time
#pragma omp parallel for
    for (int j = 0; j < n; j++) {
        w[j] = 0.0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            w[j] += B[i * n + j] * u[i];
        }
    }
}

double frobenius(const double *a, const double *b, int m, int n) {
    double res = 0.0;
#pragma omp parallel for reduction(+:res)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res += pow(a[i*n+j]-b[i*n+j],2);
        }
    }
    return sqrt(res);
}

double dot(const double *a, const double *b, long long n) {
    double s = 0.0;
    #pragma omp parallel for reduction(+:s)
    for (long long i = 0; i < n; i++) {
        s += a[i] * b[i];
    }
    return s;
}

double project(const double *A, const double *u, const double *v, long long m, long long n) {
    // u^T*A*v
    // Actually, can't I remove this?
    double *w = (double *) malloc(m * sizeof(double));
    matmul(A, v, w, m, n, 1);
    double s = dot(u, w, m);
    
    free(w);
    return s;
}

void sumfun(double *A_k, const double *u, const double *v, double s, long long m, long long n) {
#pragma omp parallel for
    for (long long i = 0; i < m; i++) {
        for (long long j = 0; j < n; j++) {
            A_k[i*n + j] += s * u[i] * v[j];
        }
    }
}
