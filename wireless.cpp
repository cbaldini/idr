#include "wireless.h"
#include <basededatos.h>
#include<QDebug>

Wireless::Wireless()
{

}

string Wireless::getBanda(){
    return this->_strBanda;
}
void Wireless::setBanda(string banda){
    this->_strBanda = banda;
}
string Wireless::getTipoAntena(){
    return this->_strTipoAntena;
}
void Wireless::setTipoAntena(string antena){
    this->_strTipoAntena = antena;
}
int Wireless::getDbi(){
    return this->_intDbi;
}
void Wireless::setDbi(int dbi){
    this->_intDbi = dbi;
}
int Wireless::getPotencia(){
    return this->_intPotencia;
}
void Wireless::setPotencia(int potencia){
    this->_intPotencia = potencia;
}
bool Wireless::Equals(Wireless wireless){
    return this->_modelo == wireless.getModelo();
}
string Wireless::EstablecerTipo(){
    return "Dispositivo wireless";
}

string Wireless::MostrarEnLista(){
    return EstablecerTipo()+", marca "+getMarca()+", modelo "+getModelo();
}

string Wireless::MostrarDatos(){
    return EstablecerTipo()+ "marca: "+getMarca()+" modelo: "+getModelo()+" banda; "+getBanda()+" tipo de antena: "+getTipoAntena()+
            " dbi: "+std::to_string(getDbi())+" potencia del equipo: "+std::to_string(getPotencia())+" IP:"+IP()+" Usuario: "+getUser()+" Clave: "+getPass()+
            ". Precio en dolares: "+std::to_string(getPrecioEnDolares())+". Precio en pesos: "+std::to_string(getPrecioEnPesos())+". Precio con IVA: "+std::to_string(getPrecioIVA());
}

string Wireless::IP()
{
    return std::to_string(getIPbyte1())+"."+std::to_string(getIPbyte2())+"."+std::to_string(getIPbyte3())+"."+std::to_string(getIPbyte4());
}

void Wireless::crearTablaWireless()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS wireless("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "marca VARCHAR(50),"
                    "modelo VARCHAR(50),"
                    "bocas VARCHAR(3),"
                    "funcion VARCHAR(20),"
                    "ip VARCHAR(20),"
                    "potencia VARCHAR(3),"
                    "banda VARCHAR(8),"
                    "antena VARCHAR(20),"
                    "dbi VARCHAR(3),"
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

void Wireless::insertarWireless()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetBocas = QString::fromStdString(std::to_string(getCantidadBocas()));
    QString qgetFuncion = QString::fromStdString(getFuncion());
    QString qgetIP = QString::fromStdString(IP());
    QString qgetUser = QString::fromStdString(getUser());
    QString qgetPass = QString::fromStdString(getPass());
    QString qgetPotencia = QString::fromStdString(std::to_string(getPotencia()));
    QString qgetBanda = QString::fromStdString(getBanda());
    QString qgetAntena = QString::fromStdString(getTipoAntena());
    QString qgetDbi = QString::fromStdString(std::to_string(getDbi()));
    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);


    QSqlQuery query;
    query.prepare("INSERT INTO wireless (marca, modelo, bocas, funcion, ip, potencia, banda, antena, dbi, user, pass, precious, precioar, precioiva)"
                  "VALUES(:marca, :modelo, :bocas, :funcion, :ip, :potencia, :banda, :antena, :dbi, :user, :pass, :precious, :precioar, :precioiva)");
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":bocas", qgetBocas);
    query.bindValue(":funcion", qgetFuncion);
    query.bindValue(":ip", qgetIP);
    query.bindValue(":potencia", qgetPotencia);
    query.bindValue(":banda", qgetBanda);
    query.bindValue(":antena", qgetAntena);
    query.bindValue(":dbi", qgetDbi);
    query.bindValue(":user", qgetUser);
    query.bindValue(":pass", qgetPass);
    query.bindValue(":precious", qgetPrecioUs);
    query.bindValue(":precioar", qgetPrecioAr);
    query.bindValue(":precioiva", qgetPrecioIVA);
    query.exec();
}

void Wireless::actualizarWireless()
{
    QString qgetMarca = QString::fromStdString(getMarca());
    QString qgetModelo = QString::fromStdString(getModelo());
    QString qgetBocas = QString::fromStdString(std::to_string(getCantidadBocas()));
    QString qgetFuncion = QString::fromStdString(getFuncion());
    QString qgetIP = QString::fromStdString(IP());
    QString qgetUser = QString::fromStdString(getUser());
    QString qgetPass = QString::fromStdString(getPass());
    QString qgetPotencia = QString::fromStdString(std::to_string(getPotencia()));
    QString qgetBanda = QString::fromStdString(getBanda());
    QString qgetAntena = QString::fromStdString(getTipoAntena());
    QString qgetDbi = QString::fromStdString(std::to_string(getDbi()));    QString qgetPrecioUs = QString::number(getPrecioEnDolares(), 'f', 2);
    QString qgetPrecioAr = QString::number(getPrecioEnPesos(), 'f', 2);
    QString qgetPrecioIVA = QString::number(getPrecioIVA(), 'f', 2);
    QString qgetId = QString::number(getId());

    QSqlQuery query;

    query.prepare("UPDATE wireless SET marca = :marca, modelo = :modelo, bocas = :bocas, funcion = :funcion, ip = :ip, potencia = :potencia, banda = :banda, antena = :antena, dbi = :dbi, user = :user, pass = :pass, precious = :precious, precioar = :precioar, precioiva = :precioiva WHERE id = :id");
    qDebug()<<qgetId;
    query.bindValue(":marca", qgetMarca);
    query.bindValue(":modelo", qgetModelo);
    query.bindValue(":bocas", qgetBocas);
    query.bindValue(":funcion", qgetFuncion);
    query.bindValue(":ip", qgetIP);
    query.bindValue(":potencia", qgetPotencia);
    query.bindValue(":banda", qgetBanda);
    query.bindValue(":antena", qgetAntena);
    query.bindValue(":dbi", qgetDbi);
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

void Wireless::borrarListaWireless()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM wireless");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void Wireless::borrarWireless(){

    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM wireless WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}
