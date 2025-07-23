#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


#define ROWS 8
#define COLS  8
#define blanco 'B'
#define negro 'N'
#define vacio 'V'
#define MAX_MOVS 33      //La cantidad máxima de movimientos que puede llegar a tener un jugador en un turno
#ifdef _WIN32
    #define BORRAR_PANTALLA() system("cls")
    #include <windows.h>
#else
    #define BORRAR_PANTALLA() system("clear")
    #include <unistd.h>
#endif


void esperar_segundos(int segundos){
#ifdef _WIN32
        Sleep(segundos *  1000);
#else
        sleep(segundos);
#endif
}
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void inicializarTablero(char arr[ROWS][COLS]);
void mostrarTablero(char arr[ROWS][COLS]);
void inscribirJugador(char nombre[], char *equipo, int nroJugador, char equipoJugador1);
char sortearTurnos();
void ejecutarJuego(char tablero[ROWS][COLS], char nombreJ1[], char nombreJ2[], char equipoJ1, char equipoJ2, char equipoQueInicia);
int hayMovimientosValidos(char tablero[ROWS][COLS], char jugador);
int contarCasillas(char tablero[ROWS][COLS], char equipo);
void mostrarMovimientos(char tablero[ROWS][COLS], char equipo, int posiblesMovimientos[MAX_MOVS][2]);
int validarMovimiento(int movimiento, int posiblesMovimientos[MAX_MOVS][2]);
void ejecutarMovimiento(int movFila, int movColumna, int posiblesMovimientos[MAX_MOVS][2], char tablero[ROWS][COLS], char equipo);

int main(){
        int i ;
        char tablero[ROWS][COLS];
        //Variables para nombres y equipos de cada jugador
        char nombreJ1[25],nombreJ2[25];
        char equipoJ1 = vacio, equipoJ2  = vacio;
        char inicia;
        char opcion;
        // Ponemos como semilla para el rand() el id del proceso para que cambia con cada ejecución
        srand(getpid());
        // Configuramos los locales para la región del usuario. En este caso el entorno del usuario es español: permite utilizar tildes.
        setlocale(LC_ALL, "");

        //Solicitar nombres y equipos de los jugadores
        inscribirJugador(nombreJ1, &equipoJ1, 1, equipoJ1);
        inscribirJugador(nombreJ2, &equipoJ2, 2, equipoJ1);

        do{
                BORRAR_PANTALLA();

                inicializarTablero(tablero);
                //Sortear equipo que inicia
                inicia = sortearTurnos();


                for(i=7;i>=1;i--){
                        BORRAR_PANTALLA();
                        printf("\n\n   -----------------   Jugadores   -----------------");
                        printf("\n\n   [1] %-25s   %s  ", nombreJ1, (equipoJ1 == blanco)?"BLANCAS":"NEGRAS");
                        printf("\n\n   [2] %-25s   %s  ", nombreJ2, (equipoJ2 == blanco)?"BLANCAS":"NEGRAS");
                        printf("\n\n   -------------------------------------------------");
                        printf("\n\n   Empiezan moviendo las %s", (inicia==blanco)?"BLANCAS":"NEGRAS");
                        printf("\n\n   El juego empieza en %d segundos", i);
                        esperar_segundos(1);
                }

                ejecutarJuego(tablero, nombreJ1, nombreJ2, equipoJ1, equipoJ2, inicia);
                printf("\n\n\n   ¿Desea jugar otra vez con los mismos jugadores? (s/n): ");
                opcion = getchar();
                limpiarBuffer();

        } while (opcion == 'S' || opcion == 's');


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
        printf("\n\n  ");
        printf("  ");
        printf("x   C0   C1   C2   C3   C4   C5   C6   C7    ");
        for(i=0;i<ROWS;i++){
                printf("\n\n");
                for(j=0;j<COLS;j++){
                        (j==0)?printf("   F%d  ",i):printf("");
                        (arr[i][j] == 'V')?printf("  -  ", arr[i][j]):printf("  %c  ", arr[i][j]);
                }
        }
        printf("\n\n");
}


