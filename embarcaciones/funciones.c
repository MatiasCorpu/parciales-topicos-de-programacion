#include "funciones.h"

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    double dLat = (lat2 - lat1) * PI / 180.0;
    double dLon = (lon2 - lon1) * PI / 180.0;

    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c; // Retorna la distancia en kilómetros
}

Vector *vectorCrear(size_t tamELem, int capIni)
{
    Vector *vec = malloc(sizeof(Vector));
    if (!vec)
        return NULL;

    vec->vec = malloc(tamELem * capIni);
    if (!vec->vec)
    {
        free(vec);
        return NULL;
    }

    vec->ce = 0;
    vec->cap = capIni;
    vec->tamElem = tamELem;

    return vec;
}

void vectorDestruir(Vector *vec)
{
    free(vec->vec);
    free(vec);
}

int minimaDistanciaRecorridaPorEmbarcaciones(const char *archEmbarcaciones)
{
    FILE *archEmb = fopen(archEmbarcaciones, "r");
    if (!archEmb)
        return ERR_ARCH;

    Vector *vec = vectorCrear(sizeof(EmbarcacionRecorrido), MAX_CANT_EMBARCACIONES);

    EmbarcacionRecorrido emb;

    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, archEmb))
    {
        lineaAEstructura(linea, &emb);
        emb.distanciaKM = 0;
        vectorInsertarOrdenado(vec, &emb, cmpMatriculasEmbarcaciones, actualizarDistanciaEmbarcacion);
    }

    vectorRecorrer(vec, accionMostrarEmbarcacion, NULL);

    fclose(archEmb);
    vectorDestruir(vec);
    return TODO_OK;
}

int lineaAEstructura(char *linea, EmbarcacionRecorrido *emb)
{
    char *ptr = strrchr(linea, '\n');
    if (!ptr)
        return ERR_LINEA_LARGA;

    // MATRICULA
    *ptr = '\0';
    ptr = strrchr(linea, ',');
    sscanf(ptr + 1, "%s", emb->matricula);

    // LONGITUD
    *ptr = '\0';
    ptr = strrchr(linea, ',');
    sscanf(ptr + 1, "%lf", &emb->longitud);

    // LATITUD
    *ptr = '\0';
    sscanf(linea, "%lf", &emb->latitud);

    return TODO_OK;
}

int cmpMatriculasEmbarcaciones(const void *a, const void *b)
{
    EmbarcacionRecorrido *x = (EmbarcacionRecorrido *)a;
    EmbarcacionRecorrido *y = (EmbarcacionRecorrido *)b;

    return strcmp(x->matricula, y->matricula);
}

int vectorInsertarOrdenado(Vector *vec, void *elem, Comparar cmp, Actualizar actualizar)
{
    void *act = vec->vec;
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);

    while (act <= ult)
    {
        int comp = cmp(act, elem);

        if (comp == 0)
        {
            actualizar(act, elem);
            return DUPLICADO_O_ACTUALIZADO;
        }
        if (comp > 0)
            break;

        act += vec->tamElem;
    }

    for (void *i = ult; i >= act; i -= vec->tamElem)
        memcpy(i + vec->tamElem, i, vec->tamElem);

    memcpy(act, elem, vec->tamElem);
    vec->ce++;

    return TODO_OK;
}

void vectorRecorrer(Vector *vec, Accion accion, void *datosAccion)
{
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);

    for (void *i = vec->vec; i <= ult; i += vec->tamElem)
    {
        accion(i, datosAccion);
    }
}

void accionMostrarEmbarcacion(void *i, void *extra)
{
    EmbarcacionRecorrido *emb = (EmbarcacionRecorrido *)i;
    printf("%-10s Recorrido : %lf km\n", emb->matricula, emb->distanciaKM);
}

void actualizarDistanciaEmbarcacion(void *act, const void *datoAct)
{
    EmbarcacionRecorrido *actualizar = (EmbarcacionRecorrido *)act;
    EmbarcacionRecorrido *datos = (EmbarcacionRecorrido *)datoAct;

    double distanciaMinima = haversine(actualizar->latitud, actualizar->longitud, datos->latitud, datos->longitud);

    actualizar->latitud = datos->latitud;
    actualizar->longitud = datos->longitud;
    actualizar->distanciaKM += distanciaMinima;
}