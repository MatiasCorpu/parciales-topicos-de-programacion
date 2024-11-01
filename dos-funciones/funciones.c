#include "funciones.h"

// FUNCIONES PARTE 1

int mstrlen(const char *s)
{
    int cont = 0;

    while (*s != '\0')
    {
        cont++;
        s++;
    }

    return cont;
}

char *mstrrchr(const char *s, char c)
{
    const char *ultAparicion = NULL;

    while (*s != '\0')
    {
        if (*s == c)
            ultAparicion = s;

        s++;
    }

    return (char *)ultAparicion;
}

char *mstrcpy(char *sDest, const char *sOrig)
{
    char *ptrDest = sDest;

    while (*sOrig != '\0')
    {
        *ptrDest = *sOrig;
        ptrDest++;
        sOrig++;
    }
    *ptrDest = '\0';

    return sDest;
}

Palabra *contarPalabrasMio(const char *nomArchTxt, Palabra *pal)
{
    FILE *archTxt = fopen(nomArchTxt, "rt");
    if (!archTxt)
        return NULL;

    char linea[TAM_MAX_LINEA];
    pal->cantOcurr = 0;
    int cantPalabrasArchTxt = 0;

    while (fgets(linea, TAM_MAX_LINEA, archTxt))
    {
        palabraMasLargaAparicionesYcantPalabrasArchTxt(pal, linea, &cantPalabrasArchTxt);
    }

    printf("Cantidad de palabras en el archivo %s : %d", nomArchTxt, cantPalabrasArchTxt);

    fclose(archTxt);
    return pal;
}

void crearSecPalabra(char *s, SecPalabra *secPal)
{
    secPal->ptr = s;
    secPal->finSecPal = false;
}

bool leerPalabra(Palabra *pal, SecPalabra *secPal)
{
    while (*secPal->ptr != '\0' && !ES_LETRA(*secPal->ptr))
        secPal->ptr++;

    if (*secPal->ptr == '\0')
    {
        secPal->finSecPal = true;
        return false;
    }

    char *ptrPal = pal->palabra;

    while (*secPal->ptr != '\0' && ES_LETRA(*secPal->ptr))
    {
        *ptrPal = *secPal->ptr;
        secPal->ptr++;
        ptrPal++;
    }

    *ptrPal = '\0';
    return true;
}

int compararPalabras(const Palabra *pal1, const Palabra *pal2)
{
    return mstrlen(pal1->palabra) - mstrlen(pal2->palabra);
}

int palabraMasLargaAparicionesYcantPalabrasArchTxt(Palabra *palLarga, char *linea, int *cantPalEnArch)
{
    char *ptr = mstrrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    *ptr = '\0';

    SecPalabra secLect;
    crearSecPalabra(linea, &secLect);

    Palabra pal;

    while (leerPalabra(&pal, &secLect))
    {
        // printf("%s\n", pal.palabra);
        if (compararPalabras(&pal, palLarga) > 0)
        {
            mstrcpy(palLarga->palabra, pal.palabra);
            palLarga->cantOcurr = 1;
        }
        else if (compararPalabras(&pal, palLarga) == 0)
        {
            palLarga->cantOcurr++;
        }

        (*cantPalEnArch)++;
    }

    return TODO_OK;
}

// FUNCIONES PARTE 2

void **matrizCrear(int filas, int columnas, size_t tamElem)
{
    void **mat = malloc(filas * sizeof(void *));
    if (!mat)
        return NULL;

    for (int i = 0; i < filas; i++)
    {
        mat[i] = malloc(columnas * tamElem);

        if (!mat[i])
        {
            for (int j = 0; j < i; j++)
                free(mat[j]);

            free(mat);
            return NULL;
        }
    }
    return mat;
}

void matrizDestruir(void **mat, int filas)
{
    for (int i = 0; i < filas; i++)
        free(mat[i]);

    free(mat);
}

void matrizLLenarDatosCampeonato(int **mat, int filas, int columnas, int matCampeonato[][TAM_MAX_EQUIPOS])
{
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            mat[i][j] = matCampeonato[i][j];
}

void matrizMostrar(int **mat, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

bool esMatrizCampeonatoValidaMIO(const int **mat, int filCol)
{
    int puntos[6] = {0, 1, 2, 3, 4, 6};
    int cePuntos = 6;

    for (int i = 0; i < filCol - 1; i++)
    {
        for (int j = i + 1; j < filCol; j++)
        {
            if (i != j)
            {
                int *posi = (int *)busquedaBinaria(puntos, cePuntos, sizeof(int), &mat[i][j], cmpEnteros);
                if (!posi)
                    return false;

                int resulEsperado = (*posi == 2 || *posi == 3) ? *posi : puntos[(cePuntos - 1) - (posi - puntos)];

                // printf("%d ",  resulEsperado);

                if (mat[j][i] != resulEsperado)
                    return false;
            }
        }
    }

    return true;
}

int cmpEnteros(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void *busquedaBinaria(const void *v, int ce, size_t tamElem, const void *elem, Comparar cmp)
{
    const void *izq = v;
    const void *der = v + tamElem * (ce - 1);
    const void *mid;

    while (izq <= der)
    {
        mid = izq + ((der - izq) / (2 * tamElem)) * tamElem;

        if (cmp(mid, elem) == 0)
            return (void *)mid;

        else if (cmp(mid, elem) < 0)
            izq = mid + tamElem;

        else
            der = mid - tamElem;
    }

    return NULL;
}