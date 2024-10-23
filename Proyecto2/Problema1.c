#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define NO_CASILLAS_DISPONIBLES 0
#define MAX_SOLUCIONES 10

int max_solutions;

void inicializarTablero(char **tablero,int n);
int insertarCaballos(char **tablero,int fila,int columna,int casillasDisponibles,int numCaballos,int n);
int verificarMovimientos(char **tablero,int fila,int columna,int casillasDisponibles,int n);
void imprimirTablero(char **tablero,int n);
void imprimirTableroarchivo(char **tablero,int n);
int maximoCaballos(int totalCaballos[]);
 
int main(){
    FILE* fichero;//archivo
    int n,i,j = 0,fila,columna,numCaballos,casillasDisponibles,MaxCaballos;
    char **tablero;
    int x[10],y[10],valores[10];//cordenadas y valor que contendran las cordenadas de los 10 mejores resultados
    int min=100,max,totguardados=0;
    int totalmin=0,control=0;

    do{//obligamos al usuario a que ingrese un tablero de entre 2 y 20
        printf("Dame tamanio de tablero: ");
        scanf("%d",&n);
    }while(n < 2 || n > 20);

    max_solutions = n*n;//numero maximo de soluciones a verificar
    int totalCaballos[max_solutions];
    
        tablero = malloc(n*sizeof(char*));//creamos el tablero del tamaño del usuario a ingresado

        for(i = 0;i < n;i++)
           tablero[i] = malloc(n);

        for(int fil=0 ; fil < n ; fil++){//recorremos todas las filas
            for(int col=0 ; col < n ; col++){//recorremos todas las columnas
                numCaballos = 0;//declaramos el numero de caballos 0
                casillasDisponibles = n*n;//total de casillas en el tablero
                
                fila = fil;//usamos los bucles para asignar posiciones de donde se ubicara el caballo
                columna = col;

                printf("(%d,%d)\n",fila,columna);//posicion donde el primer caballo estara ubicado
                inicializarTablero(tablero,n);//llenamos el tablero con puros 0 
                totalCaballos[j] = insertarCaballos(tablero,fila,columna,casillasDisponibles,numCaballos,n);
                imprimirTablero(tablero,n);
                printf("\n\nEl numero maximo de caballos en esta solucion es de %d\n",totalCaballos[j]);//muestra el numero maximo de caballos en esa posible posicion
                if(j < 10){//ingresamos los primeras 10 opciones 
                    valores[j]=totalCaballos[j];
                    x[j] = col;
                    y[j] = fil;
                    if(valores[j] < min){
                        min = totalCaballos[j];   
                    }
                }
                if(j >= 10){
                    if(totalCaballos[j] > min){//verificamos que los nuevos datos sean mayores al menor del arreglo
                        for(int v=0 ; v<10 ; v++){//recorremos el arreglo encontrando el valor menor
                            if(valores[v]==min){//ya que lo encontremos le asignaremos los nuevos valores
                                valores[v] = totalCaballos[j];
                                x[v] = col;
                                y[v] = fil;
                                break;
                            }
                        }
                        min=100;
                        for(int v=0 ; v<10 ; v++){//buscamos el nuevo valor menor en el arreglo
                            if(valores[v]<min){
                                min = valores[v];
                            }
                        }
                    }
                }
                j++;
            }
        }
        MaxCaballos = maximoCaballos(totalCaballos);
        printf("\nEl numero maximo de caballos en un tablero de %d x %d sin atacarse es %d\n",n,n,MaxCaballos);
        
        char nombre[17] = "CABAL_00.OUT.txt";//creamos el nombre del archivo en base al numero asignado a el tamanio del tablero
        if (n < 10){
            nombre[7]=n+48;
        }else{
            nombre[6]='1';
            nombre[7]=(n-10)+48;
        }

        fichero = fopen(nombre, "wt");
        //fputs("%d\n",MaxCaballos,fichero);
        fprintf (fichero, "%d\n", MaxCaballos);
        fprintf (fichero, "%d\n", casillasDisponibles);
        for(int i=0 ; i<10 ; i++){//recorremos los 10 mejores resultados
            numCaballos = 0;
            inicializarTablero(tablero,n);//llenamos el tablero con puros 0 
            totalCaballos[j] = insertarCaballos(tablero,y[i],x[i],casillasDisponibles,numCaballos,n);
            
            int k,l;
            for(k = 0;k < n;k++){//guardamos los mejores 10 tableros en el archivo
                fprintf(fichero,"\n");
                for(l = 0;l < n;l++)
                fprintf (fichero, "%c ", tablero[k][l]);
            }
            fprintf(fichero,"\n\n");

        }    
        fclose(fichero);//cerramos el archivo
    return 0;
}


 
void inicializarTablero(char **tablero,int n){//inicializamos el tablero en ceros
    int i,j;
    for(i = 0;i < n;i++){
        for(j = 0;j < n;j++)
           tablero[i][j] = '0';
    }
}
 
