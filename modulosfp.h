#ifndef MODULOSFP_H
#define MODULOSFP_H
#include <conector.h>
#include <string>
#include<basededatos.h>

class ModuloSFP : public Conector
{
public:
    ModuloSFP();
    string getModo();
    void setModo(string modo);
    int getKilometrosSoportados();
    void setKilometrosSoportados(int km);
    bool Equals(ModuloSFP sfp);
    string EstablecerTipo();
    string MostrarDatos();
    void crearTablaSFP();
    void insertarSFP();
    void borrarListaSFP();
    void actualizarSFP();
    void borrarSFP();
protected:
    string _strModo;
    int _intKM;
};

#endif // MODULOSFP_H
