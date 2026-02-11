#include <cmath>
#include <cstdlib>
#include <iostream>

double *sol_1(int, double *, double *);
double *euler_explicite_1(int, double, double *, double *, double (*phi)(double, double));
double phi(double, double);
using std::cout;

int main() {
    double a = 0;
    double b = 1;
    double u0 = 1;
    int length = 1;
    int n;

    int n_h = 20;
    double h = (double)length/n_h;

    double *u = (double *)calloc(n_h, sizeof(double));
    double *x = (double *)calloc(n_h, sizeof(double));
    for (n = 0;n <= n_h; n++)
        x[n] = a + n*h; 
    u[0] = 1;

    u = euler_explicite_1(n_h,h,u,x,*phi);

    double *u_analytic = (double *)calloc(n_h, sizeof(double));
    u_analytic = sol_1(n_h,u,x);

    cout << "x : " << std::endl;
    for (n = 0;n <= n_h; n++)
        cout << x[n] << std::endl;

    cout << "u avec Euler explicite : " << std::endl;
    for (n = 0;n <= n_h; n++)
        cout << u[n] << std::endl;
    cout << "u avec solution analytique : " << std::endl;
    for (n = 0;n <= n_h; n++)
        cout << u_analytic[n] << std::endl;
    cout << "différences : " << std::endl;
    for (n = 0;n <= n_h; n++)
        cout << u[n]-u_analytic[n] << std::endl;

    return 0;
}

double *euler_explicite_1(int n_h, double h, double *u, double *x, double (*phi)(double, double)) {
    int n;
    for (n = 0; n <= n_h; n++)
        u[n+1] = u[n] + h*phi(x[n],u[n]);
    return u;
}

double *sol_1(int n_h, double *u, double *x) {
    int n;
    for (n = 0; n <= n_h; n++)
        u[n] = exp(x[n]*x[n]);
    return u;
}

double phi(double x, double u) {
    return 2*x*u;
}