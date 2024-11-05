#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILAS 100
#define TAM_MAX_PAL 101

#define ES_LETRA(c) ((c >= 'a' && c <= 'z') || c >= 'A' && c <= 'Z')

typedef int (*Comparar)(const void *, const void *);

typedef struct
{
    char pal[TAM_MAX_PAL];
} Palabra;

typedef struct
{
    char *ptr;
    bool finSecPal;
} SecPal;

int cmpEnteros(const void *a, const void *b);
bool insertarOrdenado(void *v, int *ce, int cap, size_t tamElem, void *elem, Comparar cmp, const char *tipo);
void transponerMatrizCuadradaInsitu(int mat[MAX_FILAS][MAX_FILAS], int filas);

void crearSecPal(SecPal *secPal, char *s);
bool leerPalabra(SecPal *secPal, Palabra *pal);

char *mstrstr(const char *s1, const char *s2);

#endif // FUNCIONES_H_INCLUDED
