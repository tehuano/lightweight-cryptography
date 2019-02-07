#include <stdio.h>
#include <stdlib.h>
#define _N 5

void compute_md(int **A, int **B, int M, int N);
void print_matrix(int **A, int M, int N);
int **create_matrix(int M, int N);
void free_matrix(int **A, int M);

int main() {
    /*
        {{1,1,1,1,1},
        {1,1,0,1,1},
	{1,1,0,0,0},
	{1,1,0,1,0},
	{0,0,1,0,0}};
    */
    int **Md;
    int **M;
    M = create_matrix(_N,_N);
    Md = create_matrix(_N,_N);

    M[0][0] = 1; M[0][1] = 1; M[0][2] = 1; M[0][3] = 1; M[0][4] = 1;
    M[1][0] = 1; M[1][1] = 1; M[1][2] = 0; M[1][3] = 1; M[1][4] = 1;
    M[2][0] = 1; M[2][1] = 1; M[2][2] = 0; M[2][3] = 0; M[2][4] = 0;
    M[3][0] = 1; M[3][1] = 1; M[3][2] = 0; M[3][3] = 1; M[3][4] = 0;
    M[4][0] = 0; M[4][1] = 0; M[4][2] = 1; M[4][3] = 0; M[4][4] = 0;

    compute_md(M,Md,_N,_N);
    printf("M:\n");
    print_matrix(M,_N,_N);
    printf("Md:\n");
    print_matrix(Md,_N,_N);

    free_matrix(Md,_N);
    free_matrix(M,_N);

    return 0;
}

void free_matrix(int **A, int M) {
    int i;
    for (i = 0; i < M; i++) {
        free(A[i]);
    }
    free(A);
}

int ** create_matrix(int m, int n) {
    int **M;
    int i;
    M = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
    }
    return M;
}

void compute_md(int **Mo, int **Md, int M, int N) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
	    Md[i][j] = Mo[i][j] - 1;
	}
    }
}

void print_matrix(int **A, int M, int N) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
	    printf("%d\t", A[i][j]);
	}
	printf("\n");
    }
}

