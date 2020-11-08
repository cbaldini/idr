#include "parametros.h"
#include "precioenpesos.h"
#include "precioconiva.h"
#include "ui_parametros.h"
#include<QDebug>

Parametros::Parametros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametros)
{
    ui->setupUi(this);
    QString consulta;
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
    ui->leDolar->clear();
    ui->leDolar->insert(consultar.value(0).toByteArray().constData());
    }
}

double Parametros::getDolar(){
    return this->_dblDolar;
}

void Parametros::setDolar(double dolar){
    this->_dblDolar = dolar;
}

void Parametros::on_buttonBox_rejected()
{
    close();
}

void Parametros::on_buttonBox_accepted()
{
    setDolar(ui->leDolar->text().toDouble());
    crearTablaMonedas();
    actualizarMoneda();
}

int Parametros::getId()
{
    return this->_id;
}

void Parametros::setId(int id)
{
    this->_id = id;
}

//SQLITE DATABASE
void Parametros::crearTablaMonedas()
{
        QString consulta;
        consulta.append("CREATE TABLE IF NOT EXISTS monedas("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "moneda VARCHAR(10),"
                        "valor VARCHAR(10)"
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

void Parametros::insertarMoneda()
{
    QString qgetMoneda = QString::fromStdString("dolar");
    QString qgetDolar = QString::number(getDolar(), 'f', 2);

    QSqlQuery query;
    query.prepare("INSERT INTO monedas (moneda, valor)"
                  "VALUES(:moneda, :valor)");
    query.bindValue(":moneda", qgetMoneda);
    query.bindValue(":valor", qgetDolar);
    if(query.exec()){
        qDebug()<<"Insersión de datos hecha correctamente";
    }
    else{
        qDebug()<<"Error en la insersión de datos";
        qDebug()<<"Error: "<<query.lastError();
    }
}

void Parametros::borrarMonedas()
{
    QSqlQuery borrar;
    borrar.prepare("DELETE FROM monedas");
    if(borrar.exec()){
        qDebug()<<"Borrado de tablas ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado de la tabla";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void Parametros::borrarMoneda()
{
    QString qgetId = QString::number(getId());
    QSqlQuery borrar;
    borrar.bindValue(":id", qgetId);
    qDebug()<<qgetId;
    borrar.prepare("DELETE FROM monedas WHERE `_rowid_`="+qgetId);
    if(borrar.exec()){
        qDebug()<<"Borrado de registro ejecutado correctamente";
    }
    else{
        qDebug()<<"Error en el borrado del registro";
        qDebug()<<"Error: "<<borrar.lastError();
    }
}

void Parametros::actualizarMoneda()
{
    QString qgetMoneda = QString::fromStdString("dolar");
    QString qgetDolar = QString::number(getDolar(), 'f', 2);
    QString qgetId = QString::number(getId());

    QSqlQuery query;

    query.prepare("UPDATE monedas SET moneda = :moneda, valor = :valor WHERE id = :id");
    query.bindValue(":moneda", qgetMoneda);
    qDebug()<<qgetId;
    query.bindValue(":valor", qgetDolar);
    query.bindValue(":id", qgetId);

    if(query.exec()){

        qDebug()<<"Actualización de datos hecha correctamente";
    }
    else{
        qDebug()<<"Error en la actualización de datos";
        qDebug()<<"Error: "<<query.lastError();
    }
}
