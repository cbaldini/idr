#include "precioconiva.h"

PrecioConIVA::PrecioConIVA()
{

}

void PrecioConIVA::CalcularPrecio(double a){
    r = a*1.2;
}
double PrecioConIVA::Resultado(){
    return r;
}
