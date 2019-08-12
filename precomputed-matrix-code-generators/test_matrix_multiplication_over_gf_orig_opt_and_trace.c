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
void multiply(int, uint8 **, int **, uint8 *, int m, int n, int mt, int nt, uint8 *);
void exp_type1(int);
void free_uchar_matrix(uint8 **M, int m);
void free_int_matrix(int **M, int m);
void show_square_matrix_downto(uint8 **, int);
void n_squaring(uint8 **, int, int, int *);
void inicializar_trino_squaring(int, int *, int *, int *);
void inicializar_penta_squaring(int, int *, int *, int *, int *, int *);
void load_uchar_matrix_csv(const uint8 *file_name, uint8 **A, int m, int n);
void load_int_matrix_csv(const uint8 *file_name, int **A, int m, int n);

int main(int argc, uint8 *argv[]) {
    uint8 wrong_arguments = TRUE;
    uint8 result = FALSE;
    uint8 **A = NULL;
    uint8 *test_vector = NULL;
    uint8 *result_vector = NULL;
    uint8 *gold_vector = NULL;
    uint8 name[128];
    int m = 0, n = 0, mt = 0, nt = 0, gf = 0, el = 0;
    int field = 163, i = 0;
    int test_number = 0, test_count = 0;
    int **T = NULL;
    
    srand(time(NULL));   // Initialization, should only be called once.
    if (argc >= 3) {
        field = atoi(argv[1]);
        if (field == 5 || field == 163 || field == 233 || field == 283 || field == 409 || field == 571) {
            wrong_arguments = FALSE;
        }
    }
    if (wrong_arguments) {
        printf("Usage: program 5|163|233|283|409|571 matrix_original matrix_test1 trace_test1 matrix_test2 trace_test2 ... matrix_testn trace_testn\n");
    } else {
        test_vector = (uint8 *) malloc(field * sizeof(uint8));
        gold_vector = (uint8 *) malloc(field * sizeof(uint8));
        for (i = 0; i < field; i++) {
            test_vector[i] = ((rand() & 0x000000ff) > 0x7f) ? 1:0;
            printf("%d", test_vector[i]);
        } printf("\n");
        m = field;
		n = field;
        A = allocate_uchar_matrix(field, field);
        load_uchar_matrix_csv(argv[2], A, m, n);
        multiply(field,A,T,test_vector,m,n,mt,nt,gold_vector);
        free_uchar_matrix(A, m);
        if (argc >= 4) {
            result_vector = (uint8 *) malloc(field * sizeof(uint8));
            for (test_number = 3, test_count = 1; test_number < argc; test_number += 2, test_count++) {
                sscanf(argv[test_number],"squaring_matrix_%d_%d_opt_%dx%d.dat", &gf, &el, &m, &n);
                sscanf(argv[test_number + 1],"squaring_matrix_%d_%d_trace_%dx%d.dat", &gf, &el, &mt, &nt);
                printf("reduction m = %d, n = %d. trace m = %d, n = %d\n", m, n, mt, nt);
                A = allocate_uchar_matrix(m,n);
                T = allocate_int_matrix(mt,nt);
                load_uchar_matrix_csv(argv[test_number],A,m,n);
                load_int_matrix_csv(argv[test_number + 1],T,mt,nt);
                multiply(field,A,T,test_vector,m,n,mt,nt,result_vector);
                result = compare(gold_vector,result_vector,field);
                free_uchar_matrix(A,m);
                free_int_matrix(T,mt);
                if (result == FALSE) {
                    printf("\nTest %d Failed !!\n", test_count);
                } else {
                    printf("\nTest %d Passed\n", test_count);
                }
            }
        }
    }

    // free allocated memory
    if (result_vector) {
        free(result_vector);
    }
    if (test_vector) {
        free(test_vector);
    }
    if (gold_vector) {
        free(gold_vector);
    }
    
    return 0;
}

