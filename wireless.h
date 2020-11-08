#ifndef WIRELESS_H
#define WIRELESS_H
#include <string>
#include <dispositivo.h>

class Wireless : public Dispositivo
{
public:
    Wireless();
    string getBanda();
    void setBanda(string banda);
    string getTipoAntena();
    void setTipoAntena(string antena);
    int getDbi();
    void setDbi(int dbi);
    int getPotencia();
    void setPotencia(int potencia);
    bool Equals(Wireless wireless);
    string EstablecerTipo();
    string MostrarEnLista();
    string MostrarDatos();
    string IP();
    void crearTablaWireless();
    void insertarWireless();
    void borrarListaWireless();
    void borrarWireless();
    void actualizarWireless();
protected:
    string _strBanda;
    string _strTipoAntena;
    int _intDbi;
    int _intPotencia;
};

#endif // WIRELESS_H
