#include "recurso.h"
#include<string>
#include <itipo.h>

using namespace std;

Recurso::Recurso()
{
}

int Recurso::getId()
{
    return this->_id;
}

void Recurso::setId(int id)
{
    this->_id = id;
}

string Recurso::getMarca(){
    return this->_marca;
}
void Recurso::setMarca(string marca){
    this->_marca = marca;
}
string Recurso::getModelo(){
    return this->_modelo;
}
void Recurso::setModelo(string modelo){
    this->_modelo = modelo;
}
double Recurso::getPrecioEnDolares(){
    return this->_preciodolares;
}
void Recurso::setPrecioEnDolares(double preciodolares){
    this->_preciodolares = preciodolares;
}
double Recurso::getPrecioEnPesos(){
    return this->_preciopesos;
}
void Recurso::setPrecioEnPesos(double preciopesos){
    this->_preciopesos = preciopesos;
}
double Recurso::getPrecioIVA(){
    return this->_precioiva;
}
void Recurso::setPrecioIVA(double precioiva){
    this->_precioiva = precioiva;
}


