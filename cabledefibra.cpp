#include "cabledefibra.h"
#include<QDebug>

CableDeFibra::CableDeFibra()
{
}

string CableDeFibra::EstablecerTipo()
        {
            return "Cable de fibra óptica";
        }

string CableDeFibra::getModo(){
    return this->_strModo;
}

void CableDeFibra::setModo(string modo){
    this->_strModo = modo;
   }

int CableDeFibra::getPelos(){
    return this->_intPelos;
}

void CableDeFibra::setPelos(int pelos){
    this->_intPelos = pelos;
   }

bool CableDeFibra::Equals(CableDeFibra fibra)
        {
    return (this->_modelo == fibra.getModelo());
}

string CableDeFibra::MostrarDatos(){
    return EstablecerTipo()+ " marca "+getMarca()+ ", modelo "+getModelo()+ " Modo: " +getModo()+" con "+std::to_string(getPelos())+" pelos"
            +". Precio en dolares: "+std::to_string(getPrecioEnDolares())+". Precio en pesos: "+std::to_string(getPrecioEnPesos())
            +". Precio con IVA: "+std::to_string(getPrecioIVA());
}

void CableDeFibra::crearTablaFibra()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS cablefibra("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "metros VARCHAR(5),"
                    "modo VARCHAR (10),"
                    "pelos VARCHAR (10),"
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

void CableDeFibra::insertarFibra()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetMetros = QString::fromStdString(std::to_string(getMetros()));
    QString qgetModo = QString::fromStdString(getModo());
    QString qgetPelos = QString::fromStdString(std::to_string(getPelos()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);



    QSqlQuery query;
    query.prepare("INSERT INTO cablefibra (marca, modelo, metros, modo, pelos, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :metros, :modo, :pelos, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":metros", qgetMetros);
    query.bindValue(":modo", qgetModo);
    query.bindValue(":pelos", qgetPelos);
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

void CableDeFibra::borrarListaFibra()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM cablefibra");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void CableDeFibra::actualizarFibra()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetMetros = QString::fromStdString(std::to_string(getMetros()));
    QString qgetModo = QString::fromStdString(getModo());
    QString qgetPelos = QString::fromStdString(std::to_string(getPelos()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QString qgetId = QString::number(getId());
    QSqlQuery query;

    query.prepare("UPDATE cablefibra SET marca = :marca, modelo = :modelo, metros = :metros, modo = :modo, pelos = :pelos, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
    query.bindValue(":marca", qgetMarca);
    qDebug()<<qgetId;
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":metros", qgetMetros);
    query.bindValue(":modo", qgetModo);
    query.bindValue(":pelos", qgetPelos);
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

void CableDeFibra::borrarFibra()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM cablefibra WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}
