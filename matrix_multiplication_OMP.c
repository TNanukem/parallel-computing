/* A simple implementation of a Matrix multiplication using OpenMP
   
   The program does the multiplication using the standard serialized
   way and using the OpenMP parallel loop. At the end, the program
   prints the time that was necessary to do the calculation

   Tiago Toledo Jr (a.k.a TNanukem), September of 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1500


int main (void){

	int **A = (int **) malloc(sizeof(int*) * N); 
	int **B = (int **) malloc(sizeof(int*) * N);
	int **C = (int **) malloc(sizeof(int*) * N);

	int i, j, k, nthreads;
	
	// Matrix allocation
	for(i = 0; i < N; i++){
		A[i] = (int *) malloc(sizeof(int) * N);
		B[i] = (int *) malloc(sizeof(int) * N);
		C[i] = (int *) malloc(sizeof(int) * N);
		for(j = 0; j < N; j++){
			A[i][j] = B[i][j] = 1;
			C[i][j] = 0;
		}
	}

	// Parallel implementation
	double start = omp_get_wtime();
	#pragma omp parallel private(k,j)
	{ 
		nthreads = omp_get_num_threads();
		#pragma omp for 
			for(i = 0; i < N; i++){
				for(j = 0; j < N; j++){
					for(k = 0; k < N; k++){
							C[i][j] += A[i][k] * B[k][j];
					}
				}
			}
	}
	
	double time = omp_get_wtime() - start;

	printf("Number of Threads = %d\n", nthreads);
	printf("Parallel Time = %.5f\n", time);


	// Serial implementation
	start = omp_get_wtime();
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			for(k = 0; k < N; k++){
					C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	time = omp_get_wtime() - start;
	printf("Serial Time = %.5f\n", time);

	return 0;
}