/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************/

#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>
#include "../SolucionClubesTopicos/UtilitariasClubes.h"
#include "../SolucionClubesTopicos/SolucionClubes.h"

#define ARG_ARCH_CLUB_A 1
#define ARG_ARCH_CLUB_B 2
#define ARG_ARCH_CLUB_FUS 3

#define ERR_LINEA_LARGA 3

#define CAP_INI_VEC 20
#define TAM_MAX_LINEA 300

typedef int (*Comparar)(const void *, const void *);

typedef struct
{
	void *vec;
	int ce;
	size_t tamElem;
	int cap;
} Vector;

Vector *vectorCrear_ALU(size_t tamElem, int capIni);
bool vectorRedimencionar_ALU(Vector *vec);
void vectorDestruir_ALU(Vector *vec);

int cmpCodSocioEntero_ALU(const void *a, const void *b);
void ordenarVector_ALU(void *vec, int ce, size_t tamElem, Comparar cmp);

void mostrarVecSociosB_ALU(Vector *vec);
int lineaAestructura_ALU(SocioB *sb, char *linea);
int sociosClubBaMemoria_ALU(Vector *vec, const char *nombreSociosClubBTxt);
void generarArchivoSociosClubB_ALU(const char *nomArchSociosB, const Vector *vec);
int fusionarArchivoYVector_ALU(const char *nombreSociosClubA, Vector *vec, const char *nombreSociosFus);
int fusionarArchivos_ALU(const char *nombreSociosClubA, const char *nombreSociosClubBTxt, const char *nombreSociosFus);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para m�quinas Linux
	SetConsoleCP(1252);			  // Cambiar STDIN -  Para m�quinas Windows
	SetConsoleOutputCP(1252);	  // Cambiar STDOUT - Para m�quinas Windows

	generarArchivoSociosClubA(argv[ARG_ARCH_CLUB_A]);
	generarArchivoSociosClubBTxtDesord(argv[ARG_ARCH_CLUB_B]);

	mostrarArchSociosA(argv[ARG_ARCH_CLUB_A]);
	mostrarArchSociosBTxt(argv[ARG_ARCH_CLUB_B]);

	/**
		Esta funci�n debe fusionar los archivos de los socios del club A y los del club B en un nuevo archivo.
		La estructura del archivo fusionado es la del archivo de socios del club A.
		El c�digo de socio en el archivo fusionado debe incluir el club de donde proviene. Existen socios que se encuentran en
		los 2 clubes. Ej: socio 1 del club A, el c�digo resultante es 1-A. El c�digo del socio 2, que est� en los 2 clubes
		queda 2-AB.
		La antig�edad se toma la mayor.
	*/
	/// Para que ejecute su c�digo, debe descomentar fusionarArchivos_ALU y comentar fusionarArchivos.
	fusionarArchivos_ALU(argv[ARG_ARCH_CLUB_A], argv[ARG_ARCH_CLUB_B], argv[ARG_ARCH_CLUB_FUS]);
	// fusionarArchivos(argv[ARG_ARCH_CLUB_A], argv[ARG_ARCH_CLUB_B], argv[ARG_ARCH_CLUB_FUS]);

	puts("Archivo Fusionado");
	mostrarArchSociosA(argv[ARG_ARCH_CLUB_FUS]);

	return TODO_OK;
}

int fusionarArchivos_ALU(const char *nombreSociosClubA, const char *nombreSociosClubBTxt, const char *nombreSociosFus)
{
	Vector *vSociosB = vectorCrear_ALU(sizeof(SocioB), CAP_INI_VEC);
	sociosClubBaMemoria_ALU(vSociosB, nombreSociosClubBTxt);
	ordenarVector_ALU(vSociosB->vec, vSociosB->ce, vSociosB->tamElem, cmpCodSocioEntero_ALU);

	generarArchivoSociosClubB_ALU("Socios_Club_B.dat", vSociosB);

	fusionarArchivoYVector_ALU(nombreSociosClubA, vSociosB, nombreSociosFus);

	vectorDestruir_ALU(vSociosB);
	return TODO_OK;
}

Vector *vectorCrear_ALU(size_t tamElem, int capIni)
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

