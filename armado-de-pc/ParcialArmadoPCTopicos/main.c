/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************/

#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include "../SolucionParcialArmadoPCTopicos/TiposArmadoPC.h"
#include "../SolucionParcialArmadoPCTopicos/SolucionParcialArmadoPC.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

#define ERR_LINEA_LARGA 4

#define TAM_MAX_LINEA 300

int crearVector_ALU(Vector *vec, int cap, size_t tamElem);
bool redimencionarVector_ALU(Vector *vec);
void destruirVector_ALU(Vector *vec);

void mostrarVecAyR_ALU(const Vector *vec);
void mostrarVecIdx_ALU(const Vector *vec);

int lineaAestructura_ALU(ArmadoYRep *ayr, char *linea);
int cmpCodAyR_ALU(const void *a, const void *b);
int cmpCodAyrCodIdx_ALU(const void *a, const void *b);
void actCodAyRCantYPrecio_ALU(void *a, const void *b);
int insertarEnVectorOrd_ALU(Vector *v, void *elem, Cmp cmp, Actualizar actualizar);
void cargarArmadosYRepEnVector_ALU(const char *pathArmYRep, Vector *vec);
void cargarComponentesIdxEnVector_ALU(const char *pathComponentesIdx, Vector *vec);
void *buscarEnVector_ALU(Vector *vec, const void *elem, Cmp cmp);
void actualizarComponentesConVectores_ALU(const char *pathComponentes, Vector *vAyr, Vector *vIdx);
int actualizarComponentes_ALU(const char *pathComponentes, const char *pathArmadoYRep);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para m�quinas Linux
    SetConsoleCP(1252);           // Cambiar STDIN -  Para m�quinas Windows
    SetConsoleOutputCP(1252);     // Cambiar STDOUT - Para m�quinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

    puts("Componentes antes de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
    puts("");

    puts("Armados/Reparaciones:");
    mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
    puts("");

    ///*********************************************************************************************************
    // int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///******** Descomente la l�nea de abajo y comente la de arriba para probar su c�digo **********************
    int resp = actualizarComponentes_ALU(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///*********************************************************************************************************

    if (resp != TODO_OK)
    {
        puts("Error actualizando los componentes.");
        return resp;
    }

    puts("\nComponentes despues de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    //	getchar();

    return 0;
}

int actualizarComponentes_ALU(const char *pathComponentes, const char *pathArmadoYRep)
{
    Vector vecAyR;
    crearVector(&vecAyR, 50, sizeof(ArmadoYRep));
    cargarArmadosYRepEnVector_ALU(pathArmadoYRep, &vecAyR);
    // mostrarVecAyR_ALU(&vecAyR);

    Vector vecIdxC;
    crearVector(&vecIdxC, 20, sizeof(IndComponente));
    cargarComponentesIdxEnVector_ALU("Componentes.idx", &vecIdxC);
    // puts("");
    // mostrarVecIdx_ALU(&vecIdxC);

    actualizarComponentesConVectores_ALU(pathComponentes, &vecAyR, &vecIdxC);

    destruirVector_ALU(&vecIdxC);
    destruirVector_ALU(&vecAyR);
    return TODO_OK;
}

int crearVector_ALU(Vector *vec, int cap, size_t tamElem)
{
    vec->vec = malloc(cap * tamElem);
    if (!vec->vec)
        return SIN_MEM;

    vec->cap = cap;
    vec->ce = 0;
    vec->tamElem = tamElem;

    return TODO_OK;
}

bool redimencionarVector_ALU(Vector *vec)
{
    void *nVec = realloc(vec->vec, vec->cap * vec->tamElem * 2);
    if (!nVec)
        return false;

    vec->vec = nVec;
    vec->cap *= 2;

    return true;
}

void destruirVector_ALU(Vector *vec)
{
    free(vec->vec);
    vec->vec = NULL;
    vec->cap = 0;
    vec->ce = 0;
    vec->tamElem = 0;
}

void cargarArmadosYRepEnVector_ALU(const char *pathArmYRep, Vector *vec)
{
    FILE *ayp = fopen(pathArmYRep, "rt");
    if (!ayp)
        return;

    ArmadoYRep eAyR;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, ayp))
    {
        lineaAestructura_ALU(&eAyR, linea);
        insertarEnVectorOrd_ALU(vec, &eAyR, cmpCodAyR_ALU, actCodAyRCantYPrecio_ALU);
    }

    fclose(ayp);
}