void inscribirJugador(char nombre[], char *equipo, int nroJugador, char equipoJugador1){
        int equipoElegido;
        printf("\n\n   ---------------  JUGADOR %d   ---------------", nroJugador);
        printf("\n\n   Nombre: ", nroJugador);
        fgets(nombre, 50, stdin);
        nombre[strcspn(nombre, "\n")] = 0;


        //limpiarBuffer();
        if(nroJugador == 1){
                printf("\n   -----------  Selección su equipo -----------");
                printf("\n\n        [1] - BLANCAS     [2] - NEGRAS");
                printf("\n\n   --------------------------------------------");
                printf("\n\n   Ingrese un número: ");
                scanf("%d", &equipoElegido);
                limpiarBuffer();
                while(equipoElegido != 1 && equipoElegido != 2){
                        printf("\n   Opción inválida. Intente nuevamente: ");
                        scanf("%d", &equipoElegido);
                        limpiarBuffer();
                }
                *equipo = (equipoElegido == 1) ? blanco: negro;
        } else {
                //Si es el segundo jugador en inscribirse, verificamos el equipo del primer jugador para asignarle automáticamente equipo
                *equipo = (equipoJugador1 == blanco) ? negro : blanco;
        }

}

char sortearTurnos(){
        int turno = rand() % 2;
        return (turno == 0)?blanco:negro;
}

void ejecutarJuego(char tablero[8][8], char nombreJ1[],  char nombreJ2[], char equipoJ1, char equipoJ2, char equipoQueInicia){
        int gameOver = 0;
        char turno = equipoQueInicia;
        char rival = (turno == blanco)?negro:blanco;
        int cantFichasTurno  = 0, cantFichasRival = 0;
        char ganador, perdedor;
        int movimiento;
        int movFila,movCol;
        int posiblesMovimientos[MAX_MOVS][2];

        while(!gameOver){

                BORRAR_PANTALLA();

                if(hayMovimientosValidos(tablero, turno)){
                        (turno == blanco)?printf("\n               Mueven las BLANCAS\n"):printf("\n               Mueven las NEGRAS\n");
                        printf("\n          %02d Blancas        %02d Negras", contarCasillas(tablero, blanco), contarCasillas(tablero, negro));
                        mostrarMovimientos(tablero, turno, posiblesMovimientos);

                        //Solicitar y validar movimiento del usuario
                        printf("\n\n  Ingrese el número de movimiento: ");
                        scanf("%d", &movimiento);
                        limpiarBuffer();
                        while(!validarMovimiento(movimiento, posiblesMovimientos)){
                                printf("\n  Opción Inválida. Reintente: ");
                                scanf("%d", &movimiento);
                                limpiarBuffer();
                        }
                        movFila = posiblesMovimientos[movimiento][0];
                        movCol = posiblesMovimientos[movimiento][1];
                        ejecutarMovimiento(movFila, movCol, posiblesMovimientos, tablero, turno);
                } else {
                        mostrarTablero(tablero);
                        printf("\n\n   Las %s no tiene movimientos válidos", (turno == blanco)?"BLANCAS":"NEGRAS");
                        printf("\n   Presione ENTER para pasar el turno");
                        getchar();
                        limpiarBuffer();
                }


                if( !(hayMovimientosValidos(tablero, turno)) && !(hayMovimientosValidos(tablero, rival)) ){
                        cantFichasTurno = contarCasillas(tablero, turno);
                        cantFichasRival = contarCasillas(tablero, rival);
                        BORRAR_PANTALLA();

                        mostrarTablero(tablero);
                        printf("\n\n   ");
                        if(cantFichasTurno == cantFichasRival){
                                printf("Ambos equipos tienen %d fichas", cantFichasTurno);
                                printf("\n   El resultado es un EMPATE");
                        } else if (cantFichasTurno > cantFichasRival){
                                ganador = turno;
                                perdedor  = rival;
                                printf("Cantidad de fichas del equipo BLANCO: %d", (ganador == blanco)?cantFichasTurno:cantFichasRival);
                                printf("\n   ");
                                printf("Cantidad de fichas del equipo NEGRO: %d", (ganador == blanco)?cantFichasRival:cantFichasTurno);
                                printf("\n   ");
                                printf("¡El ganador es %s!", (ganador == equipoJ1)?nombreJ1:nombreJ2);
                        } else if  (cantFichasRival > cantFichasTurno){
                                ganador = rival;
                                perdedor = turno;
                                printf("Cantidad de fichas del equipo BLANCO: %d", (ganador == blanco)?cantFichasRival:cantFichasTurno);
                                printf("\n   ");
                                printf("Cantidad de fichas del equipo NEGRO:  %d", (ganador == blanco)?cantFichasTurno:cantFichasRival);
                                printf("\n\n   ");
                                printf("         ¡El ganador es %s!", (ganador == equipoJ1)?nombreJ1:nombreJ2);
                        }

                        gameOver = 1;

                } else {

                        turno = (turno == blanco)?negro:blanco;
                        rival = (turno == blanco)?negro:blanco;

                }

        }

}

