/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Matriz/Matriz.h"
#include "../Vector/Vector.h"
#include "../SolucionMatrizDepositos/SolucionMatrizDepositos.h"

#define ARG_STOCKS 1
#define ARG_MOVIMIENTOS 2

#define ERR_MEM 1
#define ERR_LINEA_LARGA 2

#define CAP_INI_VEC 10
#define TAM_MAX_LINEA 300

// MATRIZ
void **matrizCrear_ALU(int fil, int col, size_t tamElem);
void matrizDestruir_ALU(void **mat, int fil);
void matrizMostrar_ALU(int fil, int col, int **mat);
int matrizSumarFila_ALU(int fil, int col, int **mat, int posFil);
int matrizSumarColumna_ALU(int fil, int col, int **mat, int posCol);

// VECTOR
Vector *vectorCrear_ALU(size_t tamElem, int capIni);
bool vectorRedimencionar_ALU(Vector *vec);
void vectorDestruir_ALU(Vector *vec);
void vectorRecorrer_ALU(const Vector *v, Accion accion, void *datosAccion);
void *vectorPrimerElem_ALU(const Vector *v);
void *vectorUltimoElem_ALU(const Vector *v);
int vectorTamElem_ALU(const Vector *v);
int vectorCantidadElementos_ALU(const Vector *v);
void vectorIncrementarCantElem_ALU(Vector *v);
int vectorOrdInsertar_ALU(Vector *v, const void *elem, Cmp cmp, Actualizar actualizar);
int vectorOrdBuscar_ALU(const Vector *v, void *elem, Cmp cmp);

// FUNCIONES ESPECIFICAS
void accionMostrarString_ALU(void *elem, void *extra);
int cmpCodDep_ALU(const void *e1, const void *e2);
int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int **matMovDeps, const Vector *codigosDepositos, const char *nombreStocks);
int lineaAmemoria_ALU(Movimiento *mov, char *linea);
int cargarMatrizMovimientosDepositos_ALU(const char *nombreMovimientos, int **matMovDeps, Vector *codigosDepositos);
void inicializarMatrizEnCero_ALU(int **mat, int filas, int columnas);
int crearVectorCodigosDepositos_ALU(const char *nombreStocks, Vector *codigosDepositos);
int actualizarDepositos_ALU(const char *nombreStocks, const char *nombreMovimientos);

