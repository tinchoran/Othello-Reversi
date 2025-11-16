# ⚪⚫ Othello (Reversi)
Un proyecto desarrollado como trabajo práctico para la materia **Taller de Programación I**, de la carrera **Analista Universitario en Sistemas**. Este programa implementa el clásico juego Othello (también conocido como Reversi) utilizando únicamente C estándar y la consola.

## 🎮 Características Principales
- ✔️ Tablero dinámico de **8x8**
- ✔️ Selección de nombres y equipos (Blancas / Negras)
- ✔️ Sorteo automático de primer movimiento
- ✔️ Detección completa de movimientos válidos en las 8 direcciones
- ✔️ Volteo de fichas según reglas oficiales
- ✔️ Conteo automático de fichas
- ✔️ Detección de fin de partida (sin movimientos disponibles)
- ✔️ Posibilidad de volver a jugar con los mismos jugadores
- ✔️ Compatible con **Windows** y **Linux**

## 🧠 Lógica del Juego
- Un movimiento es válido si al colocar una ficha se capturan piezas del rival en **cualquier dirección**.
- La captura se produce cuando hay una o más fichas del rival seguidas de una ficha propia.
- Si un jugador no tiene movimientos válidos, **pasa el turno automáticamente**.
- Si ningún jugador tiene movimientos disponibles, **la partida termina**.

## 🗂️ Estructura del código
### Funciones principales
- `inscribirJugador` → Guarda nombre y equipo
- `sortearTurnos` → Decide quién empieza
- `mostrarTablero` → Imprime el tablero en la consola
- `inicializarTablero` → Dos configuraciones iniciales posibles
- `ejecutarJuego` → Bucle principal del juego
- `hayMovimientosValidos` → Revisa si el jugador puede mover
- `mostrarMovimientos` → Señala en el tablero las casillas válidas (`x`)
- `validarMovimiento` → Comprueba que el usuario ingrese una jugada válida
- `ejecutarMovimiento` → Realiza el movimiento solicitado por el usuario y voltea las fichas correspondientes
- `contarCasillas` → Cuenta fichas por color

## 🖥️ Ejecución
Se necesita un compilador para compilar el archivo .c y obtener un .exe.
En este caso se explica cómo compilarlo con el compilador gcc
### Compilar el programa:
```bash
gcc othello.c -o othello
```
### Ejecutar
```
./othello
```
### En Windows (cmd)
```
gcc othello.c -o othello
othello.exe
```
### En Windows (powershell)
```
gcc othello.c -o othello
./othello.exe
```

## 📸 Interfaz (modo consola)
```

               Mueven las NEGRAS

          02 Blancas        02 Negras

    x   C0   C1   C2   C3   C4   C5   C6   C7

   F0    -    -    -    -    -    -    -    -

   F1    -    -    -    -    -    -    -    -

   F2    -    -    -    x    -    -    -    -

   F3    -    -    x    B    N    -    -    -

   F4    -    -    -    N    B    x    -    -

   F5    -    -    -    -    x    -    -    -

   F6    -    -    -    -    -    -    -    -

   F7    -    -    -    -    -    -    -    -

                   Movimientos

  (0)F2C3 (1)F3C2 (2)F4C5 (3)F5C4

  Ingrese el número de movimiento:
```

## 🏁 Fin de la partida
Cuando no quedan **movimientos posibles**:
- Se muestra la composición final del tablero
- Se anuncia el ganador
- Si ambos tienen la misma cantidad: **empate**
- Pregunta si se quiere volver a jugar

### Ejemplo de la vista final:
```


    x   C0   C1   C2   C3   C4   C5   C6   C7

   F0    B    B    B    N    N    N    N    B

   F1    B    B    B    N    N    N    N    B

   F2    B    B    N    N    B    N    N    B

   F3    B    B    B    N    N    N    B    B

   F4    B    B    B    B    B    B    N    B

   F5    B    B    B    N    B    N    B    B

   F6    B    N    N    B    N    B    N    B

   F7    N    N    N    N    N    N    N    N



   Cantidad de fichas del equipo BLANCO: 34
   Cantidad de fichas del equipo NEGRO: 30
   ¡El ganador es Juan!


   ¿Desea jugar otra vez con los mismos jugadores? (s/n):
```

## 📌 Requisitos
- Compilador compatible con C11
- Windows / Linux

## 📚 Notas
- El tablero puede inicializarse de dos formas distintas (modo clásico o “columnas”), elegidas al azar.
- `MAX_MOVS = 33` representa el máximo de movimientos posibles para cualquier turno (valor calculado para evitar overflow).

## 🧑‍💻 Autor
Proyecto desarrollado por [Martín Ranzuglia](https://martinranzuglia.vercel.app/es) como parte del Trabajo Práctico Final de Taller de Programación I (UNR).