#include "funciones.h"

// PARTE 1

int cmpEnteros(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void *buscarMenor(const void *vecIni, const void *ult, size_t tamElem, Comparar cmp)
{
    const void *act = vecIni;
    const void *min = vecIni;
    act += tamElem;

    while (act <= ult)
    {
        if (cmp(act, min) < 0)
            min = act;
        act += tamElem;
    }

    return (void *)min;
}

void intercambiar(void *a, void *b, size_t tamElem)
{
    void *aux;
    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);
}

void _ordenarSeleccion(void *vec, int ce, size_t tamElem, Comparar cmp)
{
    void *pri = vec;
    void *ult = vec + tamElem * (ce - 1);
    void *posi;

    for (void *i = pri; i < ult; i += tamElem)
    {
        posi = buscarMenor(i, ult, tamElem, cmp);

        if (i != posi)
            intercambiar(i, posi, tamElem);
    }
}

// PARTE 2

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

void *matrizInicializar(int **mat, int filas, int columnas, int matIni[4][4])
{
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            mat[i][j] = matIni[i][j];

    return mat;
}

void matrizDestruir(void **mat, int filas)
{
    for (int i = 0; i < filas; i++)
        free(mat[i]);

    free(mat);
}

void matrizMostrar(int **mat, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        printf("\n");
        for (int j = 0; j < columnas; j++)
            printf("%2d ", mat[i][j]);
    }
}

int _contarCelulasVivasEnVecindario(int **mat, int fil, int col, int posFil, int posCol)
{
    int cont = 0;

    int topeSup = posFil > 0 ? (posFil - 1) : posFil;
    int topeInf = posFil < (fil - 1) ? (posFil + 1) : posFil;
    int topeIzq = posCol > 0 ? (posCol - 1) : posCol;
    int topeDer = posCol < (col - 1) ? (posCol + 1) : posCol;

    for (int i = topeSup; i <= topeInf; i++)
    {
        for (int j = topeIzq; j <= topeDer; j++)
        {
            if (!(i == posFil && j == posCol) && ((mat[i][j] == 1) || (mat[i][j] == -1)))
                cont++;
        }
    }

    return cont;
}

void matrizActualizar(int **mat, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        // puts("");
        for (int j = 0; j < columnas; j++)
        {
            int vecVivos = _contarCelulasVivasEnVecindario(mat, 4, 4, i, j);
            // printf("%d ", vecVivos);

            if (mat[i][j] == 1)
            {

                if (vecVivos < 2 || vecVivos > 3)
                    mat[i][j] = -1; // esta por morir

                else
                    mat[i][j] = 1; // sigue vivo
            }

            if (mat[i][j] == 0 && vecVivos == 3)
                mat[i][j] = 2; // esta por nacer
        }
    }

    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
        {
            if (mat[i][j] == 2)
                mat[i][j] = 1;
            else if (mat[i][j] == -1)
                mat[i][j] = 0;
        }
}

int juegoDeLaVida()
{
    int matIni[4][4] = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
    };

    int i = 0;

    int **mat = (int **)matrizCrear(4, 4, sizeof(int));
    matrizInicializar(mat, 4, 4, matIni);
    matrizMostrar(mat, 4, 4);

    while (i <= 5)
    {
        matrizActualizar(mat, 4, 4);
        puts("\n");
        matrizMostrar(mat, 4, 4);
        i++;
    }

    matrizDestruir((void **)mat, 4);
}

// PARTE 3

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

char *_mstrstr(const char *s1, const char *s2)
{
    int nCar = mstrlen(s2);

    if (nCar > mstrlen(s1))
        return NULL;

    const char *ptr = s2;

    while (*s1 != '\0' && *ptr != '\0')
    {
        if (*s1 != *ptr)
            ptr = s2;
        else
            ptr++;
        s1++;
    }

    return *ptr == '\0' ? (char *)(s1 -= nCar) : NULL;
}
