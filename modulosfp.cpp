#include "modulosfp.h"
#include <string>
#include <QDebug>

ModuloSFP::ModuloSFP()
{

}

string ModuloSFP::getModo(){
    return this->_strModo;
}
void ModuloSFP::setModo(string modo){
    this->_strModo = modo;
}
int ModuloSFP::getKilometrosSoportados(){
    return this->_intKM;
}
void ModuloSFP::setKilometrosSoportados(int km){
    this->_intKM = km;
}
bool ModuloSFP::Equals(ModuloSFP sfp){
    return this->_modelo == sfp.getModelo();
}
string ModuloSFP::EstablecerTipo(){
    return "Módulo SFP";
}
string ModuloSFP::MostrarDatos(){
    return EstablecerTipo()+" marca: "+getMarca()+" modelo: "+getModelo()+" modo: "+getModo()+" kilómetros soportados: "+std::to_string(getKilometrosSoportados())+
            " cantidad: "+std::to_string(getCantidad())+" precio en dólares: "+std::to_string(getPrecioEnDolares())+
            " precio en pesos: "+std::to_string(getPrecioEnPesos())+" precio con IVA: "+std::to_string(getPrecioIVA());
}

void ModuloSFP::crearTablaSFP()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS modulosfp("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "modo VARCHAR (10),"
                    "kmsoportados VARCHAR (10),"
                    "cantidad VARCHAR(5),"
                    "precious VARCHAR(20),"
                    "precioar VARCHAR(20),"
                    "precioiva VARCHAR(20)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Creación de tablas hecha correctamente";
    }
    else{
        qDebug()<<"Error en la creación de la base de datos";
        qDebug()<<"Error: "<<crear.lastError();
    }
}

void ModuloSFP::insertarSFP()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetModo = QString::fromStdString(getModo());
    QString qgetKmSoportados = QString::fromStdString(std::to_string(getKilometrosSoportados()));
    QString qgetCantidad = QString::fromStdString(std::to_string(getCantidad()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);



    QSqlQuery query;
    query.prepare("INSERT INTO modulosfp (marca, modelo, modo, kmsoportados, cantidad, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :modo, :kmsoportados, :cantidad, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":modo", qgetModo);
    query.bindValue(":kmsoportados", qgetKmSoportados);
    query.bindValue(":cantidad", qgetCantidad);
    query.bindValue(":precious", qgetPrecioUs);
    query.bindValue(":precioar", qgetPrecioAr);
    query.bindValue(":precioiva", qgetPrecioIVA);

    if(query.exec()){
        qDebug()<<"Insersión de datos hecha correctamente";
    }
    else{
        qDebug()<<"Error en la insersión de datos";
        qDebug()<<"Error: "<<query.lastError();
    }
}

void ModuloSFP::borrarListaSFP()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM modulosfp");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void ModuloSFP::actualizarSFP()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetModo = QString::fromStdString(getModo());
    QString qgetKmSoportados = QString::fromStdString(std::to_string(getKilometrosSoportados()));
    QString qgetCantidad = QString::fromStdString(std::to_string(getCantidad()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QString qgetId = QString::number(getId());
    QSqlQuery query;

    query.prepare("UPDATE modulosfp SET marca = :marca, modelo = :modelo, modo = :modo, kmsoportados = :kmsoportados, cantidad = :cantidad, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
    qDebug()<<qgetId;
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":modo", qgetModo);
    query.bindValue(":kmsoportados", qgetKmSoportados);
    query.bindValue(":cantidad", qgetCantidad);
    query.bindValue(":precious", qgetPrecioUs);
    query.bindValue(":precioar", qgetPrecioAr);
    query.bindValue(":precioiva", qgetPrecioIVA);
    query.bindValue(":id", qgetId);

    if(query.exec()){

        qDebug()<<"Actualización de datos hecha correctamente";
    }
    else{
        qDebug()<<"Error en la actualización de datos";
        qDebug()<<"Error: "<<query.lastError();
    }
}

void ModuloSFP::borrarSFP()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM modulosfp WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}
