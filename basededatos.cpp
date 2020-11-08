#include "basededatos.h"
#include <QDebug>
#include<QVariant>

BaseDeDatos::BaseDeDatos()
{


}

QSqlQuery BaseDeDatos::Consultar(QString recurso)
{
        QString consulta;
        consulta.append("SELECT `_rowid_`,* FROM "+recurso+" ORDER BY `_rowid_` DESC");
        QSqlQuery consultar;
        consultar.prepare(consulta);
        if(consultar.exec()){
            qDebug()<<"Se ha consultado correctamente";
        }
        else{
            qDebug()<<"Error en la consulta a la base de datos";
            qDebug()<<"Error: "<<consultar.lastError();
        }

        return consultar;
}

QSqlQuery BaseDeDatos::BuscarMarca(QString recursoB, QString marca)
{
    QSqlQuery consulta;
        consulta.prepare("SELECT `_rowid_`,* FROM "+recursoB+" WHERE marca = '"+marca+"' ORDER BY `_rowid_` DESC");

    if(consulta.exec()){
        qDebug()<<"Se ha consultado correctamente";
    }
    else{
        qDebug()<<"Error en la consulta a la base de datos";
        qDebug()<<"Error: "<<consulta.lastError();
    }
    return consulta;
}

QSqlQuery BaseDeDatos::BuscarModelo(QString recursoB, QString modelo)
{
    QSqlQuery consulta;
        consulta.prepare("SELECT `_rowid_`,* FROM "+recursoB+" WHERE modelo = '"+modelo+"' ORDER BY `_rowid_` DESC");

    if(consulta.exec()){
        qDebug()<<"Se ha consultado correctamente";
    }
    else{
        qDebug()<<"Error en la consulta a la base de datos";
        qDebug()<<"Error: "<<consulta.lastError();
    }
    return consulta;
}

void BaseDeDatos::crearBaseDeDatos()
{
    qDebug()<<"Base de datos creada.";
    QString datos;
    datos.append("db.sqlite");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(datos);

    if(db.open()){
        qDebug()<<"Base de datos conectada.";
    }
    else{
        qDebug()<<"Error conectando a la base de datos.";
    }
}

double BaseDeDatos::valorDolar()
{
    QString consulta;
    QString valordolar;
    consulta.append("SELECT valor FROM monedas WHERE id = '0'");
    QSqlQuery consultar;
    consultar.prepare(consulta);
    if(consultar.exec()){
        qDebug()<<"Se ha consultado correctamente";
    }
    else{
        qDebug()<<"Error en la consulta a la base de datos";
        qDebug()<<"Error: "<<consultar.lastError();
    }
    while(consultar.next()){
    valordolar = consultar.value(0).toByteArray().constData();
    }
    return valordolar.toDouble();
}
