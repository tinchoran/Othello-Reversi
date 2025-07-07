#include <stdio.h>
#include <stdlib.h>
#define ROWS 8
#define COLS  8
#define blanco 'B'
#define negro 'N'
#define vacio 'V'

void inicializarTablero(char arr[ROWS][COLS]);
void mostrarTablero(char arr[ROWS][COLS]);

int main(){

        srand(getpid());

        char tablero[ROWS][COLS];
        inicializarTablero(tablero);
        mostrarTablero(tablero);
        return 0;
}


void inicializarTablero(char arr[ROWS][COLS]){
        int i,j;
        // configuracion = número aleatorio entre 0 y 1: describe la configuración inicial;0 para cruz;1 para columnas.
        int configuracion = rand() % 2;
        printf("\nConfiguración: %d\n", configuracion);
        for(i=0; i<ROWS;i++){
                for(j=0;j<COLS;j++){
                        arr[i][j] = vacio;
                }
        }
        printf("%c", arr[3][3]);
        if(configuracion ==  0){
                arr[3][3] = blanco;arr[3][4] = negro;
                arr[4][3] = negro;arr[4][4]  = blanco;
        } else if (configuracion == 1){
                arr[3][3] = blanco;arr[3][4] = negro;
                arr[4][3] = blanco;arr[4][4] = negro;
        }
}


void  mostrarTablero(char arr[ROWS][COLS]){
        int i,j;
        for(i=0;i<ROWS;i++){
                printf("\n\n");
                for(j=0;j<COLS;j++){
                        printf("  %c  ", arr[i][j]);
                }
        }
        printf("\n\n");
}








