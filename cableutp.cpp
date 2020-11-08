#include "cableutp.h"
#include<QDebug>

CableUTP::CableUTP()
{

}

string CableUTP::EstablecerTipo()
        {
            return "Cable ethernet";
        }
string CableUTP::getVaina(){
    return this->_strVaina;
}
void CableUTP::setVaina(string vaina){
    this->_strVaina = vaina;
}
string CableUTP::getInteriorExterior(){
    return this->_strIntOExt;
}
void CableUTP::setInteriorExterior(string intext){
    this->_strIntOExt = intext;
}

void CableUTP::crearTablaUTP()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS cableutp("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "metros VARCHAR(5),"
                    "intoext VARCHAR (10),"
                    "vaina VARCHAR (10),"
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

void CableUTP::insertarUTP()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetMetros = QString::fromStdString(std::to_string(getMetros()));
    QString qgetIntOExt = QString::fromStdString(getInteriorExterior());
    QString qgetVaina = QString::fromStdString(getVaina());
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);



    QSqlQuery query;
    query.prepare("INSERT INTO cableutp (marca, modelo, metros, intoext, vaina, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :metros, :intoext, :vaina, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":metros", qgetMetros);
    query.bindValue(":intoext", qgetIntOExt);
    query.bindValue(":vaina", qgetVaina);
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

void CableUTP::borrarListaUTP()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM cableutp");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void CableUTP::actualizarUTP()
{
        QString qgetMarca = QString::fromStdString(getMarca());
        QString qgetModelo = QString::fromStdString(getModelo());
        QString qgetMetros = QString::fromStdString(std::to_string(getMetros()));
        QString qgetIntOExt = QString::fromStdString(getInteriorExterior());
        QString qgetVaina = QString::fromStdString(getVaina());
        QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
        QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
        QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
        QString qgetId = QString::number(getId());

        QSqlQuery query;

        query.prepare("UPDATE cableutp SET marca = :marca, modelo = :modelo, metros = :metros, intoext = :intoext, vaina = :vaina, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
        query.bindValue(":marca", qgetMarca);
        qDebug()<<qgetId;
        query.bindValue(":marca", qgetMarca);
        query.bindValue(":modelo", qgetModelo);
        query.bindValue(":metros", qgetMetros);
        query.bindValue(":intoext", qgetIntOExt);
        query.bindValue(":vaina", qgetVaina);
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

void CableUTP::borrarUTP()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM cableutp WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

string CableUTP::MostrarDatos(){
    return EstablecerTipo()+ " marca "+getMarca()+ ", modelo "+getModelo()+ " vaina: " +getVaina()+" "+getInteriorExterior()+". Precio en dólares: "+std::to_string(getPrecioEnDolares())+". Precio en pesos: "+std::to_string(getPrecioEnPesos())+". Precio con IVA: "+std::to_string(getPrecioIVA());
}

