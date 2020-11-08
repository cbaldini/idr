#include "dispositivo.h"
#include <string>

using namespace std;

Dispositivo::Dispositivo()
{

}

string Dispositivo::getFuncion(){
    return this->_strFuncionDispositivo;
}

string Dispositivo::getUser(){
    return this->_strUser;
}

void Dispositivo::setUser(string user){
    this->_strUser = user;
}

string Dispositivo::getPass(){
    return this->_strPass;
}

void Dispositivo::setPass(string pass){
    this->_strPass = pass;
}

void Dispositivo::setFuncion(string funcion){
    this->_strFuncionDispositivo = funcion;
}
int Dispositivo::getCantidadBocas(){
    return this->_intCantidadBocas;
}
void Dispositivo::setCantidadBocas(int cantidadbocas){
    this->_intCantidadBocas = cantidadbocas;
}
int Dispositivo::getIPbyte1(){
    return this->_byte1;
}
void Dispositivo::setIPbyte1(int byte1){
    this->_byte1 = byte1;
}
int Dispositivo::getIPbyte2(){
    return this->_byte2;
}
void Dispositivo::setIPbyte2(int byte2){
    this->_byte2 = byte2;
}
int Dispositivo::getIPbyte3(){
    return this->_byte3;
}
void Dispositivo::setIPbyte3(int byte3){
    this->_byte3 = byte3;
}
int Dispositivo::getIPbyte4(){
    return this->_byte4;
}
void Dispositivo::setIPbyte4(int byte4){
    this->_byte4 = byte4;
}

bool Dispositivo::VerificarIP(int byte){
    if (byte < 255 && byte >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
