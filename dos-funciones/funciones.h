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

#define TAM_MAX_EQUIPOS 3

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

// FUNCIONES PARTE 1
int mstrlen(const char *s);
char *mstrrchr(const char *s, char c);
char *mstrcpy(char *sDest, const char *sOrig);
void crearSecPalabra(char *s, SecPalabra *secPal);
bool leerPalabra(Palabra *pal, SecPalabra *secPal);
int compararPalabras(const Palabra *pal1, const Palabra *pal2);
int palabraMasLargaAparicionesYcantPalabrasArchTxt(Palabra *palLarga, char *linea, int *cantPalEnArch);
Palabra *contarPalabrasMio(const char *nomArchTxt, Palabra *pal);

// FUNCIONES PARTE 2
void **matrizCrear(int filas, int columnas, size_t tamElem);
void matrizDestruir(void **mat, int filas);
void matrizLLenarDatosCampeonato(int **mat, int filas, int columnas, int matCampeonato[][TAM_MAX_EQUIPOS]);
void matrizMostrar(int **mat, int filas, int columnas);
bool esMatrizCampeonatoValidaMIO(const int **mat, int filCol);
int cmpEnteros(const void *a, const void *b);
void *busquedaBinaria(const void *v, int ce, size_t tamElem, const void *elem, Comparar cmp);

#endif // FUNCIONES_H_INCLUDED
