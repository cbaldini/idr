#ifndef PRECIOCONIVA_H
#define PRECIOCONIVA_H
#include<iprecio.h>

class PrecioConIVA
{
public:
    PrecioConIVA();
    void CalcularPrecio(double a);
    double Resultado();
protected:
    double r;
};

#endif // PRECIOCONIVA_H