int lineaAestructura_ALU(ArmadoYRep *ayr, char *linea)
{
    // 1\0
    char *ptr = strrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    // PRECIO UNITARIO
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    sscanf(ptr + 1, "%lf", &ayr->precioUnitario);

    // CANTIDAD
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    sscanf(ptr + 1, "%d", &ayr->cantidad);

    // CODIGO
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    strcpy(ayr->codigo, ptr + 1);

    // NRO OPERACION
    *ptr = '\0';
    sscanf(linea, "%d", &ayr->nroOp);

    return TODO_OK;
}

int insertarEnVectorOrd_ALU(Vector *v, void *elem, Cmp cmp, Actualizar actualizar)
{
    if (v->cap == v->ce)
        redimencionarVector_ALU(v);

    void *act = v->vec;
    void *ult = v->vec + v->tamElem * (v->ce - 1);

    while (act <= ult)
    {
        if (cmp(act, elem) == 0)
        {
            actualizar(act, elem);
            return TODO_OK;
        }

        if (cmp(act, elem) > 0)
            break;

        act += v->tamElem;
    }

    for (void *i = ult; i >= act; i -= v->tamElem)
        memcpy(i + v->tamElem, i, v->tamElem);

    memcpy(act, elem, v->tamElem);

    v->ce++;
    return TODO_OK;
}

int cmpCodAyR_ALU(const void *a, const void *b)
{
    ArmadoYRep *x = (ArmadoYRep *)a;
    ArmadoYRep *y = (ArmadoYRep *)b;

    return strcmp(x->codigo, y->codigo);
}

void actCodAyRCantYPrecio_ALU(void *a, const void *b)
{
    ArmadoYRep *x = (ArmadoYRep *)a;
    ArmadoYRep *y = (ArmadoYRep *)b;

    x->cantidad += y->cantidad;
    x->precioUnitario = y->precioUnitario;
}

void cargarComponentesIdxEnVector_ALU(const char *pathComponentesIdx, Vector *vec)
{
    FILE *cIdx = fopen(pathComponentesIdx, "rb");
    if (!cIdx)
        return;

    IndComponente *idx = (IndComponente *)vec->vec;

    while (fread(idx, vec->tamElem, 1, cIdx))
    {
        if (vec->cap == vec->ce)
            redimencionarVector_ALU(vec);

        idx++;
        vec->ce++;
    }

    fclose(cIdx);
}

void actualizarComponentesConVectores_ALU(const char *pathComponentes, Vector *vAyr, Vector *vIdx)
{
    FILE *archComp = fopen(pathComponentes, "r+b");
    if (!archComp)
        return;

    t_Componente comp;

    ArmadoYRep *ayrAct = (ArmadoYRep *)vAyr->vec;
    ArmadoYRep *ayrUlt = (ArmadoYRep *)vAyr->vec + vAyr->ce - 1;
    puts("\n");

    while (ayrAct <= ayrUlt)
    {
        IndComponente *posi = (IndComponente *)buscarEnVector_ALU(vIdx, ayrAct, cmpCodAyrCodIdx_ALU);

        if (!posi)
            return;

        fseek(archComp, posi->nroReg * sizeof(t_Componente), SEEK_SET);
        fread(&comp, sizeof(t_Componente), 1, archComp);

        comp.stock -= ayrAct->cantidad;
        comp.precioUnitario = ayrAct->precioUnitario;

        fseek(archComp, -(long)sizeof(t_Componente), SEEK_CUR);
        fwrite(&comp, sizeof(t_Componente), 1, archComp);
        fseek(archComp, 0L, SEEK_SET);

        ayrAct++;
    }

    fclose(archComp);
}

void *buscarEnVector_ALU(Vector *vec, const void *elem, Cmp cmp)
{
    void *act = vec->vec;
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);

    while (act <= ult)
    {
        if (cmp(act, elem) == 0)
            return act;

        act += vec->tamElem;
    }

    return NULL;
}

int cmpCodAyrCodIdx_ALU(const void *a, const void *b)
{
    IndComponente *x = (IndComponente *)a;
    ArmadoYRep *y = (ArmadoYRep *)b;

    return strcmp(x->codigo, y->codigo);
}

void mostrarVecAyR_ALU(const Vector *vec)
{
    ArmadoYRep *ayr = (ArmadoYRep *)vec->vec;

    for (int i = 0; i < vec->ce; i++)
        printf("%d %s %d %.2f\n", ayr[i].nroOp, ayr[i].codigo, ayr[i].cantidad, ayr[i].precioUnitario);
}

void mostrarVecIdx_ALU(const Vector *vec)
{
    IndComponente *idx = (IndComponente *)vec->vec;

    for (int i = 0; i < vec->ce; i++)
        printf("%s %d\n", idx[i].codigo, idx[i].nroReg);
}
