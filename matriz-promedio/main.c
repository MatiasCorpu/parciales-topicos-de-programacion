#include <stdio.h>
#include <stdlib.h>

/*
PARCIAL:

Dado un archivo de texto con campos variables separados por el carácter |, en el que cada fila representa una fila de una matriz, se requiere realizar los siguientes pasos:

Leer el archivo y cargar sus datos en una matriz dinámica teniendo en cuenta que es una matriz de 4x4.
Calcular el promedio de los elementos que se encuentran en la diagonal principal de la matriz.
Mostrar los elementos de la matriz que son mayores al promedio calculado en el paso anterior.
*/

#include "funciones.h"
// #include "funciones.c"

#define TAM_MATRIZ 4

int main()
{
    float **matriz = (float **)matrizCrear(TAM_MATRIZ, TAM_MATRIZ, sizeof(float));

    matrizArchivoTxtAMatriz("matriz.txt", matriz, TAM_MATRIZ);
    matrizMostrar(matriz, TAM_MATRIZ, TAM_MATRIZ);

    float promD = promedioDiagonalPrincipalMatriz(matriz, TAM_MATRIZ);
    printf("\n\n");

    matrizMostrarElementosMayores(matriz, TAM_MATRIZ, TAM_MATRIZ, &promD, cmpFloat);

    matrizDestruir((void **)matriz, TAM_MATRIZ);
    return 0;
}
