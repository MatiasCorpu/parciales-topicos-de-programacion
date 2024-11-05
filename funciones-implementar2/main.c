#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"
// #include "funciones.c"

int main()
{
    // 1.
    char frase[] = "las maquinas no piensan, los humanos no hacen mas que eso";
    char pal[] = "no";

    printf("%s\n\n\n", mstrstr(frase, pal));

    // 2.
    int filas2 = 7;
    int matriz2[MAX_FILAS][MAX_FILAS] = {
        {2, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0}};

    transponerMatrizCuadradaInsitu(matriz2, filas2);

    for (int i = 0; i < filas2; i++)
    {

        for (int j = 0; j < filas2; j++)
            printf("%d ", matriz2[i][j]);
        printf("\n");
    }

    // 3.
    int vec[10] = {0, 2, 3, 1, 5, 4, 7, 8, 9, 10};
    int vec2[5];
    int cap2 = 5;
    int ce2 = 0;

    for (int i = 0; i < 10; i++)
        insertarOrdenado(vec2, &ce2, cap2, sizeof(int), &vec[i], cmpEnteros, "descendente");

    printf("\n\n");
    for (int i = 0; i < ce2; i++)
        printf("%d ", vec2[i]);

    return 0;
}
