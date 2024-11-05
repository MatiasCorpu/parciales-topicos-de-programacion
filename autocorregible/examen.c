#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "examen.h"

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_LINEA_LARGA 2

#define TAM_MAX_LINEA 501

#define ES_LETRA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define A_MINUSCULA(c) (c >= 'A' && c <= 'Z' ? c + 32 : c)

typedef struct
{
    char *ptr;
} SecPalabra;

// FUNCION DE BUSQUEDA BINARIA

void *_bbinaria(const void *clave, const void *vec, size_t ce, size_t tam, int cmp(const void *, const void *))
{
    const void *izq = vec;
    const void *der = vec + tam * (ce - 1);

    const void *mid;

    while (izq <= der)
    {
        mid = izq + ((der - izq) / (2 * tam)) * tam;

        int comparacion = cmp(mid, clave);

        if (comparacion == 0)
            return (void *)mid;

        else if (comparacion < 0)
            izq = mid + tam;

        else
            der = mid - tam;
    }

    return NULL;
}

// FUNCIONES DE CONTAR PALABRAS

int mstrcmpi(const char *_Str1, const char *_Str2)
{
    while (*_Str1 != '\0' && *_Str2 != '\0')
    {
        int dif = A_MINUSCULA(*_Str1) - A_MINUSCULA(*_Str2);

        if (dif != 0)
            return dif;

        _Str1++;
        _Str2++;
    }

    return *_Str1 == '\0' && *_Str2 == '\0' ? 0 : *_Str1 == '\0' ? -1
                                                                 : 1;
}

char *mstrcpy(char *__restrict__ _Dest, const char *__restrict__ _Source)
{
    char *ptr = _Dest;
    while (*_Source != '\0')
    {
        *_Dest = *_Source;
        _Source++;
        _Dest++;
    }

    *_Dest = '\0';
    return ptr;
}

char *mstrrchr(const char *_Str, int _Ch)
{
    const char *ultApar = NULL;

    while (*_Str != '\0')
    {
        if (*_Str == _Ch)
            ultApar = _Str;

        _Str++;
    }

    return (char *)ultApar;
}

int mstrlen(const char *_Str)
{
    int n = 0;

    while (*_Str != '\0')
    {
        n++;
        _Str++;
    }

    return n;
}

void crearSecPalabras(char *s, SecPalabra *secPal)
{
    secPal->ptr = s;
}

bool leerPalabra(SecPalabra *secPal, char *pal)
{
    while (*secPal->ptr != '\0' && !ES_LETRA(*secPal->ptr))
        secPal->ptr++;

    if (*secPal->ptr == '\0')
        return false;

    while (*secPal->ptr != '\0' && ES_LETRA(*secPal->ptr))
    {
        *pal = *secPal->ptr;
        secPal->ptr++;
        pal++;
    }

    *pal = '\0';
    return true;
}

int palMasLargaYCantVeces(char *linea, char *palMasLarga, int *cantVeces, int *cPalTotal)
{
    char *sLect = mstrrchr(linea, '\n');
    if (!sLect)
        return 0;

    *sLect = '\0';

    char palabraAct[128];

    char *sEscr = palMasLarga;

    SecPalabra secLect;
    crearSecPalabras(linea, &secLect);

    while (leerPalabra(&secLect, palabraAct))
    {

        if (mstrlen(sEscr) < mstrlen(palabraAct))
        {
            // printf("%s\n", palabraAct);

            mstrcpy(sEscr, palabraAct);
            *cantVeces = 1;
        }
        else if (mstrcmpi(sEscr, palabraAct) == 0)
        {
            (*cantVeces)++;
        }

        (*cPalTotal)++;
    }

    return TODO_OK;
}

int _contarPalabras(const char *nomArc, char *palMasLarga, int *cantVeces)
{
    FILE *archTxt = fopen(nomArc, "rt");
    if (!archTxt)
    {
        printf("No se pudo abrir el archivo '%s'\n", nomArc);
        return ERR_ARCH;
    }

    int cPalTotal = 0;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, archTxt))
    {
        // printf("%s", linea);
        palMasLargaYCantVeces(linea, palMasLarga, cantVeces, &cPalTotal);
    }

    fclose(archTxt);

    return cPalTotal;
}

// FUNCIONES DE MATRIZ

int _sumTrianDerEntreDiag(int mat[][MAX_COL], int filas)
{
    int sum = 0;
    int topeMedio, topeEspejo;

    if (filas % 2 != 0)
    {
        topeMedio = (filas / 2) + 2;
        topeEspejo = (filas - 1) / 2 - 1;

        for (int j = topeMedio - 1; j < filas; j++)
            sum += mat[topeEspejo + 1][j];
    }
    else
    {
        topeMedio = (filas / 2) + 1;
        topeEspejo = (filas - 1) / 2;
    }

    for (int i = 1; i <= topeEspejo; i++)
    {
        for (int j = filas - 1; j >= filas - i; j--)
        {
            sum += mat[i][j];
            sum += mat[filas - 1 - i][j];
        }
    }

    return sum;
}

int _sumTrianInfEntreDiag(int mat[][MAX_COL], int filas)
{
    int sum = 0;
    int k = 0;
    int topeMedio, topeEspejo;

    if (filas % 2 != 0)
    {
        topeMedio = (filas / 2) + 2;
        topeEspejo = (filas - 1) / 2 - 1;

        for (int i = filas - 1; i >= topeMedio - 1; i--)
            sum += mat[i][topeEspejo + 1];
    }
    else
    {
        topeMedio = (filas / 2) + 1;
        topeEspejo = (filas - 1) / 2;
    }

    for (int i = filas - 1; i >= topeMedio; i--)
    {
        k++;
        for (int j = k; j <= topeEspejo; j++)
        {
            sum += mat[i][j];
            sum += mat[i][filas - 1 - j];
        }
    }

    return sum;
}
