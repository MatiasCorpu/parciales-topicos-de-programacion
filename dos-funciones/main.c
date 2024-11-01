#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"
// #include "funciones.c"

int main()
{
    printf("PARTE 1:\n\n");
    Palabra pal;
    contarPalabrasMio("archivo.txt", &pal);
    printf("\nPalabras mas larga: %s\nCantidad de apariciones: %d", pal.palabra, pal.cantOcurr);

    printf("\n\n\nPARTE 2:\n\n");
    int **mat = (int **)matrizCrear(TAM_MAX_EQUIPOS, TAM_MAX_EQUIPOS, sizeof(int));

    int matCamp[TAM_MAX_EQUIPOS][TAM_MAX_EQUIPOS] = {
        {0, 6, 2},
        {0, 0, 3},
        {2, 3, 0},
    };

    matrizLLenarDatosCampeonato(mat, TAM_MAX_EQUIPOS, TAM_MAX_EQUIPOS, matCamp);
    matrizMostrar(mat, TAM_MAX_EQUIPOS, TAM_MAX_EQUIPOS);

    printf("%s", esMatrizCampeonatoValidaMIO((const int **)mat, TAM_MAX_EQUIPOS) == true ? "campeonato valido" : "campeonato invalido");

    matrizDestruir((void **)mat, TAM_MAX_EQUIPOS);
    return TODO_OK;
}
