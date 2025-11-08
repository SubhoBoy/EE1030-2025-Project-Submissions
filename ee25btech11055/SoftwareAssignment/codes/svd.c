#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include "matrix.h"

double norm(double *v, long long n) {
    double s = 0;
#pragma omp parallel for reduction(+:s)
    for (long long i = 0; i < n; i++) s += v[i] * v[i];
    return sqrt(s);
}

//void trim(double *A, double *u, double *v, double s, long long m, long long n) {
//#pragma omp parallel for
//    for (long long i = 0; i < m; i++)
//        for (long long j = 0; j < n; j++)
//            A[i*n + j] -= s * u[i] * v[j];
//}

void power(double *A, double *U, double *V, long long m, long long n, int k) {
    double *B = malloc(m*n * sizeof(double));
//    double *BT = malloc(m*n * sizeof(double));
    memcpy(B, A, m*n * sizeof(double)); //leave A for Frobenius
//    memset(A_k, 0, m*n * sizeof(double));
    
    double *u = malloc(m * sizeof(double));
    double *v = malloc(n * sizeof(double));
    double *va = malloc(n * sizeof(double)); // prev v
    double *w = malloc(n * sizeof(double));

    srand(time(NULL));
    
    for (int r = 0; r < k; r++) {
        for (long long i = 0; i < n; i++) v[i] = (double)rand()/(double)RAND_MAX; //TODO Check if rand() better
        double nv = norm(v,n);
        for (long long i = 0; i < n; i++) v[i] /= nv;
        
        double nw = 0.0;
        for (int cnt = 0; cnt < 100; cnt++) {
            memcpy(va, v, n * sizeof(double));
            matmul(B,v,u,m,n,1);
            for (int i = 0; i < r; i++) {
                double* u_prev = &U[i * m];
                double du = dot(u, u_prev, m);
#pragma omp parallel for
                for (long long j = 0; j < m; j++) u[j] -= du * u_prev[j]; //clean out components from all prev vectors, fully orthogonal
            }
            double nu = norm(u, m);
            if (nu < 1e-9) break;
            for (long long i = 0; i < m; i++) u[i] /= nu;

            //for (long long i = 0; i < n; i++) w[i] = 0; //do i need a fn to do this
//            memset(w, 0, n * sizeof(double));
//            
//            mattrans(B,BT,m,n);
//            matmul(BT,u,w,n,m,1);

            transmul(B,u,w,m,n);
            for (int i = 0; i < r; i++) {
                double* v_prev = &V[i * n];
                double dv = dot(w, v_prev, n);
#pragma omp parallel for
                for (long long j = 0; j < n; j++) w[j] -= dv * v_prev[j]; //spring cleaningggg
            }
            nw = norm(w, n);
            if (nw < 1e-9) break;
            for (long long i = 0; i < n; i++) v[i] = w[i] / nw;

            double vva = 0.0;
            for (long long i = 0; i < n;i++) vva += v[i] * va[i];
            if (fabs(vva-1.0) < 1e-9) break; //v = va => v^Tva = 1
        }

        memcpy(&U[r*m],u,m*sizeof(double));
        memcpy(&V[r*n],v,n*sizeof(double));
        
//        double s = nw; // is this same as u^TBv?
//        if (fabs(s) < 1e-9) break;
//        
//        for (long long i = 0; i < m; i++)
//            for (long long j = 0; j < n; j++)
//                A_k[i*n + j] += s * u[i] * v[j];
//        
//        trim(B, u, v, s, m, n);
    }
    
    free(B);
    free(u);
    free(v);
    free(va);
    free(w);
}

//int main() {
//    int m = 4, n = 3, k = 2;
//    
//    double A[] = {
//        1, 2, 3,
//        4, 5, 6,
//        7, 8, 9,
//        10, 11, 12
//    };
//    
//    double *A_k = malloc(m*n * sizeof(double));
//    
//    power(A, A_k, m, n, k);
//    
//    printf("Original matrix A:\n");
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%7.2f ", A[i*n + j]);
//        }
//        printf("\n");
//    }
//    
//    printf("\nRank-%d approximation A_k:\n", k);
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%7.2f ", A_k[i*n + j]);
//        }
//        printf("\n");
//    }
//    
//    free(A_k);
//    return 0;
//}
