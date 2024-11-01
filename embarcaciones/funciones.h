#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2
#define DUPLICADO_O_ACTUALIZADO 3

#define R 6371 // Radio de la Tierra en kilómetros
#define PI 3.1415
#define TAM_MAX_LINEA 500

#define MAX_LONG_MATRICULA_EMBARCACION 20
#define MAX_CANT_EMBARCACIONES 20

typedef struct
{
    char matricula[MAX_LONG_MATRICULA_EMBARCACION];
    double latitud;
    double longitud;
    double distanciaKM;
} EmbarcacionRecorrido;

typedef struct
{
    void *vec;
    int ce;
    size_t tamElem;
    int cap;
} Vector;

typedef int (*Comparar)(const void *, const void *);
typedef void (*Actualizar)(void *, const void *);
typedef void (*Accion)(void *, void *);

Vector *vectorCrear(size_t tamELem, int capIni);
void vectorDestruir(Vector *vec);
int vectorInsertarOrdenado(Vector *vec, void *elem, Comparar cmp, Actualizar actualizar);
void vectorRecorrer(Vector *vec, Accion accion, void *datosAccion);

void actualizarDistanciaEmbarcacion(void *act, const void *datoAct);
void accionMostrarEmbarcacion(void *i, void *extra);
int cmpMatriculasEmbarcaciones(const void *a, const void *b);
int lineaAEstructura(char *linea, EmbarcacionRecorrido *emb);
int minimaDistanciaRecorridaPorEmbarcaciones(const char *archEmbarcaciones);

double haversine(double lat1, double lon1, double lat2, double lon2);

#endif // FUNCIONES_H_INCLUDED
