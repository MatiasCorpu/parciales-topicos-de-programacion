#include "funciones.h"

void accionMostrarEntrada(void *entrada, void *extra)
{
    Entrada *ent = (Entrada *)entrada;

    printf("%s  %s\n", ent->cod, ent->usada == false ? "false" : "true");
}

int cmpCodEntradas(const void *a, const void *b)
{
    Entrada *x = (Entrada *)a;
    Entrada *y = (Entrada *)b;

    return strcmp(x->cod, y->cod);
}

// ARCHIVO

void archivoEntradasGenerar(const char *nomArchEntradas)
{
    FILE *arch = fopen(nomArchEntradas, "wb");
    if (!arch)
        return;

    Entrada vecEntradas[TAM_MAX_ENTRADAS] = {
        {"E00001", false},
        {"A00001", false},
        {"A00004", false},
        {"B00002", false},
        {"C00004", false},
        {"D00004", false},
        {"B00003", false},
        {"C00001", false},
        {"B00004", false},
        {"C00002", false},
        {"A00003", false},
        {"C00003", false},
        {"D00002", false},
        {"D00001", false},
        {"D00003", false},
        {"E00003", false},
        {"E00002", false},
        {"B00001", false},
        {"A00002", false},
        {"E00004", false},
    };

    fwrite(vecEntradas, sizeof(Entrada), TAM_MAX_ENTRADAS, arch);

    fclose(arch);
}

void archivoEntradasRecorrer(const char *nomArchEntradas, Accion accion, void *datosAccion)
{
    FILE *arch = fopen(nomArchEntradas, "r+b");
    if (!arch)
        return;

    Entrada ent;

    while (fread(&ent, sizeof(Entrada), 1, arch))
    {
        accion(&ent, datosAccion);
    }

    fclose(arch);
}

void archivoEntradasAMemoria_1(const char *nomArchEntradas, Vector *vec) // utilizando ftell (vec desordenado)
{
    FILE *arch = fopen(nomArchEntradas, "rb");
    if (!arch)
        return;

    fseek(arch, 0L, SEEK_END);
    int ce = ftell(arch) / sizeof(Entrada);
    fseek(arch, 0L, SEEK_SET);

    fread(vec->vec, sizeof(Entrada), ce, arch);
    vec->ce = ce;

    fclose(arch);
}

void archivoEntradasAMemoria_2(const char *nomArchEntradas, Vector *vec)
{
    FILE *arch = fopen(nomArchEntradas, "rb");
    if (!arch)
        return;

    Entrada ent;

    while (fread(&ent, sizeof(Entrada), 1, arch))
    {
        vectorInsertarOrdenado(vec, &ent, cmpCodEntradas);
    }

    fclose(arch);
}

// VECTOR TDA

Vector *vectorCrear(size_t tamElem, int capIni)
{
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    if (!vec)
        return NULL;

    vec->vec = malloc(tamElem * capIni);
    if (!vec->vec)
    {
        free(vec);
        return NULL;
    }

    vec->tamElem = tamElem;
    vec->ce = 0;
    vec->cap = capIni;

    return vec;
}

void vectorDestruir(Vector *vec)
{
    free(vec->vec);
    free(vec);
}

void vectorRecorrer(Vector *vec, Accion accion, void *datosAccion)
{
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);

    for (void *i = vec->vec; i <= ult; i += vec->tamElem)
    {
        accion(i, datosAccion);
    }
}

void vectorInsertarOrdenado(Vector *vec, void *elem, Comparar cmp)
{
    void *act = vec->vec;
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);

    while (act <= ult)
    {
        if (cmp(act, elem) > 0)
            break;

        act += vec->tamElem;
    }

    for (void *i = ult; i >= act; i -= vec->tamElem)
        memcpy(i + vec->tamElem, i, vec->tamElem);

    memcpy(act, elem, vec->tamElem);

    vec->ce++;
}

