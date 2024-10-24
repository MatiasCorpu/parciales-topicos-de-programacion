#ifndef FECHAS_H
#define FECHAS_H

#include <stdbool.h>


typedef struct
{
	int dia;
	int mes;
	int anio;
}
Fecha;


typedef struct
{
	int mes;
	int anio;
}
Mes;


bool esFechaValida(const Fecha* f);
Fecha sumarDiasAFecha(const Fecha* f, unsigned dias);
void sumarDiasAFechaInSitu(Fecha* f, unsigned dias);
int difEnDiasEntreFechas(const Fecha* f1, const Fecha* f2);
int diaDelAnio(const Fecha* f);
int cmpFechas(const Fecha* f1, const Fecha* f2);
int cmpMeses(const Mes* mes1, const Mes* mes2);
Mes getMes(const Fecha* f);
Mes strToMes(const char* str);
int cantDiasMes(int mes, int anio);
int txtAFecha(const char* txt, Fecha* fecha);


#endif // FECHAS_H
