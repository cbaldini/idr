#ifndef RECURSO_H
#define RECURSO_H
#include<string>


using namespace std;

class Recurso
{
public:
    Recurso();
    int getId();
    void setId(int id);
    string getMarca();
    void setMarca(string marca);
    string getModelo();
    void setModelo(string modelo);
    double getPrecioEnDolares();
    void setPrecioEnDolares(double preciodolares);
    double getPrecioEnPesos();
    void setPrecioEnPesos(double preciopesos);
    double getPrecioIVA();
    void setPrecioIVA(double precioiva);


protected:
    int _id;
    string _marca;
    string _modelo;
    double _preciodolares;
    double _preciopesos;
    double _precioiva;

};

#endif // RECURSO_H
