#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H
#include <string>
#include <recurso.h>

using namespace std;

class Dispositivo : public Recurso
{
public:
    Dispositivo();

    string getFuncion();
    void setFuncion(string funcion);
    int getCantidadBocas();
    void setCantidadBocas(int cantidadbocas);
    int getIPbyte1();
    void setIPbyte1(int byte1);
    int getIPbyte2();
    void setIPbyte2(int byte2);
    int getIPbyte3();
    void setIPbyte3(int byte3);
    int getIPbyte4();
    void setIPbyte4(int byte4);
    bool VerificarIP(int byte);
    string getUser();
    string getPass();
    void setUser(string user);
    void setPass(string pass);
protected:
    string _strUser;
    string _strPass;
    string _strFuncionDispositivo;
    int _intCantidadBocas;
    int _byte1, _byte2, _byte3, _byte4;
};

#endif // DISPOSITIVO_H