void multiply(int gf, uint8 **A, int **Trace, uint8 *testv, int m, int n, int mt, int nt, uint8 *resultv) {
    int i = 0, j = 0, idx = 0;
    int limit_m, limit_n;
    uint8 *tracev = NULL;
    uint8 a, b;
    limit_m = (m > gf)?m:gf;
    limit_n = (n > gf)?n:gf;
    if (Trace) {
        printf("Construct trace vector with m = %d, n = %d\n", mt, nt);
        tracev = (uint8 *) malloc(sizeof(uint8) * mt);
        for (i = 0; i < mt; i++) {
            tracev[i] = 0x05;
        }
        for (idx = 0; idx < mt; idx++) {
            compute_trace_element(gf,Trace,tracev,testv,mt,nt,idx);
        }
        for (idx = 0; idx < mt; idx++) {
            if ((tracev[idx] != 0) && (tracev[idx] != 1)) {
                printf("trace_vector[%d] != 1|0, %d", idx, tracev[idx]);
            }
        }
    }
    for (i = 0; i < limit_m; i++) {
        resultv[i] = 0;
        for (j = 0; j < limit_n; j++) {
            if (j < gf) {
                resultv[i] ^= (A[i][j] * testv[j]);
			    //if (0 == i && A[i][j] == 1) {
                //    printf("(%d)%d*%d ", j, A[i][j], testv[j]);
			    //}
            } else {
                resultv[i] ^= (A[i][j] * tracev[j - gf]);
			    //if (0 == i && (A[i][j] == 1 || j == 667)) {
                //   printf("(%d)%d*%d ", j, A[i][j], tracev[j - gf]);
			    //}
            }
        }
		//if (0 == i) {
		//	printf("\n>>>\n");
		//}
    }
    if (tracev) free(tracev);
}

uint8 compute_trace_element(int gf, int **Trace, uint8 *tracev, uint8 *testv, int mt, int nt, int index) {
    int i, index_a, index_b;
    uint8 a, b;
    /*
    if ((index-163) < 0 || (index-163) >= mt) {
        printf("Error. index = %d", (index-163));
	}
	*/
    index_a = Trace[index][0];
    index_b = Trace[index][1];
    if (index_a < gf) {
        a = testv[index_a];
        //printf("%d ", index_a);
    } else {
        if ((0 == tracev[index_a - gf]) || (1 == tracev[index_a - gf])) {
			//printf("has data a !!\n");
            a = tracev[index_a - gf];
        } else {
			//printf("Recursion a !!\n");
            a = compute_trace_element(gf, Trace, tracev, testv, mt, nt, index_a - gf);
            //tracev[index_a - gf] = a;
        }
    }
    if (index_b < gf) {
        b = testv[index_b];
        //printf("%d ", index_b);
    } else {
        if ((tracev[index_b - gf] == 0) || (tracev[index_b - gf] == 1)) {
			//printf("has data b !!\n");
            b = tracev[index_b - gf];
        } else {
            //printf("Recursion b !!\n");
            b = compute_trace_element(gf, Trace, tracev, testv, mt, nt, index_b - gf);
            //tracev[index_b - gf] = b;
        }
    }
    tracev[index] = a ^ b;
    return a ^ b;
}

void load_int_matrix_csv(const uint8 *file_name, int **A, int m, int n) {
    uint8 buffer[1024];
    uint8 *record,*line;
    int i = 0, j = 0;
    FILE *fstream = fopen(file_name,"r");
    if (fstream == NULL) {
        printf("\n file opening failed ");      
        return;
    }
    //printf("#### loading %s, m = %d, n = %d\n", file_name, m, n);
    i = 0;
    while ((i < m) && ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)) {
        record = strtok(line,",");
        j = 0;
        while ((j < n) && (record != NULL)) {
            A[i][j++] = atoi(record);
            record = strtok(NULL,",");
        }
        i++;
    }
    if (fstream) fclose(fstream);
}

