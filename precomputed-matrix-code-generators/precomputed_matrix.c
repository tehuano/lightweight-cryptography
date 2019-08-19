#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 0x01
#define FALSE 0x00

/*
    f (z) = z^163+z^7+z^6+z^3+1
    f (z) = z^233+z^74+1
    f (z) = z^283+z^12+z^7+z^5+1
    f (z) = z^409+z^87+1
    f (z) = z^571+z^10+z^5+z^2+1.
*/

typedef unsigned char uint8;

uint8 compute_trace_element(int gf, int **Trace, uint8 *tracev, uint8 *testv, int mt, int nt, int index);
uint8 **trino_squaring_matrix(int);
uint8 **penta_squaring_matrix(int);
uint8 **new_square_matrix(int );
uint8 **copy_square_matrix(uint8 **, int);
uint8 **producto_matrices_cuadradas(uint8 **, uint8 **, int);
uint8 **allocate_uchar_matrix(int, int);
uint8 *poly_squaring(int );
uint8 **new_matrix_reduccion_trino(uint8 *, int, int, int);
uint8 **new_matrix_reduccion_penta(uint8 *, int, int, int, int, int);
uint8 **squaring_matrix(uint8 **, int, int);
uint8 *new_array(int );
int **allocate_int_matrix(int, int);
int compare(uint8 *, uint8 *, int);
void exp_type1(int field, int split);
void free_uchar_matrix(uint8 **M, int m);
void free_int_matrix(int **M, int m);
void show_square_matrix_downto(uint8 **, int);
void n_squaring(uint8 **, int, int, int);
void inicializar_trino_squaring(int, int *, int *, int *);
void inicializar_penta_squaring(int, int *, int *, int *, int *, int *);
void save_matrix(uint8 **A, int gfield, int exp, int split);

int main(int argc, uint8 *argv[]) {
    uint8 wrong_arguments = TRUE;
    uint8 result = FALSE;
    uint8 name[128];
    int m = 0, n = 0, mt = 0, nt = 0, gf = 0, el = 0;
    int field = 163, i = 0, split = 0;
    int test_number = 0, test_count = 0;
    
    if (argc >= 2) {
        field = atoi(argv[1]);
        printf("Field = %d\n", field);
        if (field == 5 || field == 163 || field == 233 || field == 283 || field == 409 || field == 571) {
            wrong_arguments = FALSE;
        }
		if (argc >= 3) {
            split = atoi(argv[2]);
		}
    }
    if (wrong_arguments) {
        printf("Usage: program 5|163|233|283|409|571 [1|0]\n");
    } else {
        exp_type1(field, split);
    }
    
    return 0;
}

uint8 **trino_squaring_matrix(int gfield) {
   int m,n,k;
   int dlm1;
   uint8 **A;
   uint8 **S;
   uint8 *poly, **redu;
   
   dlm1 = 2*m - 1;
   inicializar_trino_squaring(gfield,&m,&n,&k); 
   poly = poly_squaring(m);
   redu = new_matrix_reduccion_trino(poly,m,n,k);   
   A = squaring_matrix(redu,m,5);    

   return A;
}

uint8 **penta_squaring_matrix(int gfield) {
   int m,n,p,q,r;
   int dlm1;
   uint8 **A;
   uint8 **S;
   uint8 *poly, **redu;
   
   dlm1 = (2*m-1);
   inicializar_penta_squaring(gfield,&m,&n,&p,&q,&r); 
   poly = poly_squaring(m);
   redu = new_matrix_reduccion_penta(poly,m,n,p,q,r);   
   A = squaring_matrix(redu,m,17);
   return A;
}

void save_matrix(uint8 **A, int gfield, int exp, int split) {
    uint8 fname[128];
    int i, j;
    FILE *file = NULL;
    if (1 == split) {
        sprintf(fname,"squaring_matrix_%d_%d.dat",gfield,exp);
        file = fopen(fname,"w");
	} else {
        sprintf(fname,"squaring_matrix_%d.dat",gfield);
        file = fopen(fname,"a");
	}
    for (i = 0; i < gfield; i++) {
        for (j = 0; j < (gfield-1); j++) {
            fprintf(file,"%d,",A[i][j]);
        }
        fprintf(file,"%d\n",A[i][j]);
    }
    fclose (file);
}

void n_squaring(uint8 **A,int gfield, int exp, int split) {
    uint8 **S;
    int i;
    if (exp > 0) {
        S = copy_square_matrix(A,gfield);
        for (i = 1; i < exp; i++) {
            S = producto_matrices_cuadradas(A,S,gfield);  
        }
    } else {
        S = new_square_matrix(gfield);
        int k;
        for(k=0;k<gfield;k++) {
            S[k][k]=1;   
        }
    }
    save_matrix(S,gfield,exp,split);
}

uint8 **squaring_matrix(uint8 **R, int m, int rows) {
   uint8 **A;
   int i,j,x,y;
   A = new_square_matrix(m);

   for(i=0;i<rows;i++) {
       for(j=0;j<m;j++) {                       
          if (R[i][j] > -1) {
              A[j][R[i][j]] = (1+A[j][R[i][j]])%2;
          }
       }      
   }
   return A;
}

uint8 *poly_squaring(int m) {
    int dm1,j,i;
    uint8 *poly;
    dm1 = 2*m-1;
    poly = (uint8 *)calloc(sizeof(uint8),dm1);
    for(i = 1; i < dm1; i+=2) {
       poly[i] = -1;
    }
    j=0; 
    for(i = 0; i < dm1; i+=2) {
        poly[i] = j++;
    }
    return poly;
}

void inicializar_penta_squaring(int gfield,int *m, int *n, int *p, int *q, int *r) {
    if (gfield>1) {
        *m = gfield;
        switch(*m) {
            case 163:*n=7;*p=6;*q=3;*r=0;break;
            case 283:*n=12;*p=7;*q=5;*r=0;break;
            case 571:*n=10;*p=5;*q=2;*r=0;break;
            default:
                printf("ERROR en la entrada\n");exit(0);
        }
    } else {
        printf("ERROR en la entrada\n"); 
        exit(0);     
    }
}

void inicializar_trino_squaring(int gfield,int *m, int *n, int *k) {
   if (gfield>1) {
      *m = gfield;
      switch(*m) {
          case 5:*n=2;*k=0;break;
          case 233:*n=74;*k=0;break;
          case 409:*n=87;*k=0;break;
          default:
                  printf("ERROR en la entrada\n");exit(0);
      }
    } else {
        printf("ERROR en la entrada\n"); 
        exit(0);     
    }
}

uint8 **new_matrix_reduccion_trino(uint8 *poly, int m, int n, int q) {
    uint8 **redu;
    uint8 *potencias;
    int i,j,dm1,k1,k2,desborde,ultimo_usado,row;
    
    dm1 = 2*m-1;  
    potencias = new_array(2);
    redu=allocate_uchar_matrix(5,m); 
    for(i=0;i<5;i++) {
        for(j=0;j<m;j++) {
           redu[i][j] = -1;
        }
    }
    potencias[0] = q;
    potencias[1] = n;
    for(i=0;i<m;i++) {
       redu[0][i] = poly[i];
    }
    for(j=0;j<m-1;j++) {
       redu[1][j] = poly[m+j];
    }  
    for(i=1;i<2;i++) {
        for(k1=potencias[i],k2=0;k1<m;k1++,k2++) {
            redu[2+(i-1)*3][k1] = poly[m+k2];
        }     
        for(j=0;j<2;j++) {
            desborde=potencias[i]-1;
            ultimo_usado=dm1-desborde;
            row=2+(i-1)*3+j+1;
            for(k1=0;k1<desborde;k1++) {
                redu[row][potencias[j]+k1] = poly[ultimo_usado+k1];   
            }
        }
    } 
    return redu;
}

uint8 **new_matrix_reduccion_penta(uint8 *poly, int m, int n, int p, int q, int r) {

    int i,j,dm1,k1,k2,desborde,ultimo_usado,row;
    uint8 **redu;
    uint8 *potencias;
    
    dm1 = 2*m-1;  
    
    potencias = new_array(4);
    redu = allocate_uchar_matrix(17, m); 
    
    for(i = 0; i < 17; i++) {
        for(j = 0; j < m; j++) {
           redu[i][j] = -1;
        }
    }
    
    potencias[0] = r;
    potencias[1] = q;
    potencias[2] = p;
    potencias[3] = n;
    
    for(i=0;i<m;i++) {
       redu[0][i] = poly[i];
    }
    
    for(j=0;j<m-1;j++) {
       redu[1][j] = poly[m+j];
    }  
    
    for(i=1;i<4;i++) {
        for(k1=potencias[i],k2=0;k1<m;k1++,k2++) {
                redu[2+(i-1)*5][k1] = poly[m+k2];             
        }
        for(j=0;j<4;j++) {
            desborde=potencias[i]-1;
            ultimo_usado=dm1-desborde;
            row=2+(i-1)*5+j+1;
            for(k1=0;k1<desborde;k1++) {
                redu[row][potencias[j]+k1] = poly[ultimo_usado+k1];   
            }
        }      
    }

    return redu;
}


