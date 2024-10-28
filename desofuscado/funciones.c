#include "funciones.h"

// funciones de archivo
int desofuscarCitasDeArchivoTxt(const char *nomArchCitasTxt)
{
    FILE *citas = fopen(nomArchCitasTxt, "rt");
    if (!citas)
        return ERR_ARCH;

    FILE *citasTmp = fopen("tmp.txt", "wt");
    if (!citasTmp)
    {
        fclose(citas);
        return ERR_ARCH;
    }

    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, citas))
    {
        desofuscar(linea);
        fprintf(citasTmp, "%s\n", linea);
    }

    fclose(citas);
    fclose(citasTmp);

    remove(nomArchCitasTxt);
    rename("tmp.txt", nomArchCitasTxt);

    return TODO_OK;
}

void mostrarArchivoCitasTxt(const char *nomArchCitasTxt)
{
    FILE *citas = fopen(nomArchCitasTxt, "rt");
    if (!citas)
        return;

    char linea[TAM_MAX_LINEA];

    while (fgets(linea, TAM_MAX_LINEA, citas))
        printf("%s", linea);

    fclose(citas);
}

// funcciones de desofuscar
char *desofuscar(char *s)
{
    SecuenciaPal secLect;
    crearSecuenciaPal(&secLect, s);

    char lineaEscr[TAM_MAX_LINEA];
    SecuenciaPal secEscr;
    crearSecuenciaPal(&secEscr, lineaEscr);

    Palabra pal;

    while (leerPalabra(&secLect, &pal))
    {
        cambiarletrasDeLaPalabra(&pal);
        darVueltaPalabra(&pal);
        escribirPalabra(&secEscr, &pal);
        escribirCaracter(&secEscr, ' ');
    }

    moverPunteroSecPal(&secEscr, -1);
    escribirCaracter(&secEscr, '\0');

    mstrcpy(s, lineaEscr);

    return s;
}

void crearSecuenciaPal(SecuenciaPal *secPal, char *s)
{
    secPal->ptr = s;
    secPal->finSecPal = false;
}

bool leerPalabra(SecuenciaPal *secPal, Palabra *pal)
{
    while (*secPal->ptr != '\0' && !ES_LETRA(*secPal->ptr))
        secPal->ptr++;

    if (*secPal->ptr == '\0')
    {
        secPal->finSecPal = true;
        return false;
    }

    char *actPal = pal->palabra;

    while (*secPal->ptr != '\0' && ES_LETRA(*secPal->ptr))
    {
        *actPal = *secPal->ptr;
        actPal++;
        secPal->ptr++;
    }
    *actPal = '\0';

    return true;
}

void cambiarletrasDeLaPalabra(Palabra *pal)
{
    char key[] = "fedcba";
    int ceKey = mstrlen(key);

    char *act = pal->palabra;
    char *posi;

    while (*act != '\0')
    {
        posi = buscarElemento(key, ceKey, sizeof(char), act, cmpCaracter);

        if (posi != NULL)
        {
            *act = *(key + ((ceKey - 1) - (posi - key) / sizeof(char)));
            // a = mstrlen - posi = f
        }

        act++;
    }
}

void darVueltaPalabra(Palabra *pal)
{
    int nCar = mstrlen(pal->palabra);

    char *pri = pal->palabra;
    char *ult = pal->palabra + nCar - 1;
    char aux;

    while (pri < ult)
    {
        aux = *pri;
        *pri = *ult;
        *ult = aux;

        ult--;
        pri++;
    }
}

void escribirPalabra(SecuenciaPal *secPal, const Palabra *pal)
{
    const char *act = pal->palabra;

    while (*act != '\0')
    {
        *secPal->ptr = *act;
        secPal->ptr++;
        act++;
    }
}

void escribirCaracter(SecuenciaPal *secPal, const char c)
{
    *secPal->ptr = c;
    secPal->ptr++;
}

void moverPunteroSecPal(SecuenciaPal *secPal, int n)
{
    secPal->ptr += n;
}

// funciones de strlib
int mstrlen(const char *s)
{
    int count = 0;

    while (*s != '\0')
    {
        count++;
        s++;
    }
    return count;
}

char *mstrcpy(char *s1, const char *s2)
{
    if (mstrlen(s1) < mstrlen(s2))
        return NULL;

    char *ptr = s1;

    while (*s2 != '\0')
    {
        *ptr = *s2;
        ptr++;
        s2++;
    }

    *ptr = '\0';

    return s1;
}

// funcion generica
int cmpCaracter(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

void *buscarElemento(void *vec, int ce, size_t tamElem, void *elem, Comparacion cmp)
{
    void *act = vec;
    void *ult = vec + tamElem * (ce - 1);

    while (act <= ult)
    {
        if (cmp(act, elem) == 0)
            return act;
        act++;
    }

    return NULL;
}
