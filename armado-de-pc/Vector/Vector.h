#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stddef.h>
#include <stdbool.h>


#define TODO_OK     0
#define VEC_LLENO   1
#define DUPLICADO   2
#define SIN_MEM     3


typedef struct
{
	void* vec;
	int ce;
	int cap;
	size_t tamElem;
}
Vector;


typedef int (*Cmp)(const void*, const void*);
typedef void (*Actualizar)(void*, const void*);
typedef void (*Accion)(void*, void*);


int crearVector(Vector* vec, int cap, size_t tamElem);
void destruirVector(Vector* vec);
int insertarEnVectorOrd(Vector* v, void* elem, Cmp cmp, Actualizar actualizar);
void grabarVector(Vector* v, const char* nombreArch);
void recorrerVector(const Vector* v, Accion accion, void* datosAccion);
void cargarVector(const char* nombreArch, Vector* vector, size_t tamElem);
bool buscarEnVectorOrd(const Vector* v, void* elem, Cmp cmp);


#endif //VECTOR_VECTOR_H
