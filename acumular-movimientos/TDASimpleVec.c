///A Implementar por el alumno
#include "TDASimpleVec.h"
#include "general.h"

#define ERR_MEM 1

#define CAP_INI 1
#define INSERTADO 2
#define TODO_OK 0


TDASimVec* crearTDASimVecALU(unsigned tamEle)
{
    TDASimVec *vec = (TDASimVec*)malloc(sizeof(TDASimVec));
    if(!vec)
        return NULL;

    vec->vec = malloc(tamEle * CAP_INI);
    if(!vec->vec)
    {
        free(vec);
        return NULL;
    }

    vec->ce = 0;
    vec->tamEle = tamEle;
    vec->maxEle = CAP_INI;

    return vec;
};

int insertarAlFinalALU(TDASimVec* sv, void* ele)
{
    if(sv->maxEle == sv->ce)
    {
        void *nVec = realloc(sv->vec, sv->maxEle * 2 * sv->tamEle);
        if(nVec == NULL)
            return ERR_MEM;

        sv->vec = nVec;
        sv->maxEle *= 2;
    }

    void *ultMasUno = sv->vec + sv->tamEle * (sv->ce);

    memcpy(ultMasUno, ele, sv->tamEle);

    sv->ce++;

    return INSERTADO;
}


TDASimVec* ordenarALU(TDASimVec* sv, int cmp(const void*a, const void* b))
{
    void *ult = sv->vec + sv->tamEle * (sv->ce - 1);

    void *aInsertar = malloc(sv->tamEle);
    if(!aInsertar)
        return NULL;

    void *j;

    for(void *i = sv->vec + sv->tamEle; i <= ult ; i += sv->tamEle)
    {
        memcpy(aInsertar, i, sv->tamEle);
        for(j = i - sv->tamEle; j >= sv->vec && cmp(j, aInsertar) > 0; j-= sv->tamEle)
        {
            memcpy(j + sv->tamEle, j , sv->tamEle);
        }
        memcpy(j + sv->tamEle, aInsertar , sv->tamEle);
    }

    free(aInsertar);

    return sv;
};

TDASimVec* agruparALU(TDASimVec* sv, int cmp(const void*, const void*), int fagrup(void*dest, const void* origen))
{
    void *ptrAcum = sv->vec;
    void *ult = sv->vec + sv->tamEle * (sv->ce - 1);

    void *siguiente = sv->vec + sv->tamEle;
    void *aux = malloc(sv->tamEle);

    memcpy(aux, ptrAcum, sv->tamEle);

    while(siguiente <= ult)
    {
        if(cmp(aux, siguiente) == 0)
        {
            fagrup(aux, siguiente);
            sv->ce--;
        }
        else  if(cmp(aux, siguiente) < 0)
        {
            memcpy(ptrAcum, aux, sv->tamEle);
            ptrAcum += sv->tamEle;
            memcpy(aux, siguiente, sv->tamEle);
        }

        siguiente += sv->tamEle;
    }

    memcpy(ptrAcum, aux, sv->tamEle);
    free(aux);

    return sv;
};

int agruparMovimientoALU(void*dest, const void* origen)
{
    tMovimiento *d = (tMovimiento *)dest;
    tMovimiento *o = (tMovimiento *)origen;

    d->cantidad += o->cantidad;

    return TODO_OK;
}


void destruirALU(TDASimVec* sv)
{
    free(sv->vec);
    free(sv);
};

int mostrarMovimientoALU(void* v)
{
    tMovimiento m = *(tMovimiento*)v;

    printf("%s %d\n", m.CodProducto, m.cantidad);

    return TODO_OK;
}

int cmpMovimientoALU(const void* a, const void* b)
{
    tMovimiento x = *(tMovimiento*)a;
    tMovimiento y = *(tMovimiento*)b;

    return strcmp(x.CodProducto, y.CodProducto);
}

TDASimVec* amapALU(TDASimVec* sv, int accion(void*))
{
    void *act = sv->vec;
    void *ult = sv->vec + sv->tamEle * (sv->ce - 1);

    for(void *i = act; i <= ult; i += sv->tamEle)
    {
        accion(i);
    }

    return sv;
}
