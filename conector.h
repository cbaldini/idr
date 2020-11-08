#ifndef CONECTOR_H
#define CONECTOR_H
#include <recurso.h>
#include <string>

class Conector : public Recurso
{
public:
    Conector();
    int getCantidad();
    void setCantidad(int cantidad);
protected:
    int _intCantidad;
};

#endif // CONECTOR_H
