/*--------------------------------------------------------------*
                 TableCurve C Code Output
         To modify generated output, edit C.TCL
 *--------------------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define A 2
#define B 9
#define E 1e-3
#define DELTA 1e-4
#define TAU 1.6180339898954989

double func(double x);
void dih(double a, double b, double e, double delta);
void golden_cut(double a, double b, double e);
void fib(double a, double b, double e);

void main()
{
 // double x,y;
  //char str[80];
 /* while(1){
    printf("Enter x: ");
    fgets(str, 80, stdin);
    if(!*str) break;
    sscanf(str,"%lg",&x);
    y=func(x);
    printf("      y=%.15lg\n", y);
    }*/
  dih(A, B, E, DELTA); 
  golden_cut(A, B, E);
  fib(A, B, E);
}
 

/*--------------------------------------------------------------*/
double func(double x)
/*--------------------------------------------------------------*
   TableCurve Function: G:\\Lab1\\Andreev\\1.c Oct 14, 2019 9:23:06 AM 
   G:\\Lab1\\Andreev\\dan.txt 
   X=  
   Y=  
   Eqn# 6726  y=a+bx^2+cx^4+dx^6+ex^8+fx^(10)+gx^(12)+hx^(14) 
   r2=0.9999945833983647 
   r2adj=0.9999566671869173 
   StdErr=0.01520383122806203 
   Fstat=26373.80015631564 
   a= 7.109166870372088 
   b= -1.166251457154598 
   c= 0.1115184436418672 
   d= -0.005706215991369096 
   e= 0.0001583607783355519 
   f= -2.365219422087485E-06 
   g= 1.787233437054821E-08 
   h= -5.347670439943148E-11 
 *--------------------------------------------------------------*/
{
  double y;
  x=x*x;
  y=7.109166870372088+x*(-1.166251457154598+
    x*(0.1115184436418672+x*(-0.005706215991369096+
    x*(0.0001583607783355519+x*(-2.365219422087485E-06+
    x*(1.787233437054821E-08+x*-5.347670439943148E-11))))));
  return(y);
}
 
void dih(double a, double b, double e, double delta){
  double u1, u2, f1, f2, x, y;
  int i = 0;
  while (fabs(b - a) > e){
    i++;
    u1 = (a + b - delta) / (double)2;
    u2 = a + b - u1;
    f1 = func(u1);
    f2 = func(u2);
    if (f1 < f2){
      b = u2;
    }
    else if (f1 > f2){
      a = u1;
    }
    else{
      a = u1;
      b = u2;
    }
    x = (b + a) / (double)2;
    y = func(x);
  }
  printf("Метод дихотомии: f(min) = %lf, x = %lf, количество итераций : %d\n", y, x, i);
} 

void golden_cut(double a, double b, double e){
  double u1, u2, f1, f2, x, y;
  int i = 0;
  while (fabs(b - a) > e){
    i++;
    u1 = a + (3 - sqrt(5)) / 2 * (b - a);
    u2 = a + b - u1;
    f1 = func(u1);
    f2 = func(u2);
    if (f1 <= f2){
      b = u2;  
    }
    else{
      a = u1;
    }
  }
  x = (a + b) / (double)2;
  y = func(x);
  printf("Метод золотого сечения: f(min) = %lf, x = %lf, количество итераций : %d\n", y, x, i);
}

void fib(double a, double b, double e){
  double u1, u2, f1, f2, x, y;
  int i = 0, f_n = 1, f_1n = 1, f_2n = 2;
  while (fabs(b - a) > e){
    i++;
    u1 = a + (double)f_n / f_2n * (b - a);
    u2 = a + (double)f_1n / f_2n * (b - a);
    f_n = f_1n;
    f_1n = f_2n;
    f_2n = f_n + f_1n;
    f1 = func(u1);
    f2 = func(u2);
    if (f1 <= f2){
      b = u2;  
    }
    else{
      a = u1;
    }
  }
  x = (a + b) / (double)2;
  y = func(x);
  printf("Метод Фибоначчи: f(min) = %lf, x = %lf, количество итераций : %d\n", y, x, i);
}