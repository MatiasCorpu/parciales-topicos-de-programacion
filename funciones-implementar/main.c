#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"
// #include "funciones.c"

int main()
{
    // 1.
    char s1[12] = "hola ";
    char s2[7] = "amigos";

    printf("s1=%s\ts2=%s\n", s1, s2);
    mstrcat(s1, s2);
    printf("s1=%s\n", s1);

    // 3.
    int vec[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ce = 10;
    int elem = 5;

    int *posi = (int *)mbsearch(&elem, vec, ce, sizeof(int), cmpEnteros);
    printf("posicion: %p, elemento : %d\n", posi, *posi);

    // 2.
    int filas1 = 6;
    int matriz1[MAX_FILA][MAX_FILA] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0}};

    int filas2 = 7;
    int matriz2[MAX_FILA][MAX_FILA] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0}};

    int filas3 = 8;
    int matriz3[MAX_FILA][MAX_FILA] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0}};

    int filas4 = 9;
    int matriz4[MAX_FILA][MAX_FILA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0}};

    printf("Suma trangulo: %d\n", sumTrianInfEntreDiag(matriz1, filas1));

    return 0;
}
