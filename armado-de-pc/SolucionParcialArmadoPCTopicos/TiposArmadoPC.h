#ifndef TIPOS_H
#define TIPOS_H


typedef struct
{
    char codigo[21];
    char descripcion[51];
    int stock;
    double precioUnitario;
}
t_Componente;


typedef struct
{
    int nroOp;
    char codigo[21];
    int cantidad;
    double precioUnitario;
}
ArmadoYRep;


typedef struct
{
    char codigo[21];
    int nroReg;
}
IndComponente;


#endif // TIPOS_H
