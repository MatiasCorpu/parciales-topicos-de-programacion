#include "funciones.h"

void **matrizCrear(int filas, int columnas, size_t tamElem)
{
    void **mat = malloc(filas * sizeof(void *));
    if (!mat)
        return NULL;

    for (int i = 0; i < filas; i++)
    {
        mat[i] = malloc(tamElem * columnas);

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

void matrizDestruir(void **matriz, int filas)
{
    for (int i = 0; i < filas; i++)
        free(matriz[i]);

    free(matriz);
}

void matrizMostrar(float **matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        printf("\n");
        for (int j = 0; j < columnas; j++)
            printf("%4.2f ", matriz[i][j]);
    }
}

int matrizArchivoTxtAMatriz(const char *nomArch, float **mat, int filCol)
{
    FILE *matTxt = fopen(nomArch, "rt");
    if (!matTxt)
        return ERR_ARCH;

    int i = 0;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, matTxt))
    {
        lineaAmemoria(mat[i++], linea, filCol);
    }

    fclose(matTxt);
    return TODO_OK;
}

int lineaAmemoria(float *filaMat, char *linea, int columnas)
{
    // 3.5|5.2|7.8|2.1\0
    char *ptr = strrchr(linea, '\n'); // remplazar
    if (!ptr)
        return ERR_LINEA_LARGA;

    int i;
    for (i = columnas - 1; i > 0; i--)
    {
        *ptr = '\0';
        ptr = strrchr(linea, '|');
        sscanf(ptr + 1, "%f", &filaMat[i]);
    }

    *ptr = '\0';
    sscanf(linea, "%f", &filaMat[i]);

    return TODO_OK;
}

float promedioDiagonalPrincipalMatriz(float **matriz, int filCol)
{
    float sum = 0;

    for (int i = 0; i < filCol; i++)
        sum += matriz[i][i];

    return sum / (float)filCol;
}

int cmpFloat(const void *a, const void *b)
{
    return ((int)(*(float *)a - *(float *)b));
}

void matrizMostrarElementosMayores(float **matriz, int filas, int columnas, void *elem, Comparar cmp)
{
    for(int i = 0; i < filas; i++)
    {
        printf("\n");
        for(int j = 0; j < columnas; j++)
        {
            if(cmp(matriz[i] + j, elem) > 0)
                printf("%4.2f ", matriz[i][j]);
            else
            printf("---- ");
        }
    }
}