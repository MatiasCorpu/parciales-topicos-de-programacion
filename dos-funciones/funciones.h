#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2

#define TAM_MAX_LINEA 500
#define TAM_MAX_PALABRA 100

#define ES_LETRA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

typedef struct
{
    char palabra[TAM_MAX_PALABRA];
    int cantOcurr;
} Palabra;

typedef struct
{
    char *ptr;
    bool finSecPal;
} SecPalabra;

typedef int (*Comparar)(const void *, const void *);


//FUNCIONES PARTE 1
int mstrlen(const char *s);
char *mstrrchr(const char *s, char c);
char *mstrcpy(char *sDest, const char *sOrig);
void crearSecPalabra(char *s, SecPalabra *secPal);
bool leerPalabra(Palabra *pal, SecPalabra *secPal);
int compararPalabras(const Palabra *pal1, const Palabra *pal2);
int palabraMasLargaAparicionesYcantPalabrasArchTxt(Palabra *palLarga, char *linea, int *cantPalEnArch);
Palabra *contarPalabrasMio(const char *nomArchTxt, Palabra *pal);

/*
Parte 2-esMatrizCampeonatoValidaMio 
Se dispone de una matriz cuadrada de enteros de orden N, donde cada elemento [i][j] representa la 
cantidad de puntos que obtuvo el equipo i frente al equipo j al fin de un torneo de fútbol (partidos 
de ida y vuelta) en el que participaron N equipos. El sistema de puntuación es: 3 puntos para el 
ganador del partido y ninguno para el perdedor; 1 punto para cada equipo en caso de empate. 
Implemente la función esMatrizCampeonatoValidaMIO que determine si la matriz está 
correctamente generada.
*/

// FUCIONES PARTE 2



//posibles resultados:
/*
          river  boca   sanLor
river  =         3+1
boca   =  0+1
sanLor =  

3 = 0
1 = 1
0 = 3

 1 + 1
 1 + 1

6 - 2 = 4

3+3 = 6 ->j = 0 + 0 = 0
3+1 = 4 ->j = 0 + 1 = 1
3+0 = 3 ->j = 0 + 3 = 3
1+1 = 2 ->j = 1 + 1 = 2
0+0 = 0 ->j = 3 + 3 = 6

        0 1 2
river 0{0,6,2},
boca  1{0,0,3},
san l 2{2,3,0},



*/
#define TAM_MAX_EQUIPOS 3

void **matrizCrear(int filas, int columnas, size_t tamElem);
void matrizDestruir(void **mat, int filas);

void matrizLLenarDatosCampeonato(int **mat, int filas, int columnas, int matCampeonato[][TAM_MAX_EQUIPOS]);
void matrizMostrar(int **mat, int filas, int columnas);
bool esMatrizCampeonatoValidaMIO(const int **mat, int filCol);


int cmpEnteros(const void *a, const void *b);
void *busquedaBinaria(const void *v, int ce, size_t tamElem, const void *elem, Comparar cmp);

#endif // FUNCIONES_H_INCLUDED