void load_uchar_matrix_csv(const uint8 *file_name, uint8 **A, int m, int n) {
    uint8 buffer[1024*10] ;   
    uint8 *record,*line;   
    int i = 0, j = 0;
    FILE *fstream = fopen(file_name,"r");
    if (fstream == NULL) {
        printf("\n file opening failed ");      
        return;
    }
	//printf("#### loading %s, m = %d, n = %d\n", file_name, m, n);
    i = 0;
    while ((i < m) && ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)) {
        record = strtok(line,",");
        j = 0;
        while ((j < n) && (record != NULL)) {
            A[i][j++] = atoi(record);
            //if (0 == i && A[i][j-1]) {
            //    printf("$$$$ (%d) \n", j-1);
			//}
            record = strtok(NULL,",");
        }
        i++;
    }
    if (fstream) fclose(fstream);
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

void save_matrix(uint8 **A, int gfield, int exp) {
    uint8 fname[128];
    int i, j;
    FILE *file = NULL;
    sprintf(fname,"squaring_mtrix_%d_%d.dat",gfield,exp);
    file = fopen(fname,"w");
    for (i=0;i<gfield;i++) {
        for (j=0;j<gfield-1;j++) {
            fprintf(file,"%d,",A[i][j]);
        }
        fprintf(file,"%d\n",A[i][j]);
    }
    fclose (file);
}

void n_squaring(uint8 **A,int gfield, int exp, int * _index) {
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
   save_matrix(S,gfield,exp);
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

void exp_type1(int gfield) {
     int _index;
     uint8 **S;
     _index = 0;
     if (gfield == 5) {
         S = trino_squaring_matrix(gfield);
         n_squaring(S,gfield,1,&_index);
         n_squaring(S,gfield,2,&_index);
     } else if (gfield == 233) {
         S = trino_squaring_matrix(gfield);
         n_squaring(S,gfield,1,&_index);
         n_squaring(S,gfield,3,&_index);
         n_squaring(S,gfield,7,&_index);
         n_squaring(S,gfield,14,&_index);
         n_squaring(S,gfield,29,&_index);
         n_squaring(S,gfield,58,&_index);
         n_squaring(S,gfield,116,&_index);  
     } else if (gfield == 409) {
        S = trino_squaring_matrix(gfield);
        n_squaring(S,gfield,1,&_index);
        n_squaring(S,gfield,3,&_index);
        n_squaring(S,gfield,6,&_index);
        n_squaring(S,gfield,12,&_index);
        n_squaring(S,gfield,25,&_index);
        n_squaring(S,gfield,51,&_index);
        n_squaring(S,gfield,102,&_index);
        n_squaring(S,gfield,204,&_index);     
     } else if (gfield == 163) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,&_index);
        n_squaring(S,gfield,2,&_index);
        n_squaring(S,gfield,5,&_index);
        n_squaring(S,gfield,10,&_index);
        n_squaring(S,gfield,20,&_index);
        n_squaring(S,gfield,40,&_index);
        n_squaring(S,gfield,81,&_index);
     } else if (gfield == 283) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,&_index);
        n_squaring(S,gfield,2,&_index);
        n_squaring(S,gfield,4,&_index);
        n_squaring(S,gfield,8,&_index);
        n_squaring(S,gfield,17,&_index);
        n_squaring(S,gfield,35,&_index);
        n_squaring(S,gfield,70,&_index);
        n_squaring(S,gfield,141,&_index);       
     } else if (gfield == 571) {
        S = penta_squaring_matrix(gfield);
        n_squaring(S,gfield,1,&_index);
        n_squaring(S,gfield,2,&_index);
        n_squaring(S,gfield,4,&_index);
        n_squaring(S,gfield,8,&_index);
        n_squaring(S,gfield,17,&_index);
        n_squaring(S,gfield,35,&_index);
        n_squaring(S,gfield,71,&_index);
        n_squaring(S,gfield,142,&_index);
        n_squaring(S,gfield,285,&_index);     
    }
}
