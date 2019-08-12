#include <math.h>
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
void crear_suma_de_productos(int **, int **, int, int, int, int *,FILE *);
void crear_suma_de_productos_squaring(int **,int , int , FILE *);

void inicializar_trino_squaring(int, int *, int *, int *);
void inicializar_penta_squaring(int, int *, int *, int *, int *, int *);
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
void crear_ecuaciones(int **, int **, int **, int **, int, FILE *);
void crear_codigo_potencias_pares(int , int **, int **, int **, int **);
int * nuevo_arreglo(int );
void modulo_de_reduccion(int,int);

char cabecera1[] = "LIBRARY ieee;\nuse IEEE.STD_LOGIC_1164.ALL;\nuse work.libreria.all;\n\nentity mastrovito";
char cabecera2[] = " is\ngeneric(M:integer:=M);\nPORT(\n\tA : IN  STD_LOGIC_VECTOR (M-1 DOWNTO 0);\n\tB : IN  STD_LOGIC_VECTOR (M-1 DOWNTO 0);\n\tR : OUT  STD_LOGIC_VECTOR(M-1 DOWNTO 0)\n);\nend mastrovito";
char cabecera3[] = ";\n\narchitecture behavioral of mastrovito";
char cabecera4[] = " is\n";
char cabecera5[] = "\n";
char cabecera6[] = "begin\n";
char farchivo[]  = "\nend behavioral;";

int ** copiar_intervalo_matriz_multiplicacion(int ** , int ,int , int );
int ** matriz_Q(int);
int ** Q_pentanomio(int, int, int , int, int);
int ** Q_trinomio(int, int, int);
void inicializar_pentanomio(int ,int *, int *, int *, int *, int *);
void inicializar_trinomio(int, int *, int *, int *);
void mostrar_matriz(int **A, int m, int n);
void crear_factores_mastrovito_exp(int **L, int **Q, int **U,int gfield, int , int ,FILE * ff);


int main(int argc, char *argv[])
{

//  n_squaring(233,74,1);
    //char cc[255]="10101110000100010101011101001111011110110111001111110000111111010111011101101010111000011000111110111100100100000100000100011010100101100111110000000011110110111110111111110100111010011000000000000010100111000100101011010111111100001";
    //char cc[1024]="0	0	1	0	1	1	1	0	0	0	0	0	0	0	0	0	0	1	1	0	1	0	0	1	0	0	0	0	1	1	0	1	1	1	1	1	1	0	1	1	1	1	1	1	0	1	1	1	0	0	1	0	0	0	1	1	1	1	1	0	1	0	1	0	0	0	0	1	0	1	0	1	1	0	1	1	1	0	1	0	1	0	0	1	1	1	1	0	1	1	1	0	0	1	0	0	0	0	1	1	1	1	1	1	0	0	0	1	0	0	1	1	0	0	0	0	1	0	1	0	0	1	1	0	0	0	1	0	1	0	1	0	1	1	0	1	0	1	1	1	1	1	0	1	1	0	0	1	1	0	0	0	1	0	1	1	0	1	1	0	1	1	1	0	1	0	0	1	0	1	0	0	0	0	0	0	0	0	0	1	0	1	1	1	1	0	1	0	1	0	1	1	0	0	0	0	1	1	1	0	0	1	1	1	0	1	0	1	1	0	0	1	1	1	0	0	1	0	1	0	0	0	0	0	0	0	1	0	0	1	0	1	0";
//    int l,i;
//    l=strlen(cc);
//    for(i=l-1;i>=0;i--) if(cc[i]=='0' || cc[i]=='1')fprintf(ff,"%c",cc[i]);
      
      //fprintf(ff,"%s",cabecera);
      arquitectura_potenciadora(atoi(argv[1]));
 //     arquitectura_potenciadora(283);
//      arquitectura_potenciadora(571);
      //fprintf(ff,"%s",farchivo);
    //printf("\n");system("PAUSE");	
    return 0;
}

