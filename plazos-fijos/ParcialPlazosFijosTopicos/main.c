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


int main(int argc, char* argv[])
{
	generarArchivos(argv[1], argv[2]);

	if(argc != 4)
	{
		puts("Cantidad incorrecta de parámetros.");
		return 1;
	}

	puts("Cuentas antes de actualizar:");
	mostrarCuentas(argv[1]);

	FILE* cuentasDat = fopen(argv[1], "r+b");

	if(!cuentasDat)
		return 2;

	Fecha fechaProceso;
	int fechaOk = txtAFecha(argv[3], &fechaProceso);

	if(!fechaOk)
		return 3;

	PlazoFijo* plazosFijosVec = NULL;
	int ce;

	plazosFijosVec = cargarVectorPF(argv[2], &ce);

	procesarPF(cuentasDat, plazosFijosVec, ce, &fechaProceso);

	fclose(cuentasDat);

	puts("\nCuentas despues de actualizar:");
	mostrarCuentas(argv[1]);

    return 0;
}
