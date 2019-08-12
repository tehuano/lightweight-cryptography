#include <stdio.h>
#include <stdlib.h>

/*
f (z) = z^163+z^7+z^6+z^3+1
f (z) = z^233+z^74+1
f (z) = z^283+z^12+z^7+z^5+1
f (z) = z^409+z^87+1
f (z) = z^571+z^10+z^5+z^2+1.
*/
int  ** potenciar(int **,int , int);

int ** n_squaring_matrix(int);
int ** trino_squaring_matrix(int );
int ** penta_squaring_matrix(int );

void n_squaring(int **, int, int, int *);
int ** multiplier_matrix(int);
void crear_suma_de_productos(int **, int , int, FILE *);

void inicializar_trino_squaring(int, int *, int *, int *);
void inicializar_penta_squaring(int, int *, int *, int *, int *, int *);
int * crear_v(int * u, int ln);
int ** nueva_matriz_cuadrada(int );
void mostrar_matriz_cuadrada_downto(int **, int);
int ** copiar_matriz_cuadrada(int **, int);
int ** producto_matrices_cuadradas(int **, int **, int);
int ** nueva_matriz(int, int);
int * poly_squaring(int );

int ** nueva_matriz_reduccion_trino(int *, int, int, int);
int ** nueva_matriz_reduccion_penta(int *, int, int, int, int, int);
    
int ** squaring_matrix(int **, int, int);
void arquitectura_potenciadora(int);
void crear_ecuaciones(int, FILE *);
void crear_codigo_potencias_pares(int gfield);
int * nuevo_arreglo(int );
void modulo_de_reduccion(int,int);

char cabecera1[] = "LIBRARY ieee;\nuse IEEE.STD_LOGIC_1164.ALL;\nuse work.libreria.all;\n\nentity multiplicador_clasico";
char cabecera2[] = " is\nGENERIC(M:integer:=M";
char cabecera22[]= ");\nPORT(\n\tA : IN  STD_LOGIC_VECTOR (M-1 DOWNTO 0);\n\tB : IN  STD_LOGIC_VECTOR(M-1 DOWNTO 0);\n\tC : OUT  STD_LOGIC_VECTOR(2*M-2 DOWNTO 0)\n);\nend multiplicador_clasico";
char cabecera3[] = ";\n\narchitecture behavioral of multiplicador_clasico";
char cabecera4[] = " is\n";
char cabecera5[] = "\n";
char cabecera6[] = "begin\n";
char farchivo[]  = "end behavioral;";


/*
        IF5: IF M=5 GENERATE
[1][2]multiplicador_clasico
        IF233: IF M=233 GENERATE
[1]
[3]
[7][14]
[29][58][116]
        IF409: IF M=409 GENERATE
[1]
[3][6][12]
[25]
[51][102][204]
        IF163: IF M=163 GENERATE
[1][2]
[5][10][20][40]
[81]
        IF283: IF M=283 GENERATE
[1][2][4][8]
[17]
[35][70]
[141]
        IF571: IF M=571 GENERATE
[1][2][4][8]
[17]
[35]
[71][142]
[285]

*/

int main(int argc, char *argv[])
{

      arquitectura_potenciadora(atoi(argv[1]));

    return 0;
}

void arquitectura_potenciadora(int gfield){
     
    // fprintf(ff,"\n\tIF%d: IF M=%d GENERATE\n",gfield,gfield);
  
     crear_codigo_potencias_pares(gfield);
     
    // fprintf(ff,"\tEND GENERATE IF%d;\n",gfield,gfield);
}
void crear_codigo_potencias_pares(int gfield){

     FILE * file;
     file = NULL;
     char nombre[128];
     
     sprintf(nombre,"%s.%d.vhd","multiplicador.clasico",gfield);
     file = fopen(nombre,"w");
     if(!file)exit(0);
             
     fprintf(file,"%s",cabecera1);
     fprintf(file,"%s",cabecera2);
     fprintf(file,"%s",cabecera22);
     fprintf(file,"%s",cabecera3);
     fprintf(file,"%s",cabecera4);
     fprintf(file,"%s",cabecera5);
     fprintf(file,"%s",cabecera6);
     crear_ecuaciones(gfield,file);
     fprintf(file,"%s",farchivo);
     fclose(file);
     printf("[listo %d]\n",gfield);   
}

