#ifndef CABLEETHERNET_H
#define CABLEETHERNET_H
#include <string>
#include <cable.h>
#include<basededatos.h>

using namespace std;

class CableUTP : public Cable
{
public:
    CableUTP();
    string MostrarDatos();
    string MostrarLista();
    string EstablecerTipo();
    string getVaina();
    void setVaina(string vaina);
    string getInteriorExterior();
    void setInteriorExterior(string intext);
    void crearTablaUTP();
    void insertarUTP();
    void borrarListaUTP();
    void actualizarUTP();
    void borrarUTP();
protected:
    string _strVaina;
    string _strIntOExt;
};

#endif // CABLEETHERNET_H
