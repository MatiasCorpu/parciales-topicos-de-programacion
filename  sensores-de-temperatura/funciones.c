#include "funciones.h"

int informeSensores(const char *nomArch)
{
    FILE *arch = fopen(nomArch, "rt");
    if (!arch)
        return ERR_ARCH;

    Vector *vecArch = vectorCrear(sizeof(Sensores), REG_MAX);
    Vector *vecInforme = vectorCrear(sizeof(Sensores), SENSORES_MAX);

    Sensores sen;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, arch))
    {
        cargarLineaAEstructura(&sen, linea);
        vectorInsertarOrdenado(vecArch, &sen, cmpSensores);
    }

    fclose(arch);

    procesarVectorArch(vecArch, vecInforme);
    vectorInformeMostrar(vecInforme);

    vectorDesctruir(vecInforme);
    vectorDesctruir(vecArch);
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

    vec->ce = 0;
    vec->tamElem = tamElem;
    vec->cap = capIni;

    return vec;
}

int cargarLineaAEstructura(Sensores *sen, char *linea)
{
    //  1719077360   DEV08 16.50     OFFLINE\n
    char *ptr = strrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    // CAMPO ESTADO
    *ptr = '\0';
    ptr -= CAMPO_ESTADO;
    strcpy(sen->estado, borrarEspaciosIzq(ptr));

    // CAMPO TEMPERATURA
    *ptr = '\0';
    ptr -= CAMPO_TEMPERATURA;
    sscanf(borrarEspaciosIzq(ptr), "%f", &sen->temperatura);

    // CAMPO CODIGO SENSOR
    *ptr = '\0';
    ptr -= CAMPO_COD_SENSOR;
    strcpy(sen->codSensor, borrarEspaciosIzq(ptr));

    return TODO_OK;
}

char *borrarEspaciosIzq(char *s)
{
    char *ptr = s;
    while (ES_ESPACIO(*ptr) && *ptr != '\0')
        ptr++;

    return ptr;
}

void vectorInsertarOrdenado(Vector *v, void *elem, Comparar cmp)
{
    void *actual = v->vec;
    void *ult = v->vec + (v->ce - 1) * v->tamElem;

    while (actual <= ult)
    {
        if (cmp(actual, elem) >= 0)
            break;

        actual += v->tamElem;
    }

    for (void *i = v->vec + v->ce * v->tamElem; i > actual; i -= v->tamElem)
        memcpy(i, i - v->tamElem, v->tamElem);

    memcpy(actual, elem, v->tamElem);

    v->ce++;
}

int cmpSensores(const void *a, const void *b)
{
    Sensores *x = (Sensores *)a;
    Sensores *y = (Sensores *)b;

    return strcmp(x->codSensor, y->codSensor);
}

int procesarVectorArch(Vector *vArch, Vector *vInf)
{
    Sensores *actVArch = (Sensores *)vArch->vec;
    Sensores *ultVArch = (Sensores *)vArch->vec + vArch->ce - 1;

    Sensores *actVinf = (Sensores *)vInf->vec;

    int ceProm;
    while (actVArch <= ultVArch)
    {

        strcpy(actVinf->codSensor, actVArch->codSensor);
        strcpy(actVinf->estado, actVArch->estado);
        if (strcmp(actVinf->estado, "READY") != 0)
        {
            actVinf->temperatura = 0;
            ceProm = 0;
        }
        else
        {
            actVinf->temperatura = actVArch->temperatura;
            ceProm = 1;
        }
        actVArch++;

        while (actVArch <= ultVArch && (strcmp(actVinf->codSensor, actVArch->codSensor) == 0))
        {
            if ((strcmp(actVArch->estado, "READY") == 0))
            {
                actVinf->temperatura += actVArch->temperatura;
                ceProm++;
            }
            actVArch++;
        }

        if (ceProm != 0)
            actVinf->temperatura /= ceProm;

        vInf->ce++;
        actVinf++;
    }

    return TODO_OK;
}

void vectorInformeMostrar(Vector *v)
{
    Sensores *sen = (Sensores *)v->vec;

    for (int i = 0; i < v->ce; i++)
    {
        if (sen[i].temperatura != 0)
            printf("%8s%8.2f\n", sen[i].codSensor, sen[i].temperatura);
        else
            printf("%8s  -Sin informacion confiable-\n", sen[i].codSensor);
    }
}

void vectorDesctruir(Vector *v)
{
    free(v->vec);
    free(v);
}