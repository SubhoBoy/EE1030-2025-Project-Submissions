void matmul(const double *a, const double *b, double *c, int m, int n, int p);
void mattrans(const double *a,  double *b, int m, int n);
void matprint(const double *a, int m, int n);
void transmul(const double *B, const double *u, double *w, int m, int n);
double frobenius(const double *a, const double *b, int m, int n);
double dot(const double *a, const double *b, long long n);
double project(const double *A, const double *u, const double *v, long long m, long long n);
void sumfun(double *A_k, const double *u, const double *v, double s, long long m, long long n);
