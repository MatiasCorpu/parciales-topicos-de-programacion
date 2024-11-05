#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minunit.h"
#include "examen.h"

#define RENDIREXAMEN

#ifdef RENDIREXAMEN
#define bbinaria _bbinaria
#define contarPalabras _contarPalabras
#define sumTrianDerEntreDiag _sumTrianDerEntreDiag
#define sumTrianInfEntreDiag _sumTrianInfEntreDiag
#endif ESALUMNO

MU_TEST(test_busquedaBinariaEnteros)
{
    int vec[] = {3, 6, 9, 12, 15, 19, 25};
    int vecValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 25, 35};
    // Funcion creada por alumno
    void *result;
    void *resultVS;
    char errorMsg[100];
    int i;
    for (i = 0; i < sizeof(vecValues) / sizeof(vecValues[0]); i++)
    {
        resultVS = bsearch(
            &vecValues[i],
            vec,
            sizeof(vec) / sizeof(vec[0]),
            sizeof(vec[0]),
            cmp_enteros);

        result = bbinaria(
            &vecValues[i],
            vec,
            sizeof(vec) / sizeof(vec[0]),
            sizeof(vec[0]),
            cmp_enteros);

        if (resultVS != result)
        {
            sprintf(errorMsg, "Error en valor %d \n", vecValues[i]);
        }

        mu_assert(resultVS == result, errorMsg);
    }
}

MU_TEST(test_busquedaBinariaEmpleados)
{
    tEmpleado *result;

    tEmpleado vec[] = {{12, "Alfredo Di Stefano", 500.0},
                       {18, "Carlos Valderrama", 300.0},
                       {3, "Eusebio", 100.1},
                       {9, "Franz Beckenbauer", 300.0},
                       {6, "Gerd Muller", 200.0},
                       {15, "Johan Cruyff", 600.0},
                       {16, "Zinedine Zidane", 200.0}};

    tEmpleado vecValues[] = {{0, "Carlos Valderrama", 0},
                             {0, "Johan Cruyff", 0},
                             {0, "Tomas Brolin", 0}};

    result = bbinaria(&vecValues[0],
                      vec,
                      sizeof(vec[0]),
                      sizeof(vec) / sizeof(vec[0]),
                      cmp_str);

    mu_assert((result->dni != 18) || (result->sueldo != 300), "Error, registro incorrecto");

    result = bbinaria(&vecValues[1],
                      vec,
                      sizeof(vec[0]),
                      sizeof(vec) / sizeof(vec[0]),
                      cmp_str);

    mu_assert((result->dni != 15) || (result->sueldo != 600), "Error, registro incorrecto");

    result = bbinaria(&vecValues[2],
                      vec,
                      sizeof(vec[0]),
                      sizeof(vec) / sizeof(vec[0]),
                      cmp_str);

    mu_assert(result != NULL, "Error, registro incorrecto");
}

MU_TEST(test_ContarPalabras)
{
    // Obtenga en una sola lectura el total de palabras,
    // la palabra mas larga y cuantas veces se repite. No hardcodee nada,
    // se probara con otro archivo. No modifique el archivo ni use
    // memorias auxiliares.
    char palMasLarga[128];
    int totalPalabras;
    int cantVeces = 0;
    char *nomArch = "frases.txt";
    crearLotePruebaTxtFrasesSim(nomArch);
    totalPalabras = contarPalabras(nomArch, palMasLarga, &cantVeces);
    mu_assert(strcmp(palMasLarga, "programacion") == 0, "palabra mas larga incorrecta");
    mu_assert(totalPalabras == 78, "cantidad de palabras incorrecta");
    mu_assert(cantVeces == 2, "cantidad de apariciones incorrecta");
    remove(nomArch);
}

MU_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales01)
{

    int suma;
    const int filas = 6;
    int mat[][MAX_COL] = {{-1, -1, -1, -1, -1, -1},
                          {-1, -1, -1, -1, -1, -1},
                          {-1, -1, -1, -1, -1, -1},
                          {-1, -1, -1, -1, -1, -1},
                          {-1, -1, 10, 10, -1, -1},
                          {-1, 10, 10, 10, 10, -1}};

    suma = sumTrianInfEntreDiag(mat, filas);
    mu_assert(suma == 60, "Error en suma de matriz");
}

MU_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales02)
{

    int suma;
    const int filas = 2;
    int mat[][MAX_COL] = {{-1, -1},
                          {-1, -1}};

    suma = sumTrianInfEntreDiag(mat, filas);
    mu_assert(suma == 0, "Error en suma de matriz");
}

MU_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales03)
{

    int suma;
    const int filas = 1;
    int mat[][MAX_COL] = {{-1}};
    suma = sumTrianInfEntreDiag(mat, filas);
    mu_assert(suma == 0, "Error en suma de matriz");
}

MU_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales01)
{

    int suma;
    const int filas = 6;
    int mat[][MAX_COL] = {{-1, -1, -1, -1, -1, -1},
                          {-1, -1, -1, -1, -1, 10},
                          {-1, -1, -1, -1, 10, 10},
                          {-1, -1, -1, -1, 10, 10},
                          {-1, -1, -1, -1, -1, 10},
                          {-1, -1, -1, -1, -1, -1}};

    suma = sumTrianDerEntreDiag(mat, filas); // Es cuadrada
    mu_assert(suma == 60, "Error en suma de matriz");
}

MU_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales02)
{

    int suma;
    const int filas = 7;
    int mat[][MAX_COL] = {{-1, -1, -1, -1, -1, -1, -1},
                          {-1, -1, -1, -1, -1, -1, 10},
                          {-1, -1, -1, -1, -1, 10, 10},
                          {-1, -1, -1, -1, 10, 10, 10},
                          {-1, -1, -1, -1, -1, 10, 10},
                          {-1, -1, -1, -1, -1, -1, 10},
                          {-1, -1, -1, -1, -1, -1, -1}};

    suma = sumTrianDerEntreDiag(mat, filas);
    mu_assert(suma == 90, "Error en suma de matriz");
}

MU_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales03)
{

    int suma;
    const int filas = 2;
    int mat[][MAX_COL] = {{-1, -1},
                          {-1, -1}

    };

    suma = sumTrianDerEntreDiag(mat, filas);
    mu_assert(suma == 0, "Error en suma de matriz");
}

MU_TEST_SUITE(test_suite)
{

    MU_RUN_TEST(test_busquedaBinariaEnteros);
    MU_RUN_TEST(test_busquedaBinariaEmpleados);

    MU_RUN_TEST(test_ContarPalabras);

    MU_RUN_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales01);
    MU_RUN_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales02);
    MU_RUN_TEST(test_sumarMatrizTrianguloInferiorEntreDiagonales03);

    MU_RUN_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales01);
    MU_RUN_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales02);
    MU_RUN_TEST(test_sumarMatrizTrianguloDerechoEntreDiagonales03);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
