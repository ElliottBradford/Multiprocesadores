//Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Program functions
void matrix_multiplication(int m, int n, int p, double A[m*n], double B[n*p], double C[m*p]);
void write_file(FILE* fptr, int m, int p, double A[m*p]);

int main(){
	//Variables declaration
	FILE* fptr;
	fptr = fopen("matrix_result.txt", "w");
	double t1, t2, time;
	int m, n, p;
	m = 100;
	n = 100;
	p = 100;
	double A[m*n], B[n*p], C[m*p];
	//Matrix default values
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			A[(i*n)+j] = (double)j;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < p; j++){
			B[(i*p)+j] = (double)i;
		}
	}
	//Excecute multiplication
	t1 = omp_get_wtime();
	matrix_multiplication(m, n, p, A, B, C);
	t2 = omp_get_wtime();
	time = t2 - t1;
	printf("Time = %f\n",time);
	//Store results
	write_file(fptr, m, p, C);
	fclose(fptr);
	
	return 0;
}

void matrix_multiplication(int m, int n, int p, double A[m*n], double B[n*p], double C[m*p]){
	for(int j = 0; j < p; j+=2){
		for(int i = 0; i < m; i++){
			C[(i*p)+j] = 0;
			C[(i*p)+j+1] = 0;
			for(int k = 0; k < n; k++){
				C[(i*p)+j] += (A[(i*n)+k]*B[(k*p)+j]);
				C[(i*p)+j+1] += (A[(i*n)+k]*B[(k*p)+j+1]);
			}
		}
	}
}

void write_file(FILE* fptr, int m, int p, double A[m*p]){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			fprintf(fptr, "%f ", A[(i*p)+j]);
		}
		fprintf(fptr, "\n");
	}
}
