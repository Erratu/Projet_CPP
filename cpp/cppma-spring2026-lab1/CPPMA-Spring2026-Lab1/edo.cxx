#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
    float u0 = 1;
    int length = 1;

    int n_h = 100;
    float h = length/100;

    return 0;
}

float *sol_1(float);

float *euler_implicite_1(int, float, float);

float *euler_implicite_1(int nb_it, float h, float *un) {
    *un = 1;
    int n;
    for (n = 0; n <= nb_it; n++)
        *un = *un*(1+h*h*n);
    return un;
}