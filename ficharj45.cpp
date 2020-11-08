#include "ficharj45.h"
#include<basededatos.h>
#include<QDebug>

FichaRJ45::FichaRJ45()
{

}

string FichaRJ45::getComunOBlindada(){
    return this->_strComunOBlindada;
}
void FichaRJ45::setComunOBlindada(string comunoblindada){
    this->_strComunOBlindada = comunoblindada;
}

bool FichaRJ45::Equals(FichaRJ45 rj45){
    return this->_modelo == rj45.getModelo();
}

void FichaRJ45::crearTablaRJ45()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS ficharj45("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "comunoblindada VARCHAR (10),"
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

void FichaRJ45::insertarRJ45()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetComunOBlindada = QString::fromStdString(getComunOBlindada());
    QString qgetCantidad = QString::fromStdString(std::to_string(getCantidad()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);


    QSqlQuery query;
    query.prepare("INSERT INTO ficharj45 (marca, modelo, comunoblindada, cantidad, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :comunoblindada, :cantidad, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":comunoblindada", qgetComunOBlindada);
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

void FichaRJ45::borrarListaRJ45()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM ficharj45");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void FichaRJ45::actualizarRJ45()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetComunOBlindada = QString::fromStdString(getComunOBlindada());
    QString qgetCantidad = QString::fromStdString(std::to_string(getCantidad()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QString qgetId = QString::number(getId());

    QSqlQuery query;
    query.prepare("UPDATE ficharj45 SET marca = :marca, modelo = :modelo, comunoblindada = :comunoblindada, cantidad = :cantidad, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
    query.bindValue(":marca", qgetMarca);
    qDebug()<<qgetId;
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":comunoblindada", qgetComunOBlindada);
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

void FichaRJ45::borrarRJ45()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM ficharj45 WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}
string FichaRJ45::EstablecerTipo(){
    return "Ficha RJ45";
}

string FichaRJ45::MostrarDatos(){
    return EstablecerTipo()+ "marca: "+getMarca()+" modelo: "+getModelo()+" tipo: "+getComunOBlindada()+ " cantidad: "+std::to_string(getCantidad())
            +" precio en dólares: "+std::to_string(getPrecioEnDolares())+
                        " precio en pesos: "+std::to_string(getPrecioEnPesos())+" precio con IVA: "+std::to_string(getPrecioIVA());
}