void vectorOrdenarInsercion(Vector *vec, Comparar cmp)
{
    void *aInsertar = malloc(vec->tamElem);
    void *j;

    for (void *i = vec->vec + vec->tamElem; i < vec->vec + vec->tamElem * vec->ce; i += vec->tamElem)
    {
        memcpy(aInsertar, i, vec->tamElem);

        for (j = i - vec->tamElem; j >= vec->vec && cmp(aInsertar, j) < 0; j -= vec->tamElem)
            memcpy(j + vec->tamElem, j, vec->tamElem);

        memcpy(j + vec->tamElem, aInsertar, vec->tamElem);
    }

    free(aInsertar);
}

void *buscarMinimo(void *ini, void *fin, size_t tamElem, Comparar cmp)
{
    void *min = ini;

    for (void *i = ini; i <= fin; i += tamElem)
    {
        if (cmp(i, min) < 0)
            min = i;
    }

    return min;
}

void vectorOrdenarSeleccion(Vector *vec, Comparar cmp)
{
    void *ult = vec->vec + vec->tamElem * (vec->ce - 1);
    void *aux = malloc(vec->tamElem);

    for (void *i = vec->vec; i < ult; i += vec->tamElem)
    {
        void *posi = buscarMinimo(i, ult, vec->tamElem, cmp);

        if (i != posi)
        {
            memcpy(aux, i, vec->tamElem);
            memcpy(i, posi, vec->tamElem);
            memcpy(posi, aux, vec->tamElem);
        }
    }

    free(aux);
}

void *vectorBusquedaBinaria(Vector *vec, void *elem, Comparar cmp)
{
    void *izq = vec->vec;
    void *der = vec->vec + vec->tamElem * (vec->ce - 1);

    void *mid;

    while (izq <= der)
    {
        mid = izq + ((der - izq) / (2 * vec->tamElem)) * vec->tamElem;

        int comp = cmp(mid, elem);

        if (comp == 0)
            return mid;

        else if (comp < 0)
            izq = mid + vec->tamElem;

        else
            der = mid - vec->tamElem;
    }

    return NULL;
}

// VALIDAR ENTRADA

void procesarEntradas(const char *nomArchEntradas, Vector *vec)
{
    // archivoEntradasAMemoria_1("entradasVendidas.bin", vec); // 1 FORMA  -> BAJAR A MEM ARCHIVO -> ORDENARLO -> BUSCAR LA ENTRADA DE FORMA BINARIA -> ACTUALIZAR
    // vectorOrdenarInsercion(vec, cmpCodEntradas);
    // vectorOrdenarSeleccion(vec, cmpCodEntradas);

    archivoEntradasAMemoria_2("entradasVendidas.bin", vec); // 2 FORMA -> BAJAR A MEM ARCHIVO DE FORMA ORDENADA -> BUSCAR LA ENTRADA DE FORMA BINARIA -> ACTUALIZAR

    printf("\n\nVector :\n");
    vectorRecorrer(vec, accionMostrarEntrada, NULL);

    validarEntradasYActualizar(vec);
}

void validarEntradasYActualizar(Vector *vec)
{
    char entrada[TAM_MAX_COD_ENTRADAS];

    printf("Ingrese entradas, finaliza con 'FIN':\n");
    scanf("%s", entrada);

    while (strcmpi(entrada, "FIN") != 0)
    {
        Entrada *posi = (Entrada *)vectorBusquedaBinaria(vec, entrada, cmpCodEntradas);

        if (posi != NULL && posi->usada == false)
        {
            posi->usada = true;
            printf("Puede ingresar al evento\n");
        }

        else if (posi != NULL)
            printf("Entrada ya utilizada\n");

        else
            printf("Entrada falsa\n");

        fflush(stdin);
        printf("Ingrese entradas, finaliza con 'FIN':\n");
        scanf("%s", entrada);
    }
}
