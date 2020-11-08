#ifndef CABLEDEFIBRA_H
#define CABLEDEFIBRA_H
#include <string>
#include <cable.h>
#include<basededatos.h>

using namespace std;

class CableDeFibra : public Cable
{
public:
    CableDeFibra();
    string MostrarDatos();
    string MostrarLista();
    string getModo();
    string EstablecerTipo();
    bool Equals(CableDeFibra fibra);
    int getPelos();
    void setModo(string modo);
    void setPelos(int pelos);
    void crearTablaFibra();
    void insertarFibra();
    void borrarListaFibra();
    void actualizarFibra();
    void borrarFibra();
protected:
    string _strModo;
    int _intPelos;
};
#endif // CABLEDEFIBRA_H