void arquitectura_potenciadora(int gfield){
     
    // fprintf(ff,"\n\tIF%d: IF M=%d GENERATE\n",gfield,gfield);
     int **S,**W,**L,**U,**Q;
      
     W = multiplier_matrix(gfield);
     L = copiar_intervalo_matriz_multiplicacion(W,gfield,0,gfield-1);
     U = copiar_intervalo_matriz_multiplicacion(W,gfield,gfield,(2*gfield)-2);
     Q = matriz_Q(gfield);
     
     //mostrar_matriz(Q,gfield,gfield-1);
     //mostrar_matriz(S,gfield,gfield);
     crear_codigo_potencias_pares(gfield,L,Q,U,W);
     
    // fprintf(ff,"\tEND GENERATE IF%d;\n",gfield,gfield);
}
void crear_codigo_potencias_pares(int gfield, int **L, int **Q, int **U, int **W){
        
     int indice,i,hmw,mults,j;
     int longitud,longitudv;
     int * tira, *pots;
     int **P;
     int bandera=0;
     char * nombre;
     
     
     nombre = (char*)calloc(sizeof(char),128);
     
     
     //fprintf(ff,"longitus cadena:%d\nmultiplicaciones:%d\n",longitud,mults);

     FILE * file;
     file = NULL;
     
             //fprintf(ff,"\n----------------  [%d]  -----------------\n",pots[j]);
             
             sprintf(nombre,"%s.%d.vhd","mastrovito",gfield);
             file = fopen(nombre,"w");
             if(!file)exit(0);
             
             fprintf(file,"%s",cabecera1);
             fprintf(file,"%s",cabecera2);
             fprintf(file,"%s",cabecera3);
             fprintf(file,"%s",cabecera4);
             fprintf(file,"%s",cabecera5);
             fprintf(file,"%s",cabecera6);
             crear_ecuaciones(L,Q,U,W,gfield,file);
             //fprintf(file,"\t\tred%d:\tpolynomial_reductor GENERIC MAP(M) PORT MAP(C,R);",pots[j]);
             fprintf(file,"%s",farchivo);
             fclose(file);
             printf("[listo]\n");
}

void crear_ecuaciones(int **L, int **Q, int **U, int **W, int gfield, FILE * ff){

   int i,j,k,ii,l, unos, unos2, unosqu, cont;
   int dm1;
   
   dm1 = 2*gfield-1;
   
//   for(i=0;i<m;i++){
//       fprintf(ff,"\t\tB(%d)\t<=\t",i);
//       crear_suma_de_productos(S,m,i, ff);
//       fprintf(ff,";\n"); 
//   }
//   
//   fprintf(ff,"\t\t--\n");

     //mostrar_matriz(P,gfield,gfield);
     fprintf(ff,"\n");
   fprintf(ff,"\t\t---------------\n");
     for(i=0;i<gfield;i++){
         fprintf(ff,"\t\tR(%d) <= ",i);
         cont=0;
         unos=0;
         //for(j=0;j<gfield;j++)if(P[j][i]==1)unos++;
         for(j=0;j<gfield;j++){
                 fprintf(ff,"(B(%d)",j);
                 fprintf(ff,"AND(");
                 crear_factores_mastrovito_exp(L,Q,U,gfield,i,j,ff);
                 fprintf(ff,")");
                 if(j<gfield-1){
                 fprintf(ff,")XOR");
                 }else{
                 fprintf(ff,")");      
                 }
         }fprintf(ff,";\n");
     }
}

void crear_factores_mastrovito_exp(int **L, int **Q, int **U,int gfield,int filam, int colum,FILE * ff){
     int k;
     int unos,contador,unos2;
     
     for(k=0;k<gfield-1;k++){
         if(Q[filam][k]==1 && U[k][colum]!=-1){
         unos=1;
         break;
         }
     } 
     if(L[filam][colum]!=-1){
         fprintf(ff,"A(%d)",L[filam][colum]);
         if(unos==1){
         fprintf(ff,"XOR(");
         } 
     }
                   
     if(unos==1){
     //fprintf(ff,"(");
     crear_suma_de_productos(Q,U,gfield-1,filam,colum,&unos2,ff);
     //fprintf(ff,")");  
     }
           
     if(L[filam][colum]!=-1){
        if(unos==1){
        fprintf(ff,")");
        } 
     }
}

void crear_suma_de_productos_squaring(int **S, int m,int fila, FILE * file){

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
                        fprintf(file,"A(%d)XOR ",j);
                   }
                   c2++;
                }              
           }       
     }
}

