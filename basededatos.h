#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
//Librerias de bases de datos
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <string>

using namespace std;


class BaseDeDatos
{
public:
    BaseDeDatos();
    void crearBaseDeDatos();
    double valorDolar();
    QSqlQuery Consultar(QString recurso);
    QSqlQuery BuscarMarca(QString recursoB, QString marca);
    QSqlQuery BuscarModelo(QString recursoB, QString modelo);

private:
    QSqlDatabase db;
};

#endif // BASEDEDATOS_H
