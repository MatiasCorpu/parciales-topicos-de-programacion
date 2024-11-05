#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX_FILA 100

typedef int (*Comparar)(const void *, const void *);

char *mstrcpy(char *s1, const char *s2);
int mstrlen(const char *s);
char *mstrcat(char *s1, const char *s2);
int cmpEnteros(const void *a, const void *b);
void *mbsearch(const void *clave, const void *base, size_t ce, size_t tamElem, Comparar cmp);
int sumTrianInfEntreDiag(int matriz[][MAX_FILA], int filas);

#endif // FUNCIONES_H_INCLUDED