void mostrar_matriz(int **A, int m, int n){
       int i,j;
       printf("\n");
       for(i=0;i<m;i++){
           for(j=0;j<n;j++){
                 printf("%d ",A[i][j]);
           }      
           printf("\n");
       } 
       printf("\n");     
}
int ** matriz_Q(int gf){
    
    int **R;
    int m,n,p,q,r;
    int esTrinomio=1;
    
    if(gf==5||gf==193||gf==233||gf==409){
          inicializar_trinomio(gf,&m,&n,&p);
    }else if(gf==163||gf==283||gf==571){
          inicializar_pentanomio(gf,&m,&n,&p,&q,&r);
          esTrinomio = 0;
    }else exit(0);

    
    if(esTrinomio==1){
      R = Q_trinomio(m,n,p);   
    }else{
      R = Q_pentanomio(m,n,p,q,r);    
    }
    return R;
    
}
int ** Q_trinomio(int gfield,int n,int p){
    int ** Q;
    int i,j;
    int gf, gft;
    gf = gfield;
    gft = gfield-1; 
    Q = nueva_matriz(gfield,gfield-1);

    for(i = 0;i<gft;i++){
       Q[i][i] = 1;  
    }
    for(i = 0;i<gft;i++){
        if(n+i < gf ){
            Q[n+i][i] = 1;       
        }else{
            Q[p+((n+i)%gf)][i] = 1;
            Q[n+((n+i)%gf)][i] = 1;  
        }
    }
    return Q;
}
int ** Q_pentanomio(int gfield,int n,int p, int q, int r){
    int ** Q;
    int i,j;
    int gf, gft;
    gf = gfield;
    gft = gfield-1; 
    int nmasi,nmasimodgf,pmasi,pmasimodgf,qmasi,qmasimodgf;

    Q = nueva_matriz(gf,gft);
   
   for(i=0;i<gft;i++){
       Q[i][i] = 1;  
    }
    for(i=0;i<gft;i++){
	//para n
	nmasi=(n+i);
	nmasimodgf=(nmasi)%gf;
	//para p	
	pmasi=(p+i);
	pmasimodgf=(pmasi)%gf;
	//para q	
	qmasi=(q+i);
	qmasimodgf=(qmasi)%gf;

        if((nmasi) < gf ){		//para n
            Q[nmasi][i] =  (Q[nmasi][i]+1)%2;       
        }else{
            Q[r+(nmasimodgf)][i] = (Q[r+(nmasimodgf)][i]+1)%2;
	    Q[q+(nmasimodgf)][i] = (Q[q+(nmasimodgf)][i]+1)%2;
            Q[p+(nmasimodgf)][i] = (Q[p+(nmasimodgf)][i]+1)%2;
            Q[n+(nmasimodgf)][i] = (Q[n+(nmasimodgf)][i]+1)%2;  
        }

        if((pmasi) < gf ){		//para p
            Q[pmasi][i] =  (Q[pmasi][i]+1)%2;      
        }else{
	    Q[r+(pmasimodgf)][i] = (Q[r+(pmasimodgf)][i]+1)%2;
	    Q[q+(pmasimodgf)][i] = (Q[q+(pmasimodgf)][i]+1)%2;
            Q[p+(pmasimodgf)][i] = (Q[p+(pmasimodgf)][i]+1)%2;
            Q[n+(pmasimodgf)][i] = (Q[n+(pmasimodgf)][i]+1)%2;  
        }

        if((qmasi) < gf ){		//para q
            Q[qmasi][i] =  (Q[qmasi][i]+1)%2;      
        }else{
	    Q[r+(qmasimodgf)][i] = (Q[r+(qmasimodgf)][i]+1)%2;
	    Q[q+(qmasimodgf)][i] = (Q[q+(qmasimodgf)][i]+1)%2;
            Q[p+(qmasimodgf)][i] = (Q[p+(qmasimodgf)][i]+1)%2;
            Q[n+(qmasimodgf)][i] = (Q[n+(qmasimodgf)][i]+1)%2;  
        }
    }

    return Q;
}
int ** copiar_intervalo_matriz_multiplicacion(int ** M, int gfield, int ini, int fin){
    int i,j,i2;
    int ** M2;

    M2 = nueva_matriz(fin-ini+1,gfield);
    for(i=ini,i2=0;i<=fin;i++,i2++){
       for(j=0;j<gfield;j++){
          //printf("%d,%d\n",i,j);
          M2[i2][j]=M[i][j];
       }
    }

    return M2;
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
   
   S = copiar_matriz_cuadrada(A,gfield);
   
   for(i=1;i<exp;i++){
       S = producto_matrices_cuadradas(A,S,gfield);  
   }
   return S;
}


void crear_suma_de_productos(int **Q, int **U, int len, int filaq, int colu, int *ct,FILE * file){

     int c2,contador_unos;
     int i,j;
     contador_unos=0;
     c2=0;
     *ct=0;
     
     for(j=0;j<len;j++)if(Q[filaq][j]==1 && U[j][colu]!=-1)contador_unos++; 
          
     *ct=contador_unos;
     

     if(contador_unos==1){
           for(j=0;j<len;j++){
                if(Q[filaq][j]==1 && U[j][colu]!=-1){
                   fprintf(file,"A(%d)",U[j][colu]);
                   break;
                }              
           }
     }else if(contador_unos>1){
           //fprintf(ff,"=================  %d,%d ====================",m,indice);
           for(j=len-1;j>=0;j--){
                if(Q[filaq][j]==1 && U[j][colu]!=-1){
                   if(c2==contador_unos-1){
                        fprintf(file,"A(%d)",U[j][colu]); 
                        break;         
                   }else{
                        fprintf(file,"A(%d)XOR ",U[j][colu]);
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

void inicializar_pentanomio(int gfield,int *m, int *n, int *p, int *q, int *r){
   
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

void inicializar_trinomio(int gfield,int *m, int *n, int *k){
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
     for(i=m-1;i>=0;i--){
        for(j=m-1;j>=0;j--){
        printf("%d",A[i][j]);
        }
        printf("\n");
     }
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
                  R[i][j] = (R[i][j]+(A[i][k]*B[k][j]))%2;
            }
        }
    }
    return R;
}
