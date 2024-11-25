#include "gbib.h"

int permutarArchClientesALU(const char *archOri, const char *archDes)
{
    return TODO_OK;
}

int restaurarArchClientesALU(const char *archOri, const char *archDes)
{
    FILE *archPermutado = fopen(archOri, "rt");
    if (!archPermutado)
        return ERR_ARCH;

    Vector *vecCli = vectorCrear(sizeof(sCliente), MAX_REG);
    sCliente *ptrVecCli = (sCliente *)vecCli->vec;

    sCliente cl;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, archPermutado))
    {
        lineaAEstructuraCliente(linea, &cl);
        *ptrVecCli = cl;
        ptrVecCli++;
        vecCli->ce++;
    }

    vectorClientesMostrar(vecCli);

    despermutarVectorClientes(ARCHPERM, vecCli);

    vectorClientesAArchivoTxt(vecCli, archDes);

    fclose(archPermutado);
    vectorDestruir(vecCli);
    return TODO_OK;
}

Vector *vectorCrear(size_t tamElem, int capIni)
{
    Vector *vec = malloc(sizeof(Vector));
    if (!vec)
        return NULL;

    vec->vec = malloc(tamElem * capIni);
    if (!vec->vec)
    {
        free(vec);
        return NULL;
    }

    vec->cap = capIni;
    vec->ce = 0;
    vec->tamElem = tamElem;

    return vec;
}

void vectorDestruir(Vector *v)
{
    free(v->vec);
    free(v);
}

void vectorClientesMostrar(Vector *v)
{
    sCliente *c = v->vec;

    for (int i = 0; i < v->ce; i++)
        printf("%d %s %s %.2f\n", c[i].legajo, c[i].nomYAp, c[i].codSeg, c[i].saldo);
}

int lineaAEstructuraCliente(char *linea, sCliente *cl)
{
    char *ptr = strrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    // SALDO
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    sscanf(ptr + 1, "%f", &cl->saldo);

    // COD SEG
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    strcpy(cl->codSeg, ptr + 1);

    // NOM AP
    *ptr = '\0';
    ptr = strrchr(linea, '|');
    strcpy(cl->nomYAp, ptr + 1);

    // LEGAJO
    *ptr = '\0';
    sscanf(linea, "%d", &cl->legajo);

    return TODO_OK;
}

int despermutarVectorClientes(const char *archPer, Vector *v)
{
    FILE *arch = fopen(archPer, "rt");
    if (!arch)
        return ERR_ARCH;

    sPerm per;
    char linea[TAM_MAX_LINEA];

    Vector *vecPer = vectorCrear(sizeof(sPerm), MAX_REG);
    sPerm *ptrVecPer = vecPer->vec;

    while (fgets(linea, TAM_MAX_LINEA, arch))
    {
        lineaAEstructuraPermutaciones(linea, &per);
        *ptrVecPer = per;
        ptrVecPer++;
        vecPer->ce++;
    }
    fclose(arch);

    despermutacionProcesarVectores(v, vecPer);

    vectorDestruir(vecPer);
    return TODO_OK;
}

int lineaAEstructuraPermutaciones(char *linea, sPerm *per)
{
    // 0    1
    char *ptr = strrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    sscanf(linea, "%5d%5d", &per->elem1, &per->elem2);

    return TODO_OK;
}

void vectorPermutacionesMostrar(Vector *v)
{
    sPerm *p = v->vec;

    for (int i = 0; i < v->ce; i++)
        printf("%d %d\n", p[i].elem1, p[i].elem2);
}

void despermutacionProcesarVectores(Vector *vCli, Vector *vPer)
{
    float auxSaldo;

    sPerm *actPer = (sPerm *)vPer->vec + vPer->ce - 1;
    sPerm *priPer = (sPerm *)vPer->vec;

    sCliente *priCliente = (sCliente *)vCli->vec;
    sCliente *actCliente;

    while (actPer >= priPer)
    {
        actCliente = priCliente + actPer->elem1;
        auxSaldo = actCliente->saldo;

        actCliente->saldo = (priCliente + actPer->elem2)->saldo;
        (priCliente + actPer->elem2)->saldo = auxSaldo;

        actPer--;
    }
}

void vectorClientesAArchivoTxt(const Vector *vCli, const char *archCliRestaurado)
{
    FILE *archCliRes = fopen(archCliRestaurado, "wt");
    if (!archCliRes)
        return;

    sCliente *actCli = (sCliente *)vCli->vec;
    sCliente *ultCli = (sCliente *)vCli->vec + vCli->ce - 1;

    for (sCliente *i = actCli; i <= ultCli; i++)
    {
        fprintf(archCliRes, "%d|%s|%s|%.2f\n", i->legajo, i->nomYAp, i->codSeg, i->saldo);
    }

    fclose(archCliRes);
}