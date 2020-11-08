#ifndef PRECIOENPESOS_H
#define PRECIOENPESOS_H


class PrecioEnPesos
{
public:
    PrecioEnPesos();
    void CalcularPrecio(double p, double d);
    double Resultado();
protected:
    double r;
};

#endif // PRECIOENPESOS_H
