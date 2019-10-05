#include <stdio.h>
#include <math.h>

#define M 4
#define N1 1
#define M1 3
#define N 7

void read_m(float mas[M][N], int m, int n);
void prepare(float mas[M][N], int m, int n);
void print_task(float mas[M][N], int m, int n);
void read_cb(int mas_cb[M1][N1], int m, int n);
float scalar(float mas[M][N], int mas_cb[M1][N1], int c);
int delta(float mas[M][N], int mas_cb[M1][N1], int n);
int key_element(float mas[M][N], int n, int max_col);
void change(float mas[M][N], float mas2[M][N], int m, int n, int r, int k);

int main(){
	float mas[M][N], mas2[M][N];
	float coeff[N - 1] = {0, 8, 0, 7, 0, 1};
	int n_bas[M - 1] = {0, 2, 4};
	int mas_cb[M1][N1];
	int max_col, min_row;
	prepare(mas, M, N);
	read_m(mas, M, N);
	print_task(mas, M, N);
	read_cb(mas_cb, M1, N1);

	max_col = delta(mas, mas_cb, N);
	printf("max_col = %d\n", max_col);
	min_row = key_element(mas, N, max_col);
	n_bas[min_row] = max_col;
	printf("min_row = %d\n", min_row);
	change(mas, mas2, M, N, min_row, max_col);

	print_task(mas, M, N);
	printf("Базис: %dx %dx %dx\n", n_bas[0] + 1, n_bas[1] + 1, n_bas[2] + 1);
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
		x += mas[i][c] * mas_cb[i][0];
	}
	return x;
}

int delta(float mas[M][N], int mas_cb[M1][N1], int n){
	float s, max = 1e-6;
	int k = 0, max_col;
	for (int j = 0; j < N - 1; j++){
		s = scalar(mas, mas_cb, j) - mas[M-1][j];
		if (fabs(s) > max){
			max = fabs(s);
			max_col = j;
		}
		if (s < 0){
			k++;
		} 
	}
	// end check
	if (k == N - 1){	
		print_task(mas, M, N);
	}
	return max_col;
}

int key_element(float mas[M][N], int n, int max_col){
	float s, min = 1e6;
	int min_row;
	for (int i = 0; i < M - 1; i++){
		s = mas[i][N-1] / mas[i][max_col];
		if (s < min){
			min = s;
			min_row = i;
		}
	}
	return min_row;
}

void change(float mas[M][N], float mas2[M][N], int m, int n, int r, int k){
	for (int i = 0; i < m - 1; i++){
		for (int j = 0; j < n; j++){
			if (i == r){
				mas2[i][j] = mas[r][j] / mas[r][k];
				mas2[i][N - 1] = mas[r][N-1] / mas[r][k];
			}
			else{
				mas2[i][j] = mas[i][j] - (mas[r][j] / mas[r][k]) * mas[i][k];
				mas2[i][N - 1] = mas[i][N - 1] - (mas[r][N - 1] / mas[r][k]) * mas[i][k];
			} 
	
		}
	}
	for (int i = 0; i < m - 1 ; i++){
		for (int j = 0; j < n; j++){
			mas[i][j] = mas2[i][j];
		}
	}
}
