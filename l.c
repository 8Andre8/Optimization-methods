#include <stdio.h>

#define M 4
#define N1 1
#define M1 3
#define N 7

void read_m(float mas[M][N], int m, int n);
void prepare(float mas[M][N], int m, int n);
void print_task(float mas[M][N], int m, int n);
void read_cb(int mas_cb[M1][N1], int m, int n);
float scalar(float mas[M][N], int mas_cb[M1][N1], int c);

int main(){
	float mas[M][N];
	int mas_cb[M1][N1];
	prepare(mas, M, N);
	read_m(mas, M, N);
	print_task(mas, M, N);
	read_cb(mas_cb, M1, N1);
	float z = 0; 
	z = scalar(mas, mas_cb, 1);
	printf("%f", z);
}

void prepare(float mas[M][N], int m, int n){
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			mas[i][j] = 0;
		}
	}
}

void read_m(float mas[M][N], int m, int n){
	char file[] = "matrix.txt";
	FILE *p;
	p = fopen(file, "r");
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			fscanf(p, "%f", &mas[i][j]);
		}
	}
	fclose(p);
}

void print_task(float mas[M][N], int m, int n){
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			if (j != N - 1){
			    printf("%8.1f%s%d\t%c", mas[i][j], "*x", j+1, '+');
			}
			else{
                if (i == m - 1){
                    printf("%8s\n", "=  F");
                    continue;
                }  
			    printf("%5c\t%-8.1f\n", '=', mas[i][j]);
			}
		}
	}
}

void read_cb(int mas_cb[M1][N1], int m, int n){
	char file[] = "cb.txt";
	FILE *p = fopen(file, "r");
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			fscanf(p, "%d", &mas_cb[i][j]);
		}
	}
	fclose(p);
}

float scalar(float mas[M][N], int mas_cb[M1][N1], int c){
	float x = 0;
	for (int i = 0; i < 3; i++){
		x += mas[i][c] * mas_cb[i-1][1];
	}
	return(x);
}
