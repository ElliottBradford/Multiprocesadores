//Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 6

//Functions declaration
void row_matrix_multiplication(int i, int m, int n, int p, double A[m*n], double B[n*p], double C[m*p]);
void write_file(FILE* fptr, int m, int p, double A[m*p]);

int main(){
	//Program variables
	omp_set_num_threads(NUM_THREADS);
	FILE* fptr;
	fptr = fopen("matrix_result.txt", "w");
	double t1, t2, time;
	int m, n, p;
	m = 100;
	n = 100;
	p = 100;
	double A[m*n], B[n*p], C[m*p];
	//Matrix values
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
	//Matrix multiplication
	t1 = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m; i++)
			row_matrix_multiplication(i, m, n, p, A, B, C);
		
	}
	t2 = omp_get_wtime();
	time = t2 - t1;
	printf("Time = %f\n",time);
	write_file(fptr, m, p, C);
	fclose(fptr);
	
	return 0;
}

void row_matrix_multiplication(int i, int m, int n, int p, double A[m*n], double B[n*p], double C[m*p]){
	for(int j = 0; j < p; j+=2){
		C[(i*p)+j] = 0;
		C[(i*p)+j+1] = 0;
		for(int k = 0; k < n; k++){
			C[(i*p)+j] += (A[(i*n)+k]*B[(k*p)+j]);
			C[(i*p)+j+1] += (A[(i*n)+k]*B[(k*p)+j+1]);
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