int hayMovimientosValidos(char tablero[ROWS][COLS], char jugador) {
    char rival = (jugador == blanco) ? negro : blanco;

    for (int fila = 0; fila < 8; fila++) {
        for (int col = 0; col < 8; col++) {

            if (tablero[fila][col] != vacio) continue; // Solo buscamos en casillas vacías

            // ----------- NORTE -----------
            int f = fila - 1;
            int c = col;
            int atrapadas = 0;
            while (f >= 0 && tablero[f][c] == rival) {
                atrapadas++;
                f--;
            }
            if (atrapadas > 0 && f >= 0 && tablero[f][c] == jugador) return 1;

            // ----------- SUR -----------
            f = fila + 1;
            c = col;
            atrapadas = 0;
            while (f < 8 && tablero[f][c] == rival) {
                atrapadas++;
                f++;
            }
            if (atrapadas > 0 && f < 8 && tablero[f][c] == jugador) return 1;

            // ----------- ESTE -----------
            f = fila;
            c = col + 1;
            atrapadas = 0;
            while (c < 8 && tablero[f][c] == rival) {
                atrapadas++;
                c++;
            }
            if (atrapadas > 0 && c < 8 && tablero[f][c] == jugador) return 1;

            // ----------- OESTE -----------
            f = fila;
            c = col - 1;
            atrapadas = 0;
            while (c >= 0 && tablero[f][c] == rival) {
                atrapadas++;
                c--;
            }
            if (atrapadas > 0 && c >= 0 && tablero[f][c] == jugador) return 1;

            // ----------- NOROESTE -----------
            f = fila - 1;
            c = col - 1;
            atrapadas = 0;
            while (f >= 0 && c >= 0 && tablero[f][c] == rival) {
                atrapadas++;
                f--;
                c--;
            }
            if (atrapadas > 0 && f >= 0 && c >= 0 && tablero[f][c] == jugador) return 1;

            // ----------- NORESTE -----------
            f = fila - 1;
            c = col + 1;
            atrapadas = 0;
            while (f >= 0 && c < 8 && tablero[f][c] == rival) {
                atrapadas++;
                f--;
                c++;
            }
            if (atrapadas > 0 && f >= 0 && c < 8 && tablero[f][c] == jugador) return 1;

            // ----------- SUROESTE -----------
            f = fila + 1;
            c = col - 1;
            atrapadas = 0;
            while (f < 8 && c >= 0 && tablero[f][c] == rival) {
                atrapadas++;
                f++;
                c--;
            }
            if (atrapadas > 0 && f < 8 && c >= 0 && tablero[f][c] == jugador) return 1;

            // ----------- SURESTE -----------
            f = fila + 1;
            c = col + 1;
            atrapadas = 0;
            while (f < 8 && c < 8 && tablero[f][c] == rival) {
                atrapadas++;
                f++;
                c++;
            }
            if (atrapadas > 0 && f < 8 && c < 8 && tablero[f][c] == jugador) return 1;
        }
    }

    return 0; // No hay ningún movimiento válido
}


int contarCasillas(char tablero[ROWS][COLS], char equipo){
        int cant = 0,i,j;
        for(i=0;i<ROWS;i++){
                for(j=0;j<COLS;j++){
                        if(tablero[i][j] == equipo){
                                cant++;
                        }
                }
        }
        return cant;
}