int main(int argc, char *argv[])
{
	generarStocks(argv[ARG_STOCKS]);
	generarMovimientos(argv[ARG_MOVIMIENTOS]);

	puts("Stocks antes de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

	/*********************************************************************************************************************/
	actualizarDepositos_ALU(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
	/************* Descomente la funci�n de arriba y comente la de abajo para ejecutar su c�digo. ************************/
	// actualizarDepositos(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
	/*********************************************************************************************************************/

	puts("\n\nStocks despues de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

	return 0;
}

int actualizarDepositos_ALU(const char *nombreStocks, const char *nombreMovimientos)
{
	Vector *codigosDepositos = vectorCrear_ALU(sizeof(CodigoDeposito), CAP_INI_VEC);
	crearVectorCodigosDepositos_ALU(nombreStocks, codigosDepositos);
	// vectorRecorrer_ALU(codigosDepositos, accionMostrarString_ALU, NULL);

	int **matMovDeps = (int **)matrizCrear_ALU(vectorCantidadElementos_ALU(codigosDepositos), vectorCantidadElementos_ALU(codigosDepositos), sizeof(int));
	inicializarMatrizEnCero_ALU(matMovDeps, vectorCantidadElementos_ALU(codigosDepositos), vectorCantidadElementos_ALU(codigosDepositos));
	cargarMatrizMovimientosDepositos_ALU(nombreMovimientos, matMovDeps, codigosDepositos);
	matrizMostrar_ALU(vectorCantidadElementos_ALU(codigosDepositos), vectorCantidadElementos_ALU(codigosDepositos), matMovDeps);

	procesarMatrizMovimientosDepositosActualizandoStocks_ALU(matMovDeps, codigosDepositos, nombreStocks);

	matrizDestruir_ALU((void **)matMovDeps, vectorCantidadElementos_ALU(codigosDepositos));
	vectorDestruir_ALU(codigosDepositos);
	return TODO_OK;
}

// MATRIZ

void **matrizCrear_ALU(int fil, int col, size_t tamElem)
{
	void **mat = malloc(sizeof(void *) * fil);
	if (!mat)
		return NULL;

	for (int i = 0; i < fil; i++)
	{
		mat[i] = malloc(tamElem * col);

		if (!mat[i])
		{
			for (int j = 0; j < i; j++)
				free(mat[j]);
			free(mat);

			return NULL;
		}
	}

	return mat;
}

void matrizDestruir_ALU(void **mat, int fil)
{
	for (int i = 0; i < fil; i++)
		free(mat[i]);

	free(mat);
}

void matrizMostrar_ALU(int fil, int col, int **mat)
{
	for (int i = 0; i < fil; i++)
	{
		printf("\n");
		for (int j = 0; j < col; j++)
			printf("%02d ", mat[i][j]);
	}
}

void inicializarMatrizEnCero_ALU(int **mat, int filas, int columnas)
{
	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++)
			mat[i][j] = 0;
}

int matrizSumarFila_ALU(int fil, int col, int **mat, int posFil)
{
	int sum = 0;

	for (int j = 0; j < col; j++)
		sum += mat[posFil][j];

	return sum;
}

int matrizSumarColumna_ALU(int fil, int col, int **mat, int posCol)
{
	int sum = 0;

	for (int i = 0; i < fil; i++)
		sum += mat[i][posCol];

	return sum;
}

// VECTOR

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

	vec->ce = 0;
	vec->cap = capIni;
	vec->tamElem = tamElem;

	return vec;
}

bool vectorRedimencionar_ALU(Vector *vec)
{
	void *nVec = realloc(vec->vec, vec->tamElem * vec->cap * 2);
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

void *vectorPrimerElem_ALU(const Vector *v)
{
	return v->vec;
}

void *vectorUltimoElem_ALU(const Vector *v)
{
	return v->vec + v->tamElem * (v->ce - 1);
}

int vectorTamElem_ALU(const Vector *v)
{
	return v->tamElem;
}

int vectorCantidadElementos_ALU(const Vector *v)
{
	return v->ce;
}

void vectorIncrementarCantElem_ALU(Vector *v)
{
	v->ce++;
}

void vectorRecorrer_ALU(const Vector *v, Accion accion, void *datosAccion)
{
	void *pri = vectorPrimerElem_ALU(v);
	void *ult = vectorUltimoElem_ALU(v);

	for (void *i = pri; i <= ult; i += vectorTamElem_ALU(v))
	{
		accion(i, datosAccion);
	}
}

int vectorOrdInsertar_ALU(Vector *v, const void *elem, Cmp cmp, Actualizar actualizar)
{
	void *act = vectorPrimerElem_ALU(v);
	void *ult = vectorUltimoElem_ALU(v);

	while (act <= ult)
	{
		if (cmp(act, elem) == 0)
			return DUPLICADO;

		if (cmp(act, elem) > 0)
			break;

		act += vectorTamElem_ALU(v);
	}

	for (void *i = ult; i >= act; i -= vectorTamElem_ALU(v))
		memcpy(i + vectorTamElem_ALU(v), i, vectorTamElem_ALU(v));

	memcpy(act, elem, vectorTamElem_ALU(v));
	vectorIncrementarCantElem_ALU(v);

	return TODO_OK;
}

int vectorOrdBuscar_ALU(const Vector *v, void *elem, Cmp cmp)
{
	int pos = 0;

	void *act = vectorPrimerElem_ALU(v);
	void *ult = vectorUltimoElem_ALU(v);

	while (act <= ult)
	{
		if (cmp(act, elem) == 0)
			return pos;

		act += vectorTamElem_ALU(v);
		pos++;
	}
	return -1;
}

// FUNCIONES ESPECIFICAS

void accionMostrarString_ALU(void *elem, void *extra)
{
	printf("%s\n", (char *)elem);
}

int crearVectorCodigosDepositos_ALU(const char *nombreStocks, Vector *codigosDepositos)
{
	FILE *archStock = fopen(nombreStocks, "rb");
	if (!archStock)
		return ERR_ARCHIVO;

	Stock st;
	CodigoDeposito cd;

	while (fread(&st, sizeof(Stock), 1, archStock))
	{
		strcpy(cd.codDeposito, st.codDeposito);
		vectorOrdInsertar_ALU(codigosDepositos, &cd, cmpCodDep, NULL);
	}

	fclose(archStock);
	return TODO_OK;
}

int cmpCodDep_ALU(const void *e1, const void *e2)
{
	return strcmp(((CodigoDeposito *)e1)->codDeposito, ((CodigoDeposito *)e2)->codDeposito);
}

int cargarMatrizMovimientosDepositos_ALU(const char *nombreMovimientos, int **matMovDeps, Vector *codigosDepositos)
{
	FILE *archMov = fopen(nombreMovimientos, "rt");
	if (!archMov)
		return ERR_ARCHIVO;

	int posFila, posColum;
	Movimiento mov;
	CodigoDeposito cd;
	char linea[TAM_MAX_LINEA];

	while (fgets(linea, TAM_MAX_LINEA, archMov))
	{
		lineaAmemoria_ALU(&mov, linea);

		// obtengo posi fila
		strcpy(cd.codDeposito, mov.depDestino);
		posFila = vectorOrdBuscar_ALU(codigosDepositos, &cd, cmpCodDep_ALU);
		// obtengo posi columnas
		strcpy(cd.codDeposito, mov.depOrigen);
		posColum = vectorOrdBuscar_ALU(codigosDepositos, &cd, cmpCodDep_ALU);

		matMovDeps[posFila][posColum] += mov.cantidad;
	}

	fclose(archMov);
	return TODO_OK;
}

int lineaAmemoria_ALU(Movimiento *mov, char *linea)
{
	// A         B         000030\n

	sscanf(linea, "%10s%10s%6d", mov->depDestino, mov->depOrigen, &mov->cantidad);

	return TODO_OK;
}

int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int **matMovDeps, const Vector *codigosDepositos, const char *nombreStocks)
{
	FILE *archStock = fopen(nombreStocks, "r+b");
	if (!archStock)
		return ERR_ARCHIVO;

	int pos;
	Stock st;
	CodigoDeposito cd;

	while (fread(&st, sizeof(Stock), 1, archStock))
	{
		strcpy(cd.codDeposito, st.codDeposito);
		pos = vectorOrdBuscar_ALU(codigosDepositos, &cd, cmpCodDep_ALU);

		st.stock += (matrizSumarColumna_ALU(vectorCantidadElementos_ALU(codigosDepositos), vectorCantidadElementos_ALU(codigosDepositos), matMovDeps, pos) -
					 matrizSumarFila_ALU(vectorCantidadElementos_ALU(codigosDepositos), vectorCantidadElementos_ALU(codigosDepositos), matMovDeps, pos));

		// printf("%s %d\n", st.codDeposito, st.stock);

		fseek(archStock, -(long)sizeof(Stock), SEEK_CUR);
		fwrite(&st, sizeof(Stock), 1, archStock);
		fflush(archStock);
	}

	fclose(archStock);
	return TODO_OK;
}