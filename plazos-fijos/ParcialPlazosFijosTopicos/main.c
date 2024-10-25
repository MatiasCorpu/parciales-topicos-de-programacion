#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../SolucionParcialPlazosFijosTopicos/SolucionParcialPlazosFijos.h"

/*

VECTOR ORDENADO POR CUENTAS

3|1000|3400.00|50.00|3/1/2019|60
1|2000|2500.00|40.00|5/3/2019|30
6|2000|6250.00|65.00|12/5/2018|90
5|3000|5350.00|55.00|16/6/2018|180
2|5000|2000.00|54.00|24/5/2018|90
4|7000|10000.00|48.00|12/4/2019|180


FECHA ACTUAL: 3/6/2019

*/

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_ARG 2
#define ERR_FECHA 3
#define ERR_LINEA_LARGA 4

#define ANIO_BASE 1900
#define TAM_INI_VEC 20
#define TAM_MAX_LINEA 300

typedef int (*Comparar)(const void *, const void *);

typedef struct
{
	void *vec;
	int ce;
	size_t tamElem;
	int cap;
} Vector;

Vector *vectorCrear_ALU(size_t tamElem);
bool vectorRedimencionar_ALU(Vector *vec);
void vectorDestruir_ALU(Vector *vec);
int cmpInt_ALU(const void *a, const void *b);
bool vectorInsertarOrdenado_ALU(Vector *vec, void *dato, Comparar cmp);

void mostrarCuentas_ALU(const char *nombreArchCuentas);
bool txtAFecha_ALU(const char *txt, Fecha *fecha);
bool esAnioBisiesto_ALU(const int anio);
int cantDiaMes_ALU(const int anio, const int mes);
bool esFechaValida_ALU(const Fecha *f);
void mostrarVecPF_ALU(Vector *vec);
int lineaAEstructura_ALU(PlazoFijo *pf, char *linea);
Vector *cargarVectorPF_ALU(const char *nombrePlazosFijos, Vector *vec);
int cmpFechas_ALU(const Fecha *f1, const Fecha *f2);
void procesarPF_ALU(FILE *cuentasDat, Vector *vec, Fecha *fechaProceso);

int main(int argc, char *argv[])
{
	generarArchivos(argv[1], argv[2]);

	if (argc != 4)
	{
		puts("Cantidad incorrecta de par�metros.");
		return ERR_ARG;
	}

	puts("Cuentas antes de actualizar:");
	mostrarCuentas_ALU(argv[1]);

	FILE *cuentasDat = fopen(argv[1], "r+b");

	if (!cuentasDat)
		return ERR_ARCH;

	Fecha fechaProceso;

	if (txtAFecha_ALU(argv[3], &fechaProceso) == false)
		return ERR_FECHA;

	Vector *vecPF = vectorCrear_ALU(sizeof(PlazoFijo));

	cargarVectorPF_ALU(argv[2], vecPF);

	procesarPF_ALU(cuentasDat, vecPF, &fechaProceso);

	vectorDestruir_ALU(vecPF);
	fclose(cuentasDat);

	puts("\nCuentas despues de actualizar:");
	mostrarCuentas_ALU(argv[1]);

	return TODO_OK;
}

void mostrarCuentas_ALU(const char *nombreArchCuentas)
{
	FILE *archC = fopen(nombreArchCuentas, "rb");
	if (!archC)
		return;

	Cuenta c;

	while (fread(&c, sizeof(Cuenta), 1, archC))
		printf("%-8d%-25s%8.2f\n", c.cuenta, c.cliente, c.saldo);

	fclose(archC);
}