int insertarCaballos(char **tablero,int fila,int columna,int casillasDisponibles,int numCaballos,int n){
    if(casillasDisponibles > NO_CASILLAS_DISPONIBLES){//verificamos que no queden casillas vacias
        if(tablero[fila][columna] == '0'){//verificamos que en la posicion indicada este vacia y no exista un caballo
            tablero[fila][columna] = '1';//asignamos un caballo a esa posicion
            casillasDisponibles = verificarMovimientos(tablero,fila,columna,casillasDisponibles,n);//llamamos la funcion que verifica los movimientos
            numCaballos++;
            fila = rand() % n;//asignamos nueas cordenadas al tablero, para añadir caballos
            columna = rand() %n;
            insertarCaballos(tablero,fila,columna,casillasDisponibles,numCaballos,n);
        }
        else{
            fila = rand() % n;//asignamos nueas cordenadas al tablero, para añadir caballos
            columna = rand() %n;
            insertarCaballos(tablero,fila,columna,casillasDisponibles,numCaballos,n);
        }
    }
    else
       return numCaballos;//regresamos el toatl de caballos que cupieron
}
 
int verificarMovimientos(char **tablero,int fila,int columna,int casillasDisponibles,int n){
    int i,j,nuevaFila,nuevaColumna,eliminadas;

    eliminadas = casillasDisponibles-1;//definimos las casillas disponibes que quedan en nuestro tablero

    nuevaFila = fila + 2;//verificamos la siguiente posicion asignandole los posibles movimientos
    nuevaColumna = columna -1;
    //ahora verificaremos que la nueva posicion no se salga del tablero y que esa posicion este disponible sin ningun caballo que sea atacado
    if((nuevaFila>=0 && nuevaFila<n) && (nuevaColumna>=0 && nuevaColumna<n) && ( tablero[nuevaFila][nuevaColumna] == '0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    //verificamos los otros 7 pasos posibles del caballo
    nuevaFila = fila + 2;
    nuevaColumna = columna + 1;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila + 1;
    nuevaColumna = columna - 2;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila + 1;
    nuevaColumna = columna + 2;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila - 2;
    nuevaColumna = columna - 1;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila - 2;
    nuevaColumna = columna + 1;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila - 1;
    nuevaColumna = columna - 2;
    if((nuevaFila>=0&&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    nuevaFila = fila - 1;
    nuevaColumna = columna + 2;
    if((nuevaFila >= 0 &&nuevaFila<n)&&(nuevaColumna>=0&&nuevaColumna<n)&&(tablero[nuevaFila][nuevaColumna]=='0')){
        tablero[nuevaFila][nuevaColumna] = 'O';
        eliminadas--;
    }
    return eliminadas;
 }

 
void imprimirTablero(char **tablero,int n){//mostramos el tablero
    int i,j;
    for(i = 0;i < n;i++)
    {
        printf("\n");
        for(j = 0;j < n;j++)
           printf("[%c]",tablero[i][j]);
    }
    printf("\n");
}
 
 int maximoCaballos(int totalCaballos[]){//guardamos el mejor numero de caballos de todos
    int Maximo,i;
    Maximo = totalCaballos[0];
    for(i = 0;i < max_solutions;i++){
        printf("%i ",totalCaballos[i]);
        if(totalCaballos[i] > Maximo)
           Maximo = totalCaballos[i];
    }
    return Maximo;
}