#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../c_libs/matrix.h"
#include "../c_libs/image.h"
#include "../c_libs/svd.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <input.img> <output.img> <k>\n", argv[0]);
        return 1;
    }

    char *inp = argv[1];
    int k = atoi(argv[3]);
    char *out = argv[2];

    read_img(inp,"mid.ppm");

    int fmt = (strcmp(out+(strlen(out)-strlen(".png")),".png")==0) ? 1 : 0;

    //TODO get data from image.c directly somehow, don't need a file in the way
    FILE *fp;
    if ((fp = fopen("mid.ppm","r")) == NULL) {
        printf("Could not open intermediate file");
        return 0;
    }

    char temp[20];
    fgets(temp,20,fp);
    fgets(temp,20,fp);
    int x,y;
    fscanf(fp,"%d %d\n",&x,&y);
    fgets(temp,20,fp);
    int *data = (int *) malloc((long long) x*y*3*sizeof(int));
    long long int i = 0;
    while (!feof(fp)) {
        fscanf(fp,"%d",data+(i++));
    }
    fclose(fp);
    if (remove("mid.ppm")) printf("Unable to delete intermediate file");

    long long int dim = (long long) x*y;
    double *A_r = (double *) malloc((long long)dim*sizeof(double));
    double *A_g = (double *) malloc((long long)dim*sizeof(double));
    double *A_b = (double *) malloc((long long)dim*sizeof(double));
    double *A_gr = (double *) malloc((long long)dim*sizeof(double));
    i = 0;
    for (long long int p = 0; p < x; p++) {
        for (long long int q = 0; q < y; q++) {
            A_r[p*y+q] = data[i++];
            A_g[p*y+q] = data[i++];
            A_b[p*y+q] = data[i++];
        }
    }
    free(data);

    // data is now my A matrix.
    // calloc sets to 0 directly. WAAAAHT
    // Should I update my memset code to match?
    double *A_k_r = (double *) calloc((long long)dim,sizeof(double));
    double *A_k_g = (double *) calloc((long long)dim,sizeof(double));
    double *A_k_b = (double *) calloc((long long)dim,sizeof(double));
//    double *A_k_gr = (double *) malloc((long long)dim*sizeof(double));
    // Call Lanczos here, thrice
    // OR WILL I?????
    // MWHAHAHAHA
#pragma omp parallel for
    for (long long p = 0; p < dim; p++) {
        A_gr[p] = 0.299*A_r[p]+0.587*A_g[p]+0.114*A_b[p]; //cleaner to just take grayscale data bruh. but colour img? TODO
    }

    double *U = (double *) malloc(x * k * sizeof(double));
    double *V = (double *) malloc(y * k * sizeof(double));

    power(A_gr,U,V,x,y,k);
    // Now for the hard part. Project u,v onto R,G,B subspaces somehow
    // Why am I even doing so much work. All my imgs are grayscale :(

    for (int p = 0; p < k; p++) {
        double *u = &U[p*x];
        double *v = &V[p*y];
        // cuz project() needs array work
        double s_r = project(A_r, u, v, x, y);
        double s_g = project(A_g, u, v, x, y);
        double s_b = project(A_b, u, v, x, y);

        sumfun(A_k_r, u, v, s_r, x, y);
        sumfun(A_k_g, u, v, s_g, x, y);
        sumfun(A_k_b, u, v, s_b, x, y);
    }
//    power(A_r,A_k_r,x,y,k);
//    power(A_g,A_k_g,x,y,k);
//    power(A_b,A_k_b,x,y,k);
//    int *result = (int *) malloc((long long) x*y*3*sizeof(int)); // my A_k
//    i = 0;
//    for (long long int p = 0; p < x; p++) {
//        for (long long int q = 0; q < y; q++) {
//            double r = A_k_r[p*y+q];
//            double g = A_k_g[p*y+q];
//            double b = A_k_b[p*y+q];
//
//            result[i++] = (r< 0.0) ? 0 : (r> 255.0) ? 255 : (int)r;
//            result[i++] = (g< 0.0) ? 0 : (g> 255.0) ? 255 : (int)g;
//            result[i++] = (b< 0.0) ? 0 : (b> 255.0) ? 255 : (int)b;
//        }
//    }
//
//    FILE *fin;
//    if ((fin = fopen("fin.ppm","w")) == NULL) {
//        printf("Could not open result file");
//        return 0;
//    }
//    fprintf(fin, "P3\n# I desire sleep\n%d %d\n255\n", x, y);
//    int count = 0;
//    for (i = 0; i < x*y*3; i++) {
//        fprintf(fin, "%d", result[i]);
//
//        count++;
//        if (count % 15 == 0 ){
//             fprintf(fin, "\n");
//        } else {
//             fprintf(fin, " ");
//        }
//    }
//    fclose(fin);
//    free(result);

//    write_img("fin.ppm",out,fmt,90);
//    if (remove("fin.ppm")) printf("Unable to delete result file");

    // Yayyy no need to have an intermediate fin.ppm
    write_img(A_k_r,A_k_g,A_k_b,x,y,out,fmt,30);

    printf("Frobenius norms for given image with k = %d are %lf, %lf and %lf\n",k,frobenius(A_r,A_k_r,x,y),frobenius(A_g,A_k_g,x,y),frobenius(A_b,A_k_b,x,y));

    free(A_r);
    free(A_k_r);
    free(A_g);
    free(A_k_g);
    free(A_b);
    free(A_k_b);
    free(A_gr);
    free(U);
    free(V);
    return 0;
}
