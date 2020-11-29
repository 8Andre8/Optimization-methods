#include <stdio.h>
#include <math.h>

#define T 1e-9
#define H 0.01
#define EPS 1e-4
double func(double x1, double x2);
void grad(double x1, double x2, double t, double *f_x1, double *f_x2);
void vekt_s(double f_x1, double f_x2, double *s1, double *s2);
int sign(double f_x1, double f_x2);
void perm(double x1, double x2, double eps, double h);
void step(double x1, double x2, double eps);
void mono(double x1, double x2, double eps);
void opt(double x1, double x2, double eps);

void main(){
    perm(5, 5, EPS, H);
    step(5, 5, EPS);
    mono(5, 5, EPS);
    opt(5, 5, EPS);
}
double func(double x1, double x2){ 
    return 3 * pow(x1 + 5, 2) + 3 * pow(x2 - 3, 2) + 3 * x1 * x2;
}

void grad(double x1, double x2, double t, double *f_x1, double *f_x2){
    *f_x1 = (func(x1 + t, x2) - func(x1, x2)) / t;
    *f_x2 = (func(x1, x2 + t) - func(x1, x2)) / t;
}

void vekt_s(double f_x1, double f_x2, double *s1, double *s2){
    double norm;
    norm = sqrt(f_x1 * f_x1 + f_x2 * f_x2);
    *s1 = -f_x1 / norm;
    *s2 = -f_x2 / norm; 
}

int sign(double f_x1, double f_x2){
    if ((f_x1 < 0) && (f_x2 < 0)){
        return -1;
    }
    else{
        return 1;
    }
}

double h_opt(double f_x1, double f_x2, double s1, double s2){
    return -(f_x1 * s1 + f_x2 * s2) / (s1 * (6 * s1 + 3 * s2) + s2 * (3 * s1 + 6 * s2));
}

void perm(double x1, double x2, double eps, double h){
    double L = 1e6, x1_, x2_, s1, s2, f_x1, f_x2, x2_next, x1_next;
    int i = 0;
    x1_ = x1;
    x2_ = x2;
    while(L > eps){
        grad(x1_, x2_, T, &f_x1, &f_x2);
        vekt_s(f_x1, f_x2, &s1, &s2);
        x1_next = x1_ + h * s1;
        x2_next = x2_ + h * s2;
        L = fabs(func(x1_, x2_) - func(x1_next, x2_next));
        x1_ = x1_next;
        x2_ = x2_next;
        i++;
    }
    printf("Градиентный метод с постоянным шагом :");
    printf("\nf = %lf, x1 = %lf, x2 = %lf, число шагов : %d\n", func(x1_, x2_), x1_, x2_, i);
}

void step(double x1, double x2, double eps){
    double L = 1e6, x1_, x2_, s1, s2, f_x1, f_x2, x2_next, x1_next, h;
    int k = 1, i = 0;
    h = 0.1;
    x1_ = x1;
    x2_ = x2;
    while(L > eps){
        grad(x1_, x2_, T, &f_x1, &f_x2);
        vekt_s(f_x1, f_x2, &s1, &s2);
        if (sign(f_x1, f_x2) != k){
            h = h / 5;
        }
        k = sign(f_x1, f_x2);
        x1_next = x1_ + h * s1;
        x2_next = x2_ + h * s2;
        L = fabs(func(x1_, x2_) - func(x1_next, x2_next));
        x1_ = x1_next;
        x2_ = x2_next;
        i++;
    }
    printf("\nГрадиентный метод со ступенчатым шагом :");    
    printf("\nf = %lf, x1 = %lf, x2 = %lf, число шагов : %d\n", func(x1_, x2_), x1_, x2_, i);
}

void mono(double x1, double x2, double eps){
    double L = 1e6, x1_, x2_, s1, s2, f_x1, f_x2, x2_next, x1_next, alfa = 0.8, h;
    int k = 0, i = 0;
    h = 1 / (1 + pow(k, alfa));    
    x1_ = x1;
    x2_ = x2;
    while(L > eps){
        grad(x1_, x2_, T, &f_x1, &f_x2);
        vekt_s(f_x1, f_x2, &s1, &s2);
        x1_next = x1_ + h * s1;
        x2_next = x2_ + h * s2;
        L = fabs(func(x1_, x2_) - func(x1_next, x2_next));
        x1_ = x1_next;
        x2_ = x2_next;
        k++;
        h = 1 / (1 + pow(k, alfa));
        i++;
    } 
    printf("\nГрадиентный метод с монотонно убывающим шагом :");   
    printf("\nf = %lf, x1 = %lf, x2 = %lf, число шагов : %d\n", func(x1_, x2_), x1_, x2_, i);
}

void opt(double x1, double x2, double eps){
    double L = 1e6, x1_, x2_, s1, s2, f_x1, f_x2, x2_next, x1_next, h; 
    int i = 0;
    x1_ = x1;
    x2_ = x2;
    while(L > eps){
        grad(x1_, x2_, T, &f_x1, &f_x2);
        vekt_s(f_x1, f_x2, &s1, &s2);
        h = h_opt(f_x1, f_x2, s1, s2);
        x1_next = x1_ + h * s1;
        x2_next = x2_ + h * s2;
        L = fabs(func(x1_, x2_) - func(x1_next, x2_next));
        x1_ = x1_next;
        x2_ = x2_next;
        i++;
    }
    printf("\nГрадиентный метод с оптимальным шагом :");
    printf("\nf = %lf, x1 = %lf, x2 = %lf, число шагов : %d\n", func(x1_, x2_), x1_, x2_, i);
}
