#ifndef GBIB_H_INCLUDED
#define GBIB_H_INCLUDED

#define ARCHPERM "perm.txt"
#define MAX_REG 50000

#define TODO_OK 1
#define ERR_ARCH 2
#define ERR_LINEA_LARGA 3
#define TAM_MAX_LINEA 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Cmp)(const void *elem1, const void *elem2);

typedef struct
{
    int legajo;
    char nomYAp[65];
    char codSeg[513];
    float saldo;
} sCliente;

typedef struct
{
    int elem1;
    int elem2;
} sPerm;

typedef struct
{
    void *vec;
    int ce;
    size_t tamElem;
    int cap;
} Vector;

int crearLotePruebaClientes(const char *nomArchivo);
int permutarArchClientes(const char *archOri, const char *archDes);
int restaurarArchClientes(const char *archOri, const char *archDes);

int permutarArchClientesALU(const char *archOri, const char *archDes);
int restaurarArchClientesALU(const char *archOri, const char *archDes);

Vector *vectorCrear(size_t tamElem, int capIni);
void vectorDestruir(Vector *v);
void vectorClientesMostrar(Vector *v);
void vectorPermutacionesMostrar(Vector *v);

int lineaAEstructuraCliente(char *linea, sCliente *cl);
int lineaAEstructuraPermutaciones(char *linea, sPerm *per);

int despermutarVectorClientes(const char *archPer, Vector *v);
void despermutacionProcesarVectores(Vector *vCli, Vector *vPer);

void vectorClientesAArchivoTxt(const Vector *vCli, const char *archCliRestaurado);

#endif // GBIB_H_INCLUDED
