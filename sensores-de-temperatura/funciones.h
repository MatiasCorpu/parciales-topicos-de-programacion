#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2

#define TAM_MAX_LINEA 300
#define REG_MAX 50
#define SENSORES_MAX 20

#define CAMPO_COD_SENSOR 8
#define CAMPO_TEMPERATURA 6
#define CAMPO_ESTADO 12

#define ES_ESPACIO(c) (c == ' ')

typedef int (*Comparar)(const void *, const void *);

typedef struct
{
    char codSensor[CAMPO_COD_SENSOR];
    float temperatura;
    char estado[CAMPO_ESTADO];
} Sensores;

typedef struct
{
    void *vec;
    int ce;
    size_t tamElem;
    int cap;
} Vector;

Vector *vectorCrear(size_t tamElem, int capIni);
void vectorDesctruir(Vector *v);
char *borrarEspaciosIzq(char *s);
int cargarLineaAEstructura(Sensores *sen, char *linea);
int cmpSensores(const void *a, const void *b);
void vectorInsertarOrdenado(Vector *v, void *elem, Comparar cmp);
int procesarVectorArch(Vector *vArch, Vector *vInf);
void vectorInformeMostrar(Vector *v);

int informeSensores(const char *nomArch);

#endif // FUNCIONES_H_INCLUDED