bool txtAFecha_ALU(const char *txt, Fecha *fecha)
{
	sscanf(txt, "%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);

	if (!esFechaValida_ALU(fecha))
		return false;

	return true;
}

bool esFechaValida_ALU(const Fecha *f)
{
	if (f->anio >= ANIO_BASE)
		if (f->mes >= 1 && f->mes <= 12)
			if (f->dia >= 1 && f->dia <= cantDiaMes_ALU(f->anio, f->mes))
				return true;

	return false;
}

int cantDiaMes_ALU(const int anio, const int mes)
{
	int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ((mes == 2) && esAnioBisiesto_ALU(anio))
		return 29;

	return cdm[mes];
}

bool esAnioBisiesto_ALU(const int anio)
{
	return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

Vector *cargarVectorPF_ALU(const char *nombrePlazosFijos, Vector *vec)
{

	FILE *archPF = fopen(nombrePlazosFijos, "rt");
	if (!archPF)
		return NULL;

	PlazoFijo pf;
	char linea[TAM_MAX_LINEA];

	while (fgets(linea, TAM_MAX_LINEA, archPF))
	{
		lineaAEstructura_ALU(&pf, linea);
		vectorInsertarOrdenado_ALU(vec, &pf, cmpInt_ALU);
	}

	// mostrarVecPF_ALU(vec);
	fclose(archPF);
	return vec;
}

int lineaAEstructura_ALU(PlazoFijo *pf, char *linea)
{
	// 4|7000|10000.00|48.00|12/4/2019|180\n
	char *ptr = strrchr(linea, '\n');
	if (!ptr)
		return ERR_LINEA_LARGA;

	// DIAS
	*ptr = '\0';
	ptr = strrchr(linea, '|');
	sscanf(ptr + 1, "%d", &pf->dias);

	*ptr = '\0';
	ptr = strrchr(linea, '|');
	sscanf(ptr + 1, "%d/%d/%d", &pf->fechaConstitucion.dia, &pf->fechaConstitucion.mes, &pf->fechaConstitucion.anio);

	// INTERES ANUAL
	*ptr = '\0';
	ptr = strrchr(linea, '|');
	sscanf(ptr + 1, "%f", &pf->interesAnual);

	// MONTO
	*ptr = '\0';
	ptr = strrchr(linea, '|');
	sscanf(ptr + 1, "%f", &pf->monto);

	// CUENTA
	*ptr = '\0';
	ptr = strchr(linea, '|');
	sscanf(ptr + 1, "%d", &pf->cuenta);

	// PLAZO FIJO
	*ptr = '\0';
	sscanf(linea, "%d", &pf->nroPF);

	return TODO_OK;
}

bool vectorInsertarOrdenado_ALU(Vector *vec, void *dato, Comparar cmp)
{
	if (vec->ce == vec->cap)
		vectorRedimencionar_ALU(vec);

	void *act = vec->vec;
	void *ult = vec->vec + (vec->ce - 1) * vec->tamElem;

	while (act <= ult)
	{
		if (cmp(act, dato) >= 0)
			break;

		act += vec->tamElem;
	}

	for (void *i = vec->vec + vec->ce * vec->tamElem; i > act; i -= vec->tamElem)
		memcpy(i, i - vec->tamElem, vec->tamElem);

	memcpy(act, dato, vec->tamElem);

	vec->ce++;
	return true;
}

int cmpInt_ALU(const void *a, const void *b)
{
	PlazoFijo *x = (PlazoFijo *)a;
	PlazoFijo *y = (PlazoFijo *)b;

	return x->cuenta - y->cuenta;
}

void procesarPF_ALU(FILE *cuentasDat, Vector *vec, Fecha *fechaProceso)
{
	PlazoFijo *actPf = (PlazoFijo *)vec->vec;
	PlazoFijo *ultPf = (PlazoFijo *)vec->vec + vec->ce - 1;

	Cuenta ct;

	fread(&ct, sizeof(Cuenta), 1, cuentasDat);
	while (!feof(cuentasDat) && actPf <= ultPf)
	{
		int cmp = ct.cuenta - actPf->cuenta;

		if (cmp == 0)
		{
			cmpFechas(fechaProceso, &actPf->fechaConstitucion); // si no llamo a una funcion de fecha de lib se rompe, no se por que
			if (cmpFechas_ALU(fechaProceso, &actPf->fechaConstitucion) > 0)
			{
				ct.saldo += (actPf->monto + (actPf->dias / 365.0) * (actPf->interesAnual / 100.0) * actPf->monto);
				actPf++;
			}
		}
		else if (cmp < 0)
		{
			fseek(cuentasDat, -(long)sizeof(Cuenta), SEEK_CUR);
			fwrite(&ct, sizeof(Cuenta), 1, cuentasDat);
			fseek(cuentasDat, 0L, SEEK_CUR);

			fread(&ct, sizeof(Cuenta), 1, cuentasDat);
		}
		else
			actPf++; //-> hay un plazo fijo de una cuenta que no existe
	}
	if (!feof(cuentasDat)) // -> el ultimo no se actualiza dentro del while porque actPf > ultPf y sale del bucle
	{
		fseek(cuentasDat, -(long)sizeof(Cuenta), SEEK_CUR);
		fwrite(&ct, sizeof(Cuenta), 1, cuentasDat);
		fseek(cuentasDat, 0L, SEEK_CUR);
	}
	//-> si sobran plazos fijos = hay plazos fijos de cuantas que no existen
	//-> si sobran sobran cuentas = simplente no se actualizan
}

int cmpFechas_ALU(const Fecha *f1, const Fecha *f2)
{
	if (f1->anio != f2->anio)
		return f1->anio - f2->anio;

	if (f1->mes != f2->mes)
		return f1->mes - f2->mes;

	return f1->dia - f2->dia;
}

void mostrarVecPF_ALU(Vector *vec)
{
	PlazoFijo *pf = (PlazoFijo *)vec->vec;

	for (int i = 0; i < vec->ce; i++)
	{
		printf("%d %d %.2f %.2f %d/%d/%d %d\n", pf[i].nroPF, pf[i].cuenta, pf[i].monto, pf[i].interesAnual, pf[i].fechaConstitucion.dia, pf[i].fechaConstitucion.mes, pf[i].fechaConstitucion.anio, pf[i].dias);
	}
}

Vector *vectorCrear_ALU(size_t tamElem)
{
	Vector *vec = malloc(sizeof(Vector));
	if (!vec)
		return NULL;

	vec->vec = malloc(tamElem * TAM_INI_VEC);
	if (!vec->vec)
	{
		free(vec);
		return NULL;
	}

	vec->ce = 0;
	vec->tamElem = tamElem;
	vec->cap = TAM_INI_VEC;

	return vec;
}

bool vectorRedimencionar_ALU(Vector *vec)
{
	void *nVec = realloc(vec->vec, vec->cap * 2 * vec->tamElem);
	if (!nVec)
		return false;

	vec->vec = nVec;
	vec->cap *= 2;
	return true;
}

void vectorDestruir_ALU(Vector *vec)
{
	free(vec->vec);
	free(vec);
}
