#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PARTE 1
typedef int (*Comparar)(const void *, const void *);
int cmpEnteros(const void *a, const void *b);
void *buscarMenor(const void *vecIni, const void *ult, size_t tamElem, Comparar cmp);
void intercambiar(void *a, void *b, size_t tamElem);
void _ordenarSeleccion(void *vec, int ce, size_t tamElem, Comparar cmp);

// PARTE 2
void **matrizCrear(int filas, int columnas, size_t tamElem);
void *matrizInicializar(int **mat, int filas, int columnas, int matIni[4][4]);
void matrizDestruir(void **mat, int filas);
void matrizMostrar(int **mat, int filas, int columnas);
int _contarCelulasVivasEnVecindario(int **mat, int fil, int col, int posFil, int posCol);
void matrizActualizar(int **mat, int filas, int columnas);
int juegoDeLaVida();

// PARTE 3
int mstrlen(const char *s);
char *_mstrstr(const char *s1, const char *s2);

#endif // FUNCIONES_H_INCLUDED
