#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#define TODO_OK 0
#define ERR_MEM 1
#define ERR_ARCH 2
#define ERR_LINEA_LARGA 3

#define TAM_MAX_LINEA 200

typedef int (*Comparar)(const void *, const void *);

void **matrizCrear(int filas, int columnas, size_t tamElem);
void matrizDestruir(void **matriz, int filas);
void matrizInicializarEnCero(float **matriz, int filas, int columnas);
void matrizMostrar(float **matriz, int filas, int columnas);
int lineaAmemoria(float *filaMat, char *linea, int columnas);
int matrizArchivoTxtAMatriz(const char *nomArch, float **mat, int filCol);
float promedioDiagonalPrincipalMatriz(float **matriz, int filCol);
int cmpFloat(const void *a, const void *b);
void matrizMostrarElementosMayores(float **matriz, int filas, int columnas, void *elem, Comparar cmp); //hacer matriz recorrer

#endif // FUNCIONES_H_INCLUDED
