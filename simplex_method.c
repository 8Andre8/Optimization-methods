#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M 4
#define N1 1
#define M1 3
#define N 7

void read_m(float mas[M][N], int m, int n);
void prepare(float mas[M][N], int m, int n);
void print_task(float mas[M][N], int m, int n);
void read_cb(int mas_cb[M1][N1], int m, int n);
float scalar(float mas[M][N], int mas_cb[M1][N1], int c);
void delta(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1],float coeff[N - 1], int n_bas[M - 1], int m, int n, int *cycle);
void change(float mas[M][N], float mas2[M][N], int m, int n, int r, int k);
void left(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1],float coeff[N - 1], int n_bas[M - 1]);
void right(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1],float coeff[N - 1], int n_bas[M - 1]);

int main(){
	float mas[M][N], mas2[M][N];
	float coeff[N - 1] = {0, 8, 0, 7, 0, 1};
	int n_bas[M - 1] = {0, 2, 4};
	int mas_cb[M1][N1];
	int max_col, min_row, cycle = 1;
	prepare(mas, M, N);
	read_m(mas, M, N);
	printf("\n");
	printf("Исходные условия задачи:\n");
	print_task(mas, M, N);
	read_cb(mas_cb, M1, N1);
	
	while (cycle){
		delta(mas, mas2, mas_cb, coeff, n_bas, M, N, &cycle);
	}
	printf("\n");
	printf("После преобразований :\n");
	print_task(mas, M, N);
	printf("\n");
	printf("Базис: x%d, x%d, x%d\n", n_bas[0] + 1, n_bas[1] + 1, n_bas[2] + 1);
	printf("Коэффициенты базиса: %d, %d, %d\n", mas_cb[0][0], mas_cb[1][0], mas_cb[2][0]);
	printf("F(max) = %.3f\n", mas_cb[0][0] * mas[0][N-1] + mas_cb[1][0] * mas[1][N-1] + mas_cb[2][0] * mas[2][N-1]);
// проверка устойчивости
	left(mas, mas2, mas_cb, coeff, n_bas);
	right(mas, mas2, mas_cb, coeff, n_bas);
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
			if (j != n - 1){
				if (j == n - 2){
					printf("%8.1f%s%d", mas[i][j], "*x", j + 1);
					continue;
				}
			    printf("%8.1f%s%d\t%c", mas[i][j], "*x", j + 1, '+');
			}
			else{
                if (i == m - 1){
                    printf("%s\n", "    =       F");
                    continue;
                }  
			    printf("%5c%8.1f\n", '=', mas[i][j]);
			}
		}
	}
}
// чтение коэффициентов базиса
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

void delta(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1], float coeff[N - 1], int n_bas[M - 1], int m, int n, int *cycle){
	float s, max = 1e-6, min = 1e6;
	int k = 0, max_col, min_row;
	for (int j = 0; j < n - 1; j++){
		s = scalar(mas, mas_cb, j) - mas[M-1][j];
		if (s >= 0){
			k++;
		}
		else{
			if (fabs(s) > max){
			max = fabs(s);
			max_col = j;
			}
		} 
		// конец цикла
		if (k == n - 1){
			*cycle = 0;
			break;
		}
	}
	k = 0;
	max = 1e-6;
	min = 1e6;
	for (int i = 0; i < M - 1; i++){
		if (mas[i][max_col] > 0){
		s = mas[i][N-1] / mas[i][max_col];
		}
		else{
			continue;
		}
		if (s < min){
			min = s;
			min_row = i;
		}
	}
	n_bas[min_row] = max_col;
	mas_cb[min_row][0] = coeff[max_col];
	change(mas, mas2, M, N, min_row, max_col);
}

