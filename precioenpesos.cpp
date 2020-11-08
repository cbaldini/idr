#include "precioenpesos.h"

PrecioEnPesos::PrecioEnPesos()
{

}

void PrecioEnPesos::CalcularPrecio(double d, double p){
    r = d*p;
}
double PrecioEnPesos::Resultado(){
    return r;
}