uint8 **allocate_uchar_matrix(int m, int n) {
   uint8 **M;
   int i;
   M = (uint8 **)calloc(sizeof(uint8*),m);
   for(i=0;i<m;i++)
       M[i] = (uint8 *)calloc(sizeof(uint8), n);
   return M;
}

int **allocate_int_matrix(int m, int n) {
   int **M;
   int i;
   M = (int **)calloc(sizeof(uint8*),m);
   for(i = 0; i < m; i++)
       M[i] = (int *)calloc(sizeof(int), n);
   return M;
}

void free_int_matrix(int **M, int m) {
    int i;
    for(i = 0; i < m; i++)
        free(M[i]);
    free(M);
}

void free_uchar_matrix(uint8 **M, int m) {
    int i;
    for(i = 0; i < m; i++)
        free(M[i]);
    free(M);
}

uint8 **new_square_matrix(int m) {
    uint8 **A;
    int i;
    A = (uint8 **)calloc(sizeof(uint8*),m);
    for(i = 0; i < m; i++)
        A[i] = (uint8 *) calloc (sizeof(uint8), m);
    return A;
}

void show_square_matrix_downto(uint8 **A, int m) {
     int i,j;
     //printf("%d.%d\n",m,exp);
     for(i=m-1;i>=0;i--) {
        for(j=m-1;j>=0;j--) {
            printf("%d",A[i][j]);
        }
        printf("\n");
     }
}

uint8 **copy_square_matrix(uint8 **A, int m) {
    uint8 **C;
    int i,j;
    C = new_square_matrix(m);
    for(i=0;i<m;i++) {
        for(j=0;j<m;j++) {
            C[i][j] = A[i][j];
        }
    }
    return C;
}

uint8 *new_array(int dim) {
    uint8 *ar;
    ar = (uint8 *)calloc(sizeof(uint8), dim);
    return ar;
}

uint8 **producto_matrices_cuadradas(uint8 **A, uint8 **B, int m) {
    int i,j,k;
    uint8 **R;
    R = new_square_matrix(m);
    for(i=0;i<m;i++) {
        for(j=0;j<m;j++) {
            for(k=0;k<m;k++) {
                R[i][j] = (R[i][j]+((A[i][k]*B[k][j])%2))%2;
            }
        }
    }
    return R;
}

int compare(uint8 *v1, uint8 *v2, int m) {
    int i;
    for (i = 0; i < m; i++) {
        if (v1[i] != v2[i]) {
            printf("v1[%d] = %d and v2[%d] = %d\n", i, v1[i], i, v2[i]);
            return FALSE;
        }
    }
    return TRUE;
}

void exp_type1(int gfield, int split) {
     uint8 **S;
     if (gfield == 5) {
         S = trino_squaring_matrix(gfield);
         n_squaring(S,gfield,1,split);
         n_squaring(S,gfield,2,split);
     } else if (gfield == 233) {
         S = trino_squaring_matrix(gfield);
         n_squaring(S,gfield,1,split);
         n_squaring(S,gfield,3,split);
         n_squaring(S,gfield,7,split);
         n_squaring(S,gfield,14,split);
         n_squaring(S,gfield,29,split);
         n_squaring(S,gfield,58,split);
         n_squaring(S,gfield,116,split);  
     } else if (gfield == 409) {
        S = trino_squaring_matrix(gfield);
        n_squaring(S,gfield,1,split);
        n_squaring(S,gfield,3,split);
        n_squaring(S,gfield,6,split);
        n_squaring(S,gfield,12,split);
        n_squaring(S,gfield,25,split);
        n_squaring(S,gfield,51,split);
        n_squaring(S,gfield,102,split);
        n_squaring(S,gfield,204,split);     
     } else if (gfield == 163) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,split);
        n_squaring(S,gfield,2,split);
        n_squaring(S,gfield,5,split);
        n_squaring(S,gfield,10,split);
        n_squaring(S,gfield,20,split);
        n_squaring(S,gfield,40,split);
        n_squaring(S,gfield,81,split);
     } else if (gfield == 283) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,split);
        n_squaring(S,gfield,2,split);
        n_squaring(S,gfield,4,split);
        n_squaring(S,gfield,8,split);
        n_squaring(S,gfield,17,split);
        n_squaring(S,gfield,35,split);
        n_squaring(S,gfield,70,split);
        n_squaring(S,gfield,141,split);       
     } else if (gfield == 571) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,split);
        n_squaring(S,gfield,2,split);
        n_squaring(S,gfield,4,split);
        n_squaring(S,gfield,8,split);
        n_squaring(S,gfield,17,split);
        n_squaring(S,gfield,35,split);
        n_squaring(S,gfield,71,split);
        n_squaring(S,gfield,142,split);
        n_squaring(S,gfield,285,split);     
    }
}
