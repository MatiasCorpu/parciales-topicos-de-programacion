#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_MAX_ENTRADAS 20
#define TAM_MAX_COD_ENTRADAS 10

typedef struct
{
    char cod[TAM_MAX_COD_ENTRADAS];
    bool usada;
} Entrada;

typedef struct
{
    void *vec;
    int ce;
    size_t tamElem;
    int cap;
} Vector;

typedef void (*Accion)(void *, void *);
void accionMostrarEntrada(void *entrada, void *extra);

typedef int (*Comparar)(const void *, const void *);
int cmpCodEntradas(const void *a, const void *b);

// ARCHIVO
void archivoEntradasGenerar(const char *nomArchEntradas);
void archivoEntradasRecorrer(const char *nomArchEntradas, Accion accion, void *datosAccion);
void archivoEntradasAMemoria_1(const char *nomArchEntradas, Vector *vec); // utilizando ftell (vec desordenado)
void archivoEntradasAMemoria_2(const char *nomArchEntradas, Vector *vec); // utilizando vectorInsertarOrdenado (vec ordenado)

// VECTOR TDA
Vector *vectorCrear(size_t tamElem, int capIni);
void vectorDestruir(Vector *vec);
void vectorRecorrer(Vector *vec, Accion accion, void *datosAccion);
void vectorInsertarOrdenado(Vector *vec, void *elem, Comparar cmp);
void vectorOrdenarInsercion(Vector *vec, Comparar cmp);
void *buscarMinimo(void *ini, void *fin, size_t tamElem, Comparar cmp);
void vectorOrdenarSeleccion(Vector *vec, Comparar cmp);
void *vectorBusquedaBinaria(Vector *vec, void *elem, Comparar cmp);

void validarEntradasYActualizar(Vector *vec);
void procesarEntradas(const char *nomArchEntradas, Vector *vec);

#endif // FUNCIONES_H_INCLUDED
