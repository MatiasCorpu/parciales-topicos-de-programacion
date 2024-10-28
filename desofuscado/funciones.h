#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#define TODO_OK 0
#define ERR_ARCH 1

#define TAM_MAX_PAL 100
#define TAM_MAX_LINEA 1025

#define ES_LETRA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

typedef struct
{
    char palabra[TAM_MAX_PAL];
} Palabra;

typedef struct
{
    char *ptr;
    bool finSecPal;
} SecuenciaPal;

typedef int (*Comparacion)(const void *, const void *);

// funcion generica
int cmpCaracter(const void *a, const void *b);
void *buscarElemento(void *vec, int ce, size_t tamElem, void *elem, Comparacion cmp);

// funcciones de desofuscar
void crearSecuenciaPal(SecuenciaPal *secPal, char *s);
bool leerPalabra(SecuenciaPal *secPal, Palabra *pal);
void cambiarletrasDeLaPalabra(Palabra *pal);
void darVueltaPalabra(Palabra *pal);
void escribirPalabra(SecuenciaPal *secPal, const Palabra *pal);
void escribirCaracter(SecuenciaPal *secPal, const char c);
void moverPunteroSecPal(SecuenciaPal *secPal, int n);
char *desofuscar(char *s);

// funciones de string
int mstrlen(const char *s);
char *mstrcpy(char *s1, const char *s2);

// funciones de archivo
void mostrarArchivoCitasTxt(const char *nomArchCitasTxt);
int desofuscarCitasDeArchivoTxt(const char *nomArchCitasTxt);

#endif // FUNCIONES_H_INCLUDED
