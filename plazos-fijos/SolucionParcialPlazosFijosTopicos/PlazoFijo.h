#ifndef PLAZOFIJO_H
#define PLAZOFIJO_H

#include "../Fecha/Fecha.h"

typedef struct
{
	int nroPF;
	int cuenta;
	float monto;
	float interesAnual;
	Fecha fechaConstitucion;
	int dias;
}
PlazoFijo;


typedef struct
{
	int cuenta;
	char cliente[201];
	float saldo;
}
Cuenta;


#endif // PLAZOFIJO_H
