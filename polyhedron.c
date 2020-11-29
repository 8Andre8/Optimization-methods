#include <stdio.h>
#include <math.h>

#define EPS 1e-4
#define ALPHA 1.0
#define BETA 0.5
#define GAMMA 2.0 
#define n  1

double func(double x1, double x2);
void best_and_worst(double x[3][2], double *fl, double *fh, int *min, int *max);
void center_of_gravity(double x[4][2], int max);
void reflection(double x[5][2], int max);
void stretching(double x[6][2], double fl, int min, int max);
void compression(double x[7][2], int min, int max, double fl, double fh);
void reduction(double x[3][2], int min);

void main(){
    double x[7][2];
    double fl, fh, sum, kr = 1e6;
    int min, max;
    x[0][0] =  10;  x[0][1] =  20;
    x[1][0] =  -20;  x[1][1] = 10;
    x[2][0] = -10;  x[2][1] = -10;
  //  do{
      for (int i = 0; i < 100; i++){
        best_and_worst(x, &fl, &fh, &min, &max);
        center_of_gravity(x, max);
        reflection(x, max);
        if (func(x[n + 3][0], x[n + 3][1]) <= fl){
            stretching(x, fl, min, max);
            perror("stretch");
            goto pr;
        }
        else{
            compression(x, min, max, fl, fh);
        }
        pr:
        sum = 0;
        for (int i = 0; i < 3; i++){
            sum += pow(func(x[i][0], x[i][1]) - func(x[n + 2][0], x[n + 2][1]), 2);
        }
        kr = sqrt(sum / 3.0);
        printf("fl = %lf \n", fl);
        printf("fh = %lf \n", fh);
        printf("kr = %lf \n", kr);
      }
    //}while (kr > EPS);
    
    printf("fl = %.3lf, x1 = %.3lf, x2 = %.3lf\n", fl, x[max][0], x[max][1]);
}

double func(double x1, double x2){  
    return 3 * pow(x1 + 5, 2) + 3 * pow(x2 - 3, 2) + 3 * x1 * x2;
}

void center_of_gravity(double x[4][2], int max){
    x[n + 2][0] = 0;
    x[n + 2][1] = 0;
    for (int i = 0; i < 3; i++){
        x[n + 2][0] += x[i][0];
        x[n + 2][1] += x[i][1];
    }
    x[n + 2][0] = (x[n + 2][0] - x[max][0]) / 2.0;
    x[n + 2][1] = (x[n + 2][1] - x[max][1]) / 2.0;
}

void best_and_worst(double x[3][2], double *fl, double *fh, int *min, int *max){
    double f[3];
    *fl = func(x[0][0], x[0][1]);
    *fh = *fl;
    for (int i = 0; i < 3; i++){
        f[i] = func(x[i][0], x[i][1]);
        if (f[i] < *fl){
            *fl = f[i];
            *min = i;
        }
        if (f[i] > *fh){
            *fh = f[i];
            *max = i;
        } 
    }
}

void reflection(double x[5][2], int max){
    x[n + 3][0] = x[n + 2][0] + ALPHA * (x[n + 2][0] - x[max][0]);
    x[n + 3][1] = x[n + 2][1] + ALPHA * (x[n + 2][1] - x[max][1]);
}

void stretching(double x[6][2], double fl, int min, int max){
    double f;
    x[n + 4][0] = x[n + 2][0] + GAMMA * (x[n + 3][0] - x[n + 2][0]);
    x[n + 4][1] = x[n + 2][1] + GAMMA * (x[n + 3][1] - x[n + 2][1]);
    f = func(x[n + 4][0], x[n + 4][1]);
    if (f <= fl){
        x[max][0] = x[n + 4][0];
        x[max][1] = x[n + 4][1];
    }
    else{
        x[max][0] = x[n + 3][0];
        x[max][1] = x[n + 3][1];   
    }
}

void compression(double x[7][2], int min, int max, double fl, double fh){
    x[n + 5][0] = x[n + 2][0] + BETA * (x[max][0] - x[n + 2][0]);
    x[n + 5][1] = x[n + 2][1] + BETA * (x[max][1] - x[n + 2][1]);
    if (func(x[n + 5][0], x[n + 5][1]) < fh){
        x[max][0] = x[n + 5][0];
        x[max][1] = x[n + 5][1];
        perror("comp");
    }
    if (func(x[n + 5][0], x[n + 5][1]) > fh){
        reduction(x, min);
        perror("red");
    }

}

void reduction(double x[3][2], int min){
    for (int i = 0; i < 3; i++){
        if(i != min){
            x[i][0] += 0.5 * (x[i][0] - x[min][0]);
            x[i][1] += 0.5 * (x[i][1] - x[min][1]);
        }
    }
}
