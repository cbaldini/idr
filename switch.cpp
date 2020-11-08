#include "switch.h"
#include <basededatos.h>
#include<QDebug>


Switch::Switch()
{

}

string Switch::getGestionable(){
    return this->_strGestionable;
}
void Switch::setGestionable(string gestionable){
    this->_strGestionable = gestionable;
}
bool Switch::Equals(Switch unswitch){
    return this->_modelo == unswitch.getModelo();
}
string Switch::EstablecerTipo(){
    return "Switch";
}

string Switch::IP()
{
    return std::to_string(getIPbyte1())+"."+std::to_string(getIPbyte2())+"."+std::to_string(getIPbyte3())+"."+std::to_string(getIPbyte4());

}
string Switch::MostrarDatos(){
    return EstablecerTipo()+" marca: "+getMarca()+" modelo: "+getModelo()+" funcion: "+getFuncion()+" "+getGestionable()+ " IP: "+IP()+" User: "+getUser()+" Pass: "+getPass()+" cantidad de bocas: "+std::to_string(getCantidadBocas())+"precio en dolares"+std::to_string(getPrecioEnDolares())+" precio en pesos: "+std::to_string(getPrecioEnPesos())+" precio con iva: "+std::to_string(getPrecioIVA());
}

void Switch::crearTablaSwitches()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS switches("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "bocas VARCHAR(3),"
                    "funcion VARCHAR(20),"
                    "ip VARCHAR(20),"
                    "gestionable VARCHAR(15),"
                    "user VARCHAR(20),"
                    "pass VARCHAR(20),"
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

void Switch::insertarSwitch()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetBocas = QString::fromStdString(std::to_string(getCantidadBocas()));
    QString qgetFuncion = QString::fromStdString(getFuncion());
    QString qgetIP = QString::fromStdString(IP());
    QString qgetUser = QString::fromStdString(getUser());
    QString qgetPass = QString::fromStdString(getPass());
    QString qgetGestionable = QString::fromStdString(getGestionable());
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QSqlQuery query;

    query.prepare("INSERT INTO switches (marca, modelo, bocas, funcion, ip, gestionable, user, pass, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :bocas, :funcion, :ip, :gestionable, :user, :pass, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":bocas", qgetBocas);
    query.bindValue(":funcion", qgetFuncion);
    query.bindValue(":ip", qgetIP);
    query.bindValue(":gestionable", qgetGestionable);
    query.bindValue(":user", qgetUser);
    query.bindValue(":pass", qgetPass);
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

void Switch::borrarListaSwitches()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM switches");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void Switch::actualizarSwitch()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetBocas = QString::fromStdString(std::to_string(getCantidadBocas()));
    QString qgetFuncion = QString::fromStdString(getFuncion());
    QString qgetIP = QString::fromStdString(IP());
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QString qgetId = QString::number(getId());
    QString qgetGestionable = QString::fromStdString(getGestionable());
    QString qgetUser = QString::fromStdString(getUser());
    QString qgetPass = QString::fromStdString(getPass());
    QSqlQuery query;

    query.prepare("UPDATE switches SET marca = :marca, modelo = :modelo, bocas = :bocas, funcion = :funcion, ip = :ip, gestionable = :gestionable, user = :user, pass = :pass, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
    query.bindValue(":marca", qgetMarca);
    qDebug()<<qgetId;
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":bocas", qgetBocas);
    query.bindValue(":funcion", qgetFuncion);
    query.bindValue(":ip", qgetIP);
    query.bindValue(":gestionable", qgetGestionable);
    query.bindValue(":user", qgetUser);
    query.bindValue(":pass", qgetPass);
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

void Switch::borrarSwitch()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM switches WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}
