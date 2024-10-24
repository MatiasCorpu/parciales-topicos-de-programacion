#ifndef SOLUCIONPARCIALPLAZOSFIJOS_H
#define SOLUCIONPARCIALPLAZOSFIJOS_H

#include "PlazoFijo.h"


PlazoFijo* cargarVectorPF(const char* nombrePlazosFijos, int* ce);
void procesarPF(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso);
bool insertarPFEnVectorOrd(PlazoFijo* plazosFijosVec, int* ce, PlazoFijo* plazoFijo);
void generarArchivos(const char* nombreCuentas, const char* nombrePlazosFijos);
void mostrarCuentas(const char* nombreArchCuentas);
void mostrarCuenta(const Cuenta* cuenta);

/// Vector
typedef int (*Cmp)(const void*, const void*);
void ordenarVector(void* vec, int ce, size_t tamElem, Cmp cmp);
void intercambiar(void* elem1, void* elem2, size_t tamElem);


#endif // SOLUCIONPARCIALPLAZOSFIJOS_H
