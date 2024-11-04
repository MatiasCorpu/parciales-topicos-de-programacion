#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"
// #include "funciones.c"

int main()
{
    archivoEntradasGenerar("entradasVendidas.bin");
    printf("Archivo :\n");
    archivoEntradasRecorrer("entradasVendidas.bin", accionMostrarEntrada, NULL);

    Vector *vec = vectorCrear(sizeof(Entrada), TAM_MAX_ENTRADAS);

    procesarEntradas("entradasVendidas.bin", vec);

    vectorDestruir(vec);
    return 0;
}