void  mostrarMovimientos(char tablero[ROWS][COLS], char equipo, int posiblesMovimientos[MAX_MOVS][2]){
        char copiaTablero[ROWS][COLS];
        int i,j;

        //Copiar tablero
        for(i=0;i<ROWS;i++){for(j=0;j<COLS;j++){copiaTablero[i][j] = tablero[i][j];}};

        //Reseteamos el array de posibles movimientos
        int contadorDeMovimientos = 0;
        for(i=0;i<MAX_MOVS;i++){for(j=0;j<2;j++){ posiblesMovimientos[i][j] = -1;}};

        //Vectores de direcciones que nos servirán para movernos por el tablero al analizar cada celda
        int vf[8] = { 0,-1,-1,-1,0,1,1,1 };   // O = 0   NO=N=NE= -1   E = 0   SE=S=SO = -1
        int vc[8] = {-1,-1,0,1,1,1,0,-1};   // O=NO= -1  N=0   NE=E=1   SE=1 S=0 SO= -1
        int d;
        int fila=0, columna=0, atrapadas = 0;
        char rival = (equipo == blanco)?negro:blanco;


        for(i=0;i<ROWS;i++){
                for(j=0;j<COLS;j++){
                        //Recorremos todas las celdas del tablero

                        //Solo nos sirven las celdas vacías
                        if(tablero[i][j] == vacio){

                                for(d=0;d<8;d++){
                                        //Una vez confirmado que la celda es vacía, analizamos en todas las direcciones
                                        //Como las direcciones son 8 (ONO,N,NE,E,SE,S,SO), ejecutamos 8 ciclos, uno por cada índice de los vectores de direcciones

                                        //Al principio de cada ciclo...
                                        // 1 - Sacamos las coordenadas de una celda contigua a la que analizamos usando los vectores de direcciones
                                        fila = i + vf[d];
                                        columna = j + vc[d];
                                        // 2 - Reiniciamos las fichas atrapadas para evitar conflictos
                                        atrapadas = 0;

                                        //Si el tablero lo permite y la celda en la que estamos parados es del rival nos seguimos moviendo utilizando los vectores de direcciones
                                        // hasta encontrar una ficha del equipo con turno actual o hasta que se termine el tablero
                                        while ((fila >= 0 && fila <= 7 ) && ( columna >= 0 && columna <= 7) && tablero[fila][columna] == rival) {
                                                atrapadas++;
                                                fila = fila + vf[d];
                                                columna = columna + vc[d];
                                        }
                                        if (atrapadas > 0 && fila >= 0 && fila < ROWS && columna >= 0 && columna < COLS && tablero[fila][columna] == equipo) {
                                                copiaTablero[i][j] = 'x';
                                                posiblesMovimientos[contadorDeMovimientos][0] = i;
                                                posiblesMovimientos[contadorDeMovimientos][1] = j;
                                                contadorDeMovimientos++;

                                                break; //Salimos del for para no repetir el movimiento. Si no está este break por cada camino distinto que encuentre con  esta celda creará un movimiento, entonces habrá movimientos repetidos
                                        };
                                }
                        }
                }
        }

        mostrarTablero(copiaTablero);
        i=0;
        printf("                   Movimientos\n");
        while(i < MAX_MOVS && posiblesMovimientos[i][0] != -1){
                (i % 5  == 0)?printf("\n "):printf("");
                printf(" (%d)F%dC%d", i, posiblesMovimientos[i][0], posiblesMovimientos[i][1]);
                i++;
        }

}


int validarMovimiento(int movimiento,int posiblesMovimientos[MAX_MOVS][2]){
        int i=0,numeroMayorMov=-1;
        while(i < MAX_MOVS){
                if(posiblesMovimientos[i][0] != -1){
                        numeroMayorMov++;
                }
                i++;
        }
        if(movimiento >= 0 && movimiento <= numeroMayorMov){
                return 1;
        } else {
                return 0;
        }
}

void ejecutarMovimiento(int movFila, int movColumna, int posiblesMovimientos[MAX_MOVS][2], char tablero[ROWS][COLS], char equipo){
        //Vectores de direcciones que nos servirán para movernos por el tablero al analizar cada celda
        int vf[8] = { 0,-1,-1,-1,0,1,1,1 };   // O = 0   NO=N=NE= -1   E = 0   SE=S=SO = -1
        int vc[8] = {-1,-1,0,1,1,1,0,-1};   // O=NO= -1  N=0   NE=E=1   SE=1 S=0 SO= -1
        int i;
        int fila, columna, atrapadas = 0;
        char rival = (equipo == blanco)?negro:blanco;
        for(i=0;i<8;i++){
                atrapadas = 0;
                fila = movFila + vf[i];
                columna = movColumna + vc[i];
                while ((fila >= 0 && fila <= 7 ) && ( columna >= 0 && columna <= 7) && tablero[fila][columna] == rival) {
                        atrapadas++;
                        fila+=vf[i];
                        columna+=vc[i];
                }
                if (atrapadas > 0 && fila >= 0 && fila < ROWS && columna >= 0 && columna < COLS && tablero[fila][columna] == equipo) {
                        tablero[movFila][movColumna] = equipo;

                        while(atrapadas >= 0){
                                tablero[fila][columna] = equipo;
                                fila-= vf[i];
                                columna-=vc[i];
                                atrapadas--;
                        }
                };

        }


}