void change(float mas[M][N], float mas2[M][N], int m, int n, int r, int k){
	for (int i = 0; i < m - 1 ; i++){
		for (int j = 0; j < n; j++){
			mas2[i][j] = mas[i][j];
		}
	}
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

void left(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1],float coeff[N - 1], int n_bas[M - 1]){
	int cycle, k = 0;
	float c, e = 5e-3;
	for (int i = 1; i <= 1000; i++){
		cycle = 1;
		c = mas[0][N - 1]; 
		read_m(mas, M, N);
		mas_cb[0][0] = 0; mas_cb[1][0] = 0; mas_cb[2][0] = 0; 
		n_bas[0] = 0; n_bas[1] = 2; n_bas[2] = 4;
		mas[M - 1][1] = mas[M - 1][1] - e*i;
		while (cycle){
			k++;
			if (k == 1000){
				printf("\n");
				printf("Левая граница устойчивости не найдена (зацикливание)");
				printf("\n");
				exit(0);
			}
			delta(mas, mas2, mas_cb, coeff, n_bas, M, N, &cycle);	
		}
		// проверка изменения оптимального плана
		if (c != mas[0][N - 1]){
			break;
		}
		c = mas[0][N - 1];
		if (i == 1000){
			printf("Смены оптимального плана не произошло\n");	
		}
	}
	printf("\n");
	printf("Смена оптимального плана (левая граница) :\n");
	print_task(mas, M, N);
	printf("\n");
	printf("Базис: x%d, x%d, x%d\n", n_bas[0] + 1, n_bas[1] + 1, n_bas[2] + 1);
	printf("Коэффициенты базиса: %d, %d, %d\n", mas_cb[0][0], mas_cb[1][0], mas_cb[2][0]);
	printf("F(max) = %.3f\n", mas[M - 1][n_bas[0]] * mas[0][N - 1] + mas[M - 1][n_bas[1]] * mas[1][N - 1] + mas[M - 1][n_bas[2]] * mas[2][N - 1]);
	printf("\n");
	printf("Левая граница устойчивости коэффициента с2: %.3f\n", mas[M - 1][1] + e*2);
}

void right(float mas[M][N], float mas2[M][N], int mas_cb[M1][N1],float coeff[N - 1], int n_bas[M - 1]){
	int cycle, k = 0;
	float c, e = 5e-3;
	for (int i = 1; i <= 1000; i++){
		cycle = 1;
		c = mas[0][N - 1];
		read_m(mas, M, N);
		mas_cb[0][0] = 0; mas_cb[1][0] = 0; mas_cb[2][0] = 0; 
		n_bas[0] = 0; n_bas[1] = 2; n_bas[2] = 4;
		mas[M - 1][1] = mas[M - 1][1] + e*i;
		while (cycle){
			k++;
			if (k == 1000){
				printf("\n");
				printf("Правая граница устойчивости не найдена (зацикливание)");
				printf("\n");
				exit(0);
			}
			delta(mas, mas2, mas_cb, coeff, n_bas, M, N, &cycle);	
		}
		// проверка изменения оптимального плана
		if (c != mas[0][N - 1]){
			break;
		}
		c = mas[0][N - 1];
		if (i == 1000){
			printf("Смены оптимального плана не произошло\n");	
		}
	}
	printf("\n");
	printf("Смена оптимального плана (правая граница) :\n");
	print_task(mas, M, N);
	printf("\n");
	printf("Базис: x%d, x%d, x%d\n", n_bas[0] + 1, n_bas[1] + 1, n_bas[2] + 1);
	printf("Коэффициенты базиса: %d, %d, %d\n", mas_cb[0][0], mas_cb[1][0], mas_cb[2][0]);
	printf("F(max) = %.3f\n", mas[M - 1][n_bas[0]] * mas[0][N - 1] + mas[M - 1][n_bas[1]] * mas[1][N - 1] + mas[M - 1][n_bas[2]] * mas[2][N - 1]);
	printf("\n");
	printf("Правая граница устойчивости коэффициента с2: %.6f\n", mas[M - 1][1] - e*2);
}
//