int ** n_squaring_matrix(int gf){
    int **M;    
    
    switch(gf){
    case 5:
    case 233:
    case 409:
         M = trino_squaring_matrix(gf);
         break;
    case 163:
    case 283:
    case 571:
         M = penta_squaring_matrix(gf);
         break;
     default:
             exit(0);         
    }
    
}
int * crear_v(int * u, int ln){
     int * v;
     int i;
     v = nuevo_arreglo(ln-1);
     for(i=0;i<ln-1;i++){
     v[i] = u[i+1]-u[i];      
     }
     return v;
}
int ** trino_squaring_matrix(int gfield){
    
   int m,n,k;
   int dlm1;
   int **A;
   int **S;
   int *poly, **redu;
   
   dlm1 = (2*m-1);
   
   inicializar_trino_squaring(gfield,&m,&n,&k); 
   
   poly = poly_squaring(m);
   redu = nueva_matriz_reduccion_trino(poly,m,n,k);   
   
   A = squaring_matrix(redu,m,5);    

   return A;
}
int ** penta_squaring_matrix(int gfield){
    
   int m,n,p,q,r;
   int dlm1;
   int **A;
   int **S;
   int *poly, **redu;
   
   dlm1 = (2*m-1);
   
   inicializar_penta_squaring(gfield,&m,&n,&p,&q,&r); 
   
   poly = poly_squaring(m);
   redu = nueva_matriz_reduccion_penta(poly,m,n,p,q,r);   
  
   A = squaring_matrix(redu,m,17);    
    
   return A;
}
int ** potenciar(int **A,int gfield, int exp){
  
   int **S;
   int i;
   
   //S=nueva_matriz_cuadrada(gfield);
   S = copiar_matriz_cuadrada(A,gfield);
   
   for(i=1;i<exp;i++){
       S = producto_matrices_cuadradas(A,S,gfield);  
   }
   return S;
}
void crear_ecuaciones(int m, FILE * ff){

   int i,j,k,l, unos,contador;
   int dm1;
   int **W;
   
   
   dm1 = 2*m-1;
   
   W = multiplier_matrix(m);
   
   for(k=0;k<dm1;k++){
                      
       fprintf(ff,"\t\tC(%d)\t<=\t",k);
       unos=0;
       for(i=0;i<m;i++){
       unos+=(W[k][i]!=-1)?(1):(0);
       }
       contador=0;
       for(i=0;i<m;i++){
           if(W[k][i]!=-1){
              contador++;             
              if(contador<unos){
                  fprintf(ff,"(A(%d) AND B(%d)) XOR ",i,W[k][i]);
                  
              }else if(contador==unos){
                  fprintf(ff,"(A(%d) AND B(%d))",i,W[k][i]);
              }
           }
       }
       fprintf(ff,";\n");
   }
}

void crear_suma_de_productos(int **S, int m,int fila, FILE * file){

     int c2,contador_unos;
     int i,j;
     contador_unos=0;
     c2=0;
           
     for(j=0;j<m;j++)if(S[fila][j]==1)contador_unos++; 
          
     if(contador_unos==0){
           fprintf(file,"\'0\'");
     }else if(contador_unos==1){
           for(j=0;j<m;j++){
                if(S[fila][j]==1){
                   fprintf(file,"A(%d)",j);
                }              
           }
     }else if(contador_unos>1){
           //fprintf(ff,"=================  %d,%d ====================",m,indice);
           for(j=m-1;j>=0;j--){
                if(S[fila][j]==1){
                   if(c2==contador_unos-1){
                        fprintf(file,"A(%d)",j);          
                   }else{
                        fprintf(file,"A(%d) XOR ",j);
                   }
                   c2++;
                }              
           }       
     }
}
          
int ** squaring_matrix(int **R, int m, int filas){
   
   int **A;
   int i,j,x,y;
   A = nueva_matriz_cuadrada(m);

   for(i=0;i<filas;i++){
       for(j=0;j<m;j++){                       
          if(R[i][j] > -1){
              A[j][R[i][j]] = 1;
          }
       }      
   }
   return A;
}

int * poly_squaring(int m){
    
    int dm1,j,i;
    int *poly;
    
    dm1 = 2*m-1;
    
    poly = (int *)calloc(sizeof(int),dm1);

    for(i=1;i<dm1;i+=2){
       poly[i] = -1;
    }   
    j=0; 
    for(i=0;i<dm1;i+=2){
       poly[i] = j++;
    }
    
    return poly;
}

void inicializar_penta_squaring(int gfield,int *m, int *n, int *p, int *q, int *r){
   
   if(gfield>1){
      *m=gfield;
      switch(*m){
          case 163:*n=7;*p=6;*q=3;*r=0;break;
          case 283:*n=12;*p=7;*q=5;*r=0;break;
          case 571:*n=10;*p=5;*q=2;*r=0;break;
          default:
                  printf("ERROR en la entrada P\n");exit(0);
      }
  }else{
        printf("ERROR en la entrada P\n"); 
        exit(0);     
  }     
}

void inicializar_trino_squaring(int gfield,int *m, int *n, int *k){
   if(gfield>1){
      *m=gfield;
      switch(*m){
          case 5:*n=2;*k=0;break;
          case 233:*n=74;*k=0;break;
          case 409:*n=87;*k=0;break;
          default:
                  printf("ERROR en la entrada T\n");exit(0);
      }
  }else{
        printf("ERROR en la entrada T\n"); 
        exit(0);     
  }     
}