bool vectorRedimencionar_ALU(Vector *vec)
{
	void *nVec = realloc(vec->vec, vec->cap * vec->tamElem * 2);
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

int sociosClubBaMemoria_ALU(Vector *vec, const char *nombreSociosClubBTxt)
{
	FILE *sb = fopen(nombreSociosClubBTxt, "rt");
	if (!sb)
		return ERR_ARCHIVO;

	SocioB *vecSb = (SocioB *)vec->vec;

	SocioB eSb;
	char linea[TAM_MAX_LINEA];

	while (fgets(linea, TAM_MAX_LINEA, sb))
	{
		lineaAestructura_ALU(&eSb, linea);
		memcpy(vecSb, &eSb, vec->tamElem);
		vecSb++;
		vec->ce++;
	}

	// mostrarVecSociosB_ALU(vec);
	fclose(sb);
	return TODO_OK;
}

int lineaAestructura_ALU(SocioB *sb, char *linea)
{
	// 1258\0
	char *ptr = strrchr(linea, '\n');
	if (!ptr)
		return ERR_LINEA_LARGA;

	// ANTIGUEDAD
	*ptr = '\0';
	ptr = strrchr(linea, '|');
	sscanf(ptr + 1, "%d", &sb->antiguedad);

	// NOMBRE Y APELLIDO
	*ptr = '\0';
	ptr = strrchr(linea, '|');
	strcpy(sb->apyn, ptr + 1);

	// NRO SOCIO
	*ptr = '\0';
	sscanf(linea, "%d", &sb->nroSocio);

	return TODO_OK;
}

void mostrarVecSociosB_ALU(Vector *vec)
{
	SocioB *eSb = (SocioB *)vec->vec;

	printf("Socios B en memoria:\n");
	for (int i = 0; i < vec->ce; i++)
		printf("%d %s %d\n", eSb[i].nroSocio, eSb[i].apyn, eSb[i].antiguedad);
}

void ordenarVector_ALU(void *vec, int ce, size_t tamElem, Comparar cmp)
{
	void *aInsertar = malloc(tamElem);
	void *j;

	for (void *i = vec + tamElem; i <= vec + (ce - 1) * tamElem; i += tamElem)
	{
		memcpy(aInsertar, i, tamElem);

		for (j = i - tamElem; j >= vec && cmp(aInsertar, j) < 0; j -= tamElem)
			memcpy(j + tamElem, j, tamElem);

		memcpy(j + tamElem, aInsertar, tamElem);
	}

	free(aInsertar);
}

int cmpCodSocioEntero_ALU(const void *a, const void *b)
{
	SocioB *x = (SocioB *)a;
	SocioB *y = (SocioB *)b;

	return x->nroSocio - y->nroSocio;
}

void generarArchivoSociosClubB_ALU(const char *nomArchSociosB, const Vector *vec)
{
	FILE *sb = fopen(nomArchSociosB, "wb");
	if (!sb)
		return;

	fwrite(vec->vec, vec->tamElem, vec->ce, sb);
	fclose(sb);
}

int fusionarArchivoYVector_ALU(const char *nombreSociosClubA, Vector *vec, const char *nombreSociosFus)
{
	FILE *sa = fopen(nombreSociosClubA, "rb");
	if (!sa)
		return ERR_ARCHIVO;

	FILE *sFus = fopen(nombreSociosFus, "wb");
	if (!sFus)
	{
		fclose(sa);
		return ERR_ARCHIVO;
	}

	SocioB *actSB = (SocioB *)vec->vec;
	SocioB *ultSB = (SocioB *)vec->vec + vec->ce - 1;

	SocioA eSA;
	fread(&eSA, sizeof(SocioA), 1, sa);

	while (!feof(sa) && actSB <= ultSB)
	{
		int cmp = atoi(eSA.codSocio) - actSB->nroSocio;

		if (cmp == 0)
		{
			if (actSB->antiguedad > eSA.antiguedad)
				eSA.antiguedad = actSB->antiguedad;

			strcat(eSA.codSocio, "-AB");
			fwrite(&eSA, sizeof(SocioA), 1, sFus);
			fread(&eSA, sizeof(SocioA), 1, sa);
			actSB++;
		}
		else if (cmp < 0)
		{
			strcat(eSA.codSocio, "-A");
			fwrite(&eSA, sizeof(SocioA), 1, sFus);
			fread(&eSA, sizeof(SocioA), 1, sa);
		}
		else
		{
			SocioA aux;
			sprintf(aux.codSocio, "%d", actSB->nroSocio);
			strcat(aux.codSocio, "-B");
			strcpy(aux.apyn, actSB->apyn);
			aux.antiguedad = actSB->antiguedad;

			fwrite(&aux, sizeof(SocioA), 1, sFus);
			actSB++;
		}
	}

	while (!feof(sa))
	{
		strcat(eSA.codSocio, "-A");
		fwrite(&eSA, sizeof(SocioA), 1, sFus);
		fread(&eSA, sizeof(SocioA), 1, sa);
	}

	while (actSB <= ultSB)
	{
		SocioA aux;
		sprintf(aux.codSocio, "%d", actSB->nroSocio);
		strcat(aux.codSocio, "-B");
		strcpy(aux.apyn, actSB->apyn);
		aux.antiguedad = actSB->antiguedad;

		fwrite(&aux, sizeof(SocioA), 1, sFus);
		actSB++;
	}

	fclose(sFus);
	fclose(sa);
	return TODO_OK;
}

/*
Socios Club A .bin (char, char , int)
1144, Perez, Juan, 12 o
1155, Rodriguez, Pedro, 25 o
1163, Pereyra, Joaquin, 11 o
1211, Gonzalez, Oscar, 38 o
1234, Garcia, Julian, 9 o
1245, Nuñez, Alejandro, 26 o
1256, Castro, Fernando, 23 o
1378, Alvarez, Roberto, 22 o

Socios B en memoria: (int char int)
1000 Antuñez, Antonio 9>
1110 Gomez, Carlos 19>
1170 Martinez, Pablo 11>
1209 Gimenez, Martin 39>
1211 Gonzalez, Oscar 40>
1239 Garcia, Jose 15>
1245 Nuñez, Alejandro 23>
1258 Dominguez, Matias 21 >
1378 Alvarez, Roberto 30>

Archivo Fusionado . dat

Socios Club A
1000-B, Antuñez, Antonio, 9
1110-B, Gomez, Carlos, 19
1144-A, Perez, Juan, 12
1155-A, Rodriguez, Pedro, 25
1163-A, Pereyra, Joaquin, 11
1170-B, Martinez, Pablo, 11
1209-B, Gimenez, Martin, 39
1211-AB, Gonzalez, Oscar, 40
1234-A, Garcia, Julian, 9
1239-B, Garcia, Jose, 15
1245-AB, Nuñez, Alejandro, 26
1256-A, Castro, Fernando, 23
1258-B, Dominguez, Matias, 21
1378-AB, Alvarez, Roberto, 30

*/
