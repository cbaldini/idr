#ifndef SWITCH_H
#define SWITCH_H
#include<string>
#include <basededatos.h>
#include<dispositivo.h>

using namespace std;

class Switch : public Dispositivo
{
public:
    Switch();
    string getGestionable();
    void setGestionable(string gestionable);
    bool Equals(Switch unswitch);
    string EstablecerTipo();
    string IP();
    string MostrarDatos();
    void crearTablaSwitches();
    void insertarSwitch();
    void borrarListaSwitches();
    void actualizarSwitch();
    void borrarSwitch();

protected:
    string _strGestionable;
};

#endif // SWITCH_H