int ** nueva_matriz_reduccion_trino(int * poly, int m, int n, int q){
    
    int i,j,dm1,k1,k2,desborde,ultimo_usado,fila;
    int ** redu;
    int * potencias;
    
    dm1 = 2*m-1;  
    
    potencias = nuevo_arreglo(2);
    redu=nueva_matriz(5,m); 
    
    for(i=0;i<5;i++){
    for(j=0;j<m;j++){
       redu[i][j] = -1;
    }
    }
    
    potencias[0] = q;
    potencias[1] = n;
    
    for(i=0;i<m;i++){
       redu[0][i] = poly[i];
    }
    
    for(j=0;j<m-1;j++){
       redu[1][j] = poly[m+j];
    }  
    
    for(i=1;i<2;i++){
        for(k1=potencias[i],k2=0;k1<m;k1++,k2++){
            redu[2+(i-1)*3][k1] = poly[m+k2];
        }     
        for(j=0;j<2;j++){
            desborde=potencias[i]-1;
            ultimo_usado=dm1-desborde;
            fila=2+(i-1)*3+j+1;
            for(k1=0;k1<desborde;k1++){
                redu[fila][potencias[j]+k1] = poly[ultimo_usado+k1];   
            }
        }
    } 
        
    return redu;
}

int ** nueva_matriz_reduccion_penta(int * poly, int m, int n, int p, int q, int r){

    int i,j,dm1,k1,k2,desborde,ultimo_usado,fila;
    int ** redu;
    int * potencias;
    
    dm1 = 2*m-1;  
    
    potencias = nuevo_arreglo(4);
    redu=nueva_matriz(17,m); 
    
    for(i=0;i<17;i++){
    for(j=0;j<m;j++){
       redu[i][j] = -1;
    }
    }
    
    potencias[0] = r;
    potencias[1] = q;
    potencias[2] = p;
    potencias[3] = n;
    
    for(i=0;i<m;i++){
       redu[0][i] = poly[i];
    }
    
    for(j=0;j<m-1;j++){
       redu[1][j] = poly[m+j];
    }  
    
    
    for(i=1;i<4;i++){
        for(k1=potencias[i],k2=0;k1<m;k1++,k2++){
                redu[2+(i-1)*5][k1] = poly[m+k2];             
        }
        for(j=0;j<4;j++){
            desborde=potencias[i]-1;
            ultimo_usado=dm1-desborde;
            fila=2+(i-1)*5+j+1;
            for(k1=0;k1<desborde;k1++){
                redu[fila][potencias[j]+k1] = poly[ultimo_usado+k1];   
            }
        }      
    }

    return redu;
}


int ** nueva_matriz(int m, int n){
   int **M;
   int i;
   M = (int **)calloc(sizeof(int*),m);
   for(i=0;i<m;i++)
   M[i] = (int *) calloc (sizeof(int),n);

   return M;
}

int ** nueva_matriz_cuadrada(int m){
    int **A;
    int i;
    A = (int **) calloc(sizeof(int*),m);
    for(i=0;i<m;i++)
    A[i] = (int *) calloc (sizeof(int),m);
    return A;
}

void mostrar_matriz_cuadrada_downto(int **A, int m){
     int i,j;
     //fprintf(ff,"%d.%d\n",m,exp);
     for(i=m-1;i>=0;i--){
        for(j=m-1;j>=0;j--){
        printf("%d",A[i][j]);
        }
        printf("\n");
     }
     //fprintf(ff,".\n");
}

int ** multiplier_matrix(int gfield){
    
   int m,n,i,j;
   int **A;
   m=gfield;
   n = 2*m-1;
   A=nueva_matriz(n,m);
   
   
   for(i=0;i<n;i++){
   for(j=0;j<m;j++){
      A[i][j]=-1;
   }
   }
   
   for(i=0;i<m;i++){
   for(j=0;j<m;j++){
      A[j+i][i]=j;
   }
   }
   
   //mostrar_matriz(A,n,m);
   return A;
}
int ** copiar_matriz_cuadrada(int **A, int m){
    int **C;
    int i,j;
    
    C=nueva_matriz_cuadrada(m);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = A[i][j];
        }
    }
    return C;
}
int * nuevo_arreglo(int dim){
    int *ar;
    ar = (int *)calloc(sizeof(int),dim);
    return ar;
}
int ** producto_matrices_cuadradas(int **A, int **B, int m){
    int i,j,k;
    int **R;
    R = nueva_matriz_cuadrada(m);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            for(k=0;k<m;k++){
                  R[i][j] = (R[i][j]+((A[i][k]*B[k][j])%2))%2;
            }
        }
    }
    return R;
}
