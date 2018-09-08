/* A program that uses the PThreads API to multiply two matrices of size NxN
   Tiago Toledo Junior (a.k.a TNanukem)*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 150

// Definition of the structure type, this will be used to create the thread
typedef struct{
	int r, c;
	int (*A)[N], (*B)[N], (*C)[N]; 

} matrix_type_t;

// The piece of code that each thread will be executing
void *multiply_matrices(void *m){
	int i;
	matrix_type_t *matrix = (matrix_type_t *) m;
	matrix->C[matrix->r][matrix->c] = 0;
	for(i = 0; i < N; i++){
		matrix->C[matrix->r][matrix->c] += matrix->A[matrix->r][i] * matrix->B[i][matrix->c];
	}
}

int main (void){
	
	int i, j;
	pthread_t thread[N*N];
	int A[N][N], B[N][N], C[N][N];
	matrix_type_t *matrix;

	/* Initializing both the matrices with one's. It makes easier to verify if
	the multiplication is right. */
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			A[i][j] = B[i][j] = 1;
		}
	}

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matrix = malloc (sizeof(matrix_type_t));
			matrix->r = i;
			matrix->c = j;
			matrix->A = A; matrix->B = B; matrix->C = C;
			pthread_create(&(thread[i*N + j]),NULL,multiply_matrices, (void *)matrix);
		}
	}
	
	// Waiting to the end of all threads
	for(i = 0; i < N*N; i++){
		pthread_join(thread[i], NULL);	
	}

	return 0;
}