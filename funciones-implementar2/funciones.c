#include "funciones.h"

bool insertarOrdenado(void *v, int *ce, int cap, size_t tamElem, void *elem, Comparar cmp, const char *tipo)
{
    bool asc = strcmpi(tipo, "ASCENDENTE") == 0 ? true : false;

    void *act = v;
    void *ult = v + tamElem * ((*ce) - 1);

    int comparacion;

    if (cap == (*ce))
        if (asc)
        {
            comparacion = cmp(ult, elem);

            if (asc == comparacion > 0)
            {
                memcpy(ult, elem, tamElem);
                return false; // perdida de dato
            }
            else if (comparacion < 0)
                return false; // no se inserta elemento
        }
        else
            ult -= tamElem;

    while (act <= ult)
    {
        comparacion = cmp(act, elem);

        if (asc == true ? (comparacion > 0) : (comparacion < 0))
            break;

        act += tamElem;
    }

    for (void *i = ult; i >= act; i -= tamElem)
        memcpy(i + tamElem, i, tamElem);

    memcpy(act, elem, tamElem);

    cap == (*ce) ? *ce : (*ce)++;
    return true;
}

int cmpEnteros(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void transponerMatrizCuadradaInsitu(int mat[MAX_FILAS][MAX_FILAS], int filas)
{
    int aux;

    for (int i = 0; i < filas - 1; i++)
    {
        for (int j = filas - 1; j > i; j--)
        {
            aux = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = aux;
        }
    }
}

void crearSecPal(SecPal *secPal, char *s)
{
    secPal->ptr = s;
    secPal->finSecPal = false;
}

bool leerPalabra(SecPal *secPal, Palabra *pal)
{
    while (*secPal->ptr != '\0' && !ES_LETRA(*secPal->ptr))
        secPal->ptr++;

    if (*secPal->ptr == '\0')
    {
        secPal->finSecPal = true;
        return false;
    }

    char *palAct = pal->pal;

    while (*secPal->ptr != '\0' && ES_LETRA(*secPal->ptr))
    {
        *palAct = *secPal->ptr;
        palAct++;
        secPal->ptr++;
    }

    *palAct = '\0';

    return true;
}

char *mstrstr(const char *s1, const char *s2)
{

    int tamS1 = strlen(s1);
    int tamS2 = strlen(s2);

    if (tamS2 > tamS1)
        return NULL;

    SecPal secLect;
    crearSecPal(&secLect, (char *)s1);

    Palabra pal;

    while (leerPalabra(&secLect, &pal))
    {
        // printf("%s\n", pal.pal);
        if (strcmp(pal.pal, s2) == 0)
            return secLect.ptr - tamS2;
    }

    return NULL;
}