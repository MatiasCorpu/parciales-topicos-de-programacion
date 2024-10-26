#ifndef SOLUCIONPARCIALARMADOPC_H
#define SOLUCIONPARCIALARMADOPC_H

#include "../Vector/Vector.h"


#define TODO_OK			0
#define ERR_CARGA_IND	1


void generarArchivoStockComponentes(const char* pathComponentes);
void generarArchivoArmadosYReparaciones(const char* pathArmYRep);
void mostrarArchivoComponentes(const char* pathComponentes);
void mostrarArchivoArmadoYRep(const char* pathArm);
void cargarArmadosYRepEnVector(const char* pathArmYRep, Vector* vec);
int actualizarComponentes(const char* nombreComponentes, const char* nombreArmadoYRep);
void obtenerPathIdx(const char* pathComponentes, char* pathComponentesIdx);


#endif
