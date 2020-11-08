#ifndef CABLE_H
#define CABLE_H
#include <recurso.h>
#include <string>

class Cable : public Recurso
{
public:
    Cable();
    int getMetros();
    int setMetros(int metros);
    string EstablecerTipo();
    bool Equals(Cable cable);
protected:
    int _intMetros;
};

#endif // CABLE_H
