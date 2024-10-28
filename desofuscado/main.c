#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"

int main()
{
    printf("ARCHIVO OFUSCADO:\n");
    mostrarArchivoCitasTxt("citas.txt");
    desofuscarCitasDeArchivoTxt("citas.txt");

    printf("\n\nARCHIVO DESOFUSCADO:\n");
    mostrarArchivoCitasTxt("citas.txt");

    return TODO_OK;
}
