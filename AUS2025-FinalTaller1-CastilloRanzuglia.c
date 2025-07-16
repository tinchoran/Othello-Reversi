#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define ROWS 8
#define COLS  8
#define blanco 'B'
#define negro 'N'
#define vacio 'V'
#define limpiar_buffer fflush(stdin)
#ifdef _WIN32
    #define BORRAR_PANTALLA() system("cls")
#else
    #define BORRAR_PANTALLA() system("clear")
#endif


void inicializarTablero(char arr[ROWS][COLS]);
void mostrarTablero(char arr[ROWS][COLS]);
void inscribirJugador(char nombre[], char *equipo, int nroJugador, char equipoJugador1);

int main(){

        char tablero[ROWS][COLS];
        //Variables para nombres y equipos de cada jugador
        char nombreJ1[25],nombreJ2[25];
        char equipoJ1 = 'V', equipoJ2  = 'V';

        // Ponemos como semilla para el rand() el id del proceso para que cambia con cada ejecución
        srand(getpid());
        // Configuramos los locales para la región del usuario. En este caso el entorno del usuario es español: permite utilizar tildes.
        setlocale(LC_ALL, "");

        inicializarTablero(tablero);
        mostrarTablero(tablero);

        inscribirJugador(nombreJ1, &equipoJ1, 1, equipoJ1);
        inscribirJugador(nombreJ2, &equipoJ2, 2, equipoJ1);
        printf("\nJugador 1: Nombre: %s\nEquipo: %c", nombreJ1, equipoJ1);
        printf("\nJugador 2: Nombre: %s\nEquipo: %c", nombreJ2, equipoJ2);
        return 0;
}


void inicializarTablero(char arr[ROWS][COLS]){
        int i,j;
        // configuracion = número aleatorio entre 0 y 1: describe la configuración inicial;0 para cruz;1 para columnas.
        int configuracion = rand() % 2;

        for(i=0; i<ROWS;i++){
                for(j=0;j<COLS;j++){
                        arr[i][j] = vacio;
                }
        }

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


void inscribirJugador(char nombre[], char *equipo, int nroJugador, char equipoJugador1){
        int equipoElegido;
        BORRAR_PANTALLA();
        printf("\n  Ingrese el nombre del jugador [%d]:  ", nroJugador);
        fgets(nombre, 25, stdin);
        limpiar_buffer;
        if(nroJugador == 1){
                printf("\n  -----------  Selección su equipo -----------");
                printf("\n  [1] - BLANCAS \n  [2] - NEGRAS");
                printf("\n  --------------------------------------------");
                printf("\n  Ingrese un número:  ");
                scanf("%d", &equipoElegido);
                limpiar_buffer;
                while(equipoElegido != 1 && equipoElegido != 2){
                        printf("\n  Opción inválida. Intente nuevamente:  ");
                        scanf("%d", &equipoElegido);
                        limpiar_buffer;
                }
                *equipo = (equipoElegido == 1) ? 'B' : 'N';
        } else {
                //Si es el segundo jugador en inscribirse, verificamos el equipo del primer jugador para asignarle automáticamente equipo
                *equipo = (equipoJugador1 == 'B') ? 'N' : 'B';
        }


}






