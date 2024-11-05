#include "funciones.h"

char *mstrcat(char *s1, const char *s2)
{
    int tamCad = mstrlen(s1) + mstrlen(s2) + 1;
    char *ptr1 = s1;

    char *cadTmp = (char *)malloc(tamCad * sizeof(char));
    char *ptrTmp = cadTmp;

    if (!ptrTmp)
        return NULL;

    while (*ptr1 != '\0')
    {
        *ptrTmp = *ptr1;
        ptrTmp++;
        ptr1++;
    }

    mstrcpy(ptrTmp, s2);
    mstrcpy(s1, cadTmp);

    free(cadTmp);
    return s1;
}

int mstrlen(const char *s)
{
    int n = 0;

    while (*s != '\0')
    {
        n++;
        s++;
    }
    return n;
}

char *mstrcpy(char *s1, const char *s2)
{
    char *ptr = s1;

    while (*s2 != '\0')
    {
        *ptr = *s2;
        ptr++;
        s2++;
    }
    *ptr = '\0';

    return s1;
}

void *mbsearch(const void *clave, const void *base, size_t ce, size_t tamElem, Comparar cmp)
{
    const void *izq = base;
    const void *der = base + tamElem * (ce - 1);

    const void *med;
    int comparacion;

    while (izq <= der)
    {
        med = izq + ((der - izq) / (2 * tamElem)) * tamElem;

        comparacion = cmp(med, clave);

        if (comparacion == 0)
            return (void *)med;

        else if (comparacion < 0)
            izq = med + tamElem;

        else
            der = med - tamElem;
    }

    return NULL;
}

int cmpEnteros(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int sumTrianInfEntreDiag(int matriz[][MAX_FILA], int filas)
{
    int sum = 0;
    int k = 0;

    int topeMedio = filas / 2 + 1;
    int topeEspejo = filas / 2 - 1;

    if (filas % 2 != 0)
        for (int i = topeMedio; i < filas; i++)
            sum += matriz[i][topeEspejo + 1];

    for (int i = filas - 1; i >= topeMedio; i--)
    {
        k++;
        for (int j = k; j <= topeEspejo; j++)
        {
            sum += matriz[i][j];
            sum += matriz[i][filas - j - 1];
        }
    }

    return sum;
}