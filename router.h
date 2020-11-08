#ifndef ROUTER_H
#define ROUTER_H
#include<string>
#include <basededatos.h>
#include<dispositivo.h>

using namespace std;

class Router : public Dispositivo
{
public:
    Router();
    bool Equals(Router unrouter);
    string EstablecerTipo();
    string IP();
    string MostrarEnLista();
    string MostrarDatos();
    void crearTablaRouters();
    void insertarRouter();
    void borrarRouter();
    void borrarRouters();
    void actualizarRouter();
};

#endif // ROUTER_H
