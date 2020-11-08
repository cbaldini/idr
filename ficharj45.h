#ifndef FICHARJ45_H
#define FICHARJ45_H
#include<conector.h>
#include<string>

class FichaRJ45 : public Conector
{
public:
    FichaRJ45();
    string MostrarDatos();
    string EstablecerTipo();
    string getComunOBlindada();
    void setComunOBlindada(string comunoblindada);
    bool Equals(FichaRJ45 rj45);
    void crearTablaRJ45();
    void insertarRJ45();
    void borrarListaRJ45();
    void actualizarRJ45();
    void borrarRJ45();
protected:
    string _strComunOBlindada;
};

#endif // FICHARJ45_H
