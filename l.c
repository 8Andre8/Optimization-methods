#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define M 4
#define N1 1
#define M1 3
#define N 7

void read_m(float mas[M][N], int m, int n, char file[]);
void prepare(float mas[M][N], int m, int n);
void write_m(float mas[M][N], int m, int n);


int main(){
	char file[] = "matrix.txt";
	float mas[M][N];
	prepare(mas, M, N);
	read_m(mas, M, N, file);
	write_m(mas, M, N);
}

void prepare(float mas[M][N], int m, int n){
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			mas[i][j] = 0;
		}
	}
}

void read_m(float mas[M][N], int m, int n, char file[]){
	FILE *p;
	p = fopen(file, "r");
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			fscanf(p, "%f", &mas[i][j]);
		}
	}
	fclose(p);
}

void write_m(float mas[M][N], int m, int n){
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			if (j != n-1){
			printf("%f%c%d", mas[i][j], 'x', i+1);
			}
			else{ 
			printf("%-10.1f\n", mas[i][j]);
			}
		}
	}
}