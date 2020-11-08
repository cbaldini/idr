#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parametros.h"
#include "router.h"
#include<string>
#include<precioenpesos.h>
#include<precioconiva.h>
#include<wireless.h>
#include<QDebug>
#include<basededatos.h>
#include<QMessageBox>
#include<switch.h>
#include<cableutp.h>
#include<cabledefibra.h>
#include<modulosfp.h>
#include<ficharj45.h>

using namespace std;

static Router *router = new Router();
static Wireless *wireless = new Wireless();
static Switch *switches = new Switch();
static CableUTP *cableutp = new CableUTP();
static CableDeFibra *cablefibra = new CableDeFibra();
static ModuloSFP *modulosfp = new ModuloSFP();
static FichaRJ45 *ficharj45 = new FichaRJ45();
static BaseDeDatos *basededatos;
static Parametros *parametro;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    BaseDeDatos::crearBaseDeDatos();
    mostrarDatosDbRouter();
    mostrarDatosDbWireless();
    mostrarDatosDbSwitch();
    mostrarDatosDbUTP();
    mostrarDatosDbFibra();
    mostrarDatosDbSFP();
    mostrarDatosDbRJ45();
    ui->qtwRouter->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwWireless->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwSwitch->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwUTP->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwFibra->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwSFP->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtwRJ45->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// TAB ROUTER ////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::mostrarDatosDbRouter()
{
    int fila=0;
    QSqlQuery consultar = basededatos->Consultar("routers");
    ui->qtwRouter->setRowCount(0);
    while(consultar.next()){
        ui->qtwRouter->insertRow(fila);
        ui->qtwRouter->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,9, new QTableWidgetItem(consultar.value(10).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,10, new QTableWidgetItem(consultar.value(11).toByteArray().constData()));
        fila++;
        }

}

void MainWindow::on_pbtnPrevisualizarR_clicked()
{
    PrecioEnPesos *routerenpesos = new PrecioEnPesos();
    PrecioConIVA *routerconiva = new PrecioConIVA();
    router->setMarca(ui->leMarcaRouter->text().toStdString());
    router->setModelo(ui->leModeloRouter->text().toStdString());
    router->setCantidadBocas(ui->leBocasR->text().toInt());
    router->setIPbyte1(ui->leIPr->text().toInt());
    router->setIPbyte2(ui->leIPr_2->text().toInt());
    router->setIPbyte3(ui->leIPr_3->text().toInt());
    router->setIPbyte4(ui->leIPr_4->text().toInt());
    router->setPrecioEnDolares(ui->lePrecioRouter->text().toDouble());
    routerenpesos->CalcularPrecio(ui->lePrecioRouter->text().toDouble(), parametro->getDolar());
    router->setPrecioEnPesos(routerenpesos->Resultado());
    routerconiva->CalcularPrecio(routerenpesos->Resultado());
    router->setPrecioIVA(routerconiva->Resultado());
    router->setFuncion(ui->leFuncion->text().toStdString());
    ui->qlwRouter->addItem(router->MostrarDatos().data());
}

void MainWindow::on_pbtnGuardarR_clicked()
{
    router->crearTablaRouters();
    PrecioEnPesos *routerenpesos = new PrecioEnPesos();
    PrecioConIVA *routerconiva = new PrecioConIVA();
    router->setMarca(ui->leMarcaRouter->text().toUpper().toStdString());
    router->setModelo(ui->leModeloRouter->text().toUpper().toStdString());
    router->setCantidadBocas(ui->leBocasR->text().toInt());
    bool siga1, siga2, siga3, siga4 = false;
    if(ui->leIPr->text()== nullptr && ui->leIPr_2->text()==nullptr && ui->leIPr_3->text()==nullptr && ui->leIPr_4->text()==nullptr){
        if(!ui->qtwRouter->selectedItems().empty()){
        int row = ui->qtwRouter->currentRow();
        QString strip = ui->qtwRouter->item(row,5)->text();
        QRegExp rx("(\\.)");
        QStringList query = strip.split(rx);
        router->setIPbyte1(query[0].toInt());
        router->setIPbyte2(query[1].toInt());
        router->setIPbyte3(query[2].toInt());
        router->setIPbyte4(query[3].toInt());
        }
        else{
            QMessageBox msgbx;
            msgbx.setText("Error inesperado.");
        }
        siga1 = true;
        siga2 = true;
        siga3 = true;
        siga4 = true;
    }
    else{
    if(router->VerificarIP(ui->leIPr->text().toInt())){
        router->setIPbyte1(ui->leIPr->text().toInt());
        siga1 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPr->clearFocus();
        siga1 = false;
    }
    if(router->VerificarIP(ui->leIPr_2->text().toInt())){
        router->setIPbyte2(ui->leIPr_2->text().toInt());
        siga2 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPr_2->clearFocus();
        siga2 = false;

    }
    if(router->VerificarIP(ui->leIPr_3->text().toInt())){
        router->setIPbyte3(ui->leIPr_3->text().toInt());
        siga3 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPr_3->clearFocus();
        siga3 = false;
    }
    if(router->VerificarIP(ui->leIPr_4->text().toInt())){
        router->setIPbyte4(ui->leIPr_4->text().toInt());
        siga4 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPr_4->clearFocus();
        siga4 = false;
    }
    }
    if (siga1 && siga2 && siga3 && siga4){
    router->setPrecioEnDolares(ui->lePrecioRouter->text().toDouble());
    routerenpesos->CalcularPrecio(ui->lePrecioRouter->text().toDouble(), basededatos->valorDolar());
    router->setPrecioEnPesos(routerenpesos->Resultado());
    routerconiva->CalcularPrecio(routerenpesos->Resultado());
    router->setPrecioIVA(routerconiva->Resultado());
    router->setFuncion(ui->leFuncion->text().toStdString());
    router->setUser(ui->leUserR->text().toStdString());
    router->setPass(ui->lePassR->text().toStdString());
    if(ui->qtwRouter->selectedItems().empty()){
    router->insertarRouter();
    }
    else{
    router->actualizarRouter();
    }
    mostrarDatosDbRouter();
    limpiarCamposRouter();
    }
}

void MainWindow::on_pbBorrarListaR_clicked()
{
    QMessageBox::StandardButton dialogo;
    dialogo = QMessageBox::question(this, "Borrar", "¿Seguro que desea borrar toda la lista?", QMessageBox::Yes|QMessageBox::No);
    if(dialogo == QMessageBox::Yes){
        router->borrarRouters();
        mostrarDatosDbRouter();
    }
}

void MainWindow::on_pbtnEditarR_clicked()
{
    limpiarCamposRouter();
    if(!ui->qtwRouter->selectedItems().empty()){
        int row = ui->qtwRouter->currentRow();
        router->setId(ui->qtwRouter->item(row, 0)->text().toInt());
        ui->leMarcaRouter->insert(ui->qtwRouter->item(row, 1)->text());
        ui->leModeloRouter->insert(ui->qtwRouter->item(row, 2)->text());
        ui->leBocasR->insert(ui->qtwRouter->item(row, 3)->text());
        ui->leFuncion->insert(ui->qtwRouter->item(row, 4)->text());
        QString strip = ui->qtwRouter->item(row,5)->text();
        QRegExp rx("(\\.)");
        QStringList query = strip.split(rx);
        ui->leIPr->insert(query[0]);
        ui->leIPr_2->insert(query[1]);
        ui->leIPr_3->insert(query[2]);
        ui->leIPr_4->insert(query[3]);
        ui->leUserR->insert(ui->qtwRouter->item(row, 6)->text());
        ui->lePassR->insert(ui->qtwRouter->item(row, 7)->text());
        ui->lePrecioRouter->insert(ui->qtwRouter->item(row, 8)->text());
    }
}

void MainWindow::on_pbtnBorrarR_clicked()
{
    int row = ui->qtwRouter->currentRow();
    router->setId(ui->qtwRouter->item(row, 0)->text().toInt());
    router->borrarRouter();
    mostrarDatosDbRouter();
}

void MainWindow::on_pbtnLimpiarR_clicked()
{
    limpiarCamposRouter();
}


void MainWindow::limpiarCamposRouter(){
    ui->qlwRouter->clear();
    ui->leMarcaRouter->clear();
    ui->leModeloRouter->clear();
    ui->leBocasR->clear();
    ui->leIPr->clear();
    ui->leIPr_2->clear();
    ui->leIPr_3->clear();
    ui->leIPr_4->clear();
    ui->leFuncion->clear();
    ui->lePrecioRouter->clear();
    ui->leBuscarR->clear();
    ui->leUserR->clear();
    ui->lePassR->clear();
}

// TAB WIRELESS /////////////////////////////////////////////////////////////////////////////

void MainWindow::mostrarDatosDbWireless()
{
    QSqlQuery consultar = basededatos->Consultar("wireless");
    int fila=0;
    ui->qtwWireless->setRowCount(0);
    while(consultar.next()){
        ui->qtwWireless->insertRow(fila);
        ui->qtwWireless->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,9, new QTableWidgetItem(consultar.value(10).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,10, new QTableWidgetItem(consultar.value(11).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,11, new QTableWidgetItem(consultar.value(12).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,12, new QTableWidgetItem(consultar.value(13).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,13, new QTableWidgetItem(consultar.value(14).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,14, new QTableWidgetItem(consultar.value(15).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnGuardarW_clicked()
{
    wireless->crearTablaWireless();
    PrecioEnPesos *wirelessenpesos = new PrecioEnPesos();
    PrecioConIVA *wirelessconiva = new PrecioConIVA();
    wireless->setMarca(ui->leMarcaW->text().toUpper().toStdString());
    wireless->setModelo(ui->leModeloW->text().toUpper().toStdString());
    wireless->setCantidadBocas(ui->leBocasW->text().toInt());
    bool siga1, siga2, siga3, siga4 = false;
    if(ui->leIPw->text()== nullptr && ui->leIPw_2->text()==nullptr && ui->leIPw_3->text()==nullptr && ui->leIPw_4->text()==nullptr){
        if(!ui->qtwWireless->selectedItems().empty()){
        int row = ui->qtwWireless->currentRow();
        QString strip = ui->qtwWireless->item(row,5)->text();
        QRegExp rx("(\\.)");
        QStringList query = strip.split(rx);
        wireless->setIPbyte1(query[0].toInt());
        wireless->setIPbyte2(query[1].toInt());
        wireless->setIPbyte3(query[2].toInt());
        wireless->setIPbyte4(query[3].toInt());
        }
        else{
            QMessageBox msgbx;
            msgbx.setText("Error inesperado.");
        }
        siga1 = true;
        siga2 = true;
        siga3 = true;
        siga4 = true;
    }
    else{
    if(wireless->VerificarIP(ui->leIPw->text().toInt())){
        wireless->setIPbyte1(ui->leIPw->text().toInt());
        siga1 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPw->clearFocus();
        siga1 = false;
    }
    if(wireless->VerificarIP(ui->leIPw_2->text().toInt())){
        wireless->setIPbyte2(ui->leIPw_2->text().toInt());
        siga2 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPw_2->clearFocus();
        siga2 = false;

    }
    if(wireless->VerificarIP(ui->leIPw_3->text().toInt())){
        wireless->setIPbyte3(ui->leIPw_3->text().toInt());
        siga3 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPw_3->clearFocus();
        siga3 = false;
    }
    if(wireless->VerificarIP(ui->leIPw_4->text().toInt())){
        wireless->setIPbyte4(ui->leIPw_4->text().toInt());
        siga4 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPw_4->clearFocus();
        siga4 = false;
    }
    }
    if (siga1 && siga2 && siga3 && siga4){
    wireless->setPotencia(ui->lePotencia->text().toInt());
    wireless->setBanda(ui->cboBanda->currentText().toStdString());
    wireless->setTipoAntena(ui->cboAntena->currentText().toStdString());
    wireless->setDbi(ui->leDbi->text().toInt());
    wireless->setUser(ui->leUserW->text().toStdString());
    wireless->setPass(ui->lePassW->text().toStdString());
    wireless->setPrecioEnDolares(ui->lePrecioW->text().toDouble());
    wirelessenpesos->CalcularPrecio(ui->lePrecioW->text().toDouble(), basededatos->valorDolar());
    wireless->setPrecioEnPesos(wirelessenpesos->Resultado());
    wirelessconiva->CalcularPrecio(wirelessenpesos->Resultado());
    wireless->setPrecioIVA(wirelessconiva->Resultado());    
    wireless->setFuncion(ui->leFuncionW->text().toStdString());
    if(ui->qtwWireless->selectedItems().empty()){
    wireless->insertarWireless();
    }
    else{
    wireless->actualizarWireless();
    }
    mostrarDatosDbWireless();
    limpiarCamposWireless();
    }
}

void MainWindow::on_pbtnBuscarW_clicked()
{
    QSqlQuery consulta;
    QString qBuscarW = ui->leBuscarW->text().toUpper();
    if(ui->cboBuscarW->currentText().toStdString() == "Modelo"){
    consulta = basededatos->BuscarModelo("wireless", qBuscarW);
    }
    else if(ui->cboBuscarW->currentText().toStdString() == "Marca"){
    consulta = basededatos->BuscarMarca("wireless", qBuscarW);
    }
    int fila=0;
    ui->qtwWireless->setRowCount(0);
    while(consulta.next()){
        ui->qtwWireless->insertRow(fila);
        ui->qtwWireless->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,9, new QTableWidgetItem(consulta.value(10).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,10, new QTableWidgetItem(consulta.value(11).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,11, new QTableWidgetItem(consulta.value(12).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,12, new QTableWidgetItem(consulta.value(13).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,13, new QTableWidgetItem(consulta.value(14).toByteArray().constData()));
        ui->qtwWireless->setItem(fila,14, new QTableWidgetItem(consulta.value(15).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnMostrarW_clicked()
{
    limpiarCamposWireless();
    mostrarDatosDbWireless();
}

void MainWindow::limpiarCamposWireless()
{
    ui->qlwWireless->clear();
    ui->leMarcaW->clear();
    ui->leModeloW->clear();
    ui->leBocasW->clear();
    ui->leIPw->clear();
    ui->leIPw_2->clear();
    ui->leIPw_3->clear();
    ui->leIPw_4->clear();
    ui->leFuncionW->clear();
    ui->lePrecioW->clear();
    ui->leDbi->clear();
    ui->lePotencia->clear();
    ui->cboAntena->setCurrentIndex(0);
    ui->cboBanda->setCurrentIndex(0);
    ui->leUserW->clear();
    ui->lePassW->clear();
}

// TAB SWITCH ///////////////////////////////////////////////////////////////////////////////

void MainWindow::mostrarDatosDbSwitch()
{
    QSqlQuery consultar = basededatos->Consultar("switches");
    int fila=0;
    ui->qtwSwitch->setRowCount(0);
    while(consultar.next()){
        ui->qtwSwitch->insertRow(fila);
        ui->qtwSwitch->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,9, new QTableWidgetItem(consultar.value(10).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,10, new QTableWidgetItem(consultar.value(11).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,11, new QTableWidgetItem(consultar.value(12).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::limpiarCamposSwitch()
{
    ui->qlwSwitch->clear();
    ui->leMarcaSwitch->clear();
    ui->leModeloSwitch->clear();
    ui->leBocasS->clear();
    ui->leIPs->clear();
    ui->leIPs_2->clear();
    ui->leIPs_3->clear();
    ui->leIPs_4->clear();
    ui->leFuncionS->clear();
    if(ui->rbGestionable->isChecked()){
        ui->rbGestionable->unsetCursor();
    }
    else if(ui->rbNoGestionable->isChecked()){
        ui->rbGestionable->unsetCursor();
    }
    ui->lePrecioS->clear();
    ui->leUserS->clear();
    ui->lePassS->clear();
}

void MainWindow::mostrarDatosDbUTP()
{
    QSqlQuery consultar = basededatos->Consultar("routers");
    int fila=0;
    ui->qtwUTP->setRowCount(0);
    while(consultar.next()){
        ui->qtwUTP->insertRow(fila);
        ui->qtwUTP->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,9, new QTableWidgetItem(consultar.value(10).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::limpiarCamposUTP()
{
    ui->qlwUTP->clear();
    ui->leMarcaUTP->clear();
    ui->leModeloUTP->clear();
    ui->leMetrosUTP->clear();
    if(ui->rbtExteriorUTP->isChecked()){
        ui->rbtExteriorUTP->unsetCursor();
    }
    else if(ui->rbtInteriorUTP->isChecked()){
        ui->rbtInteriorUTP->unsetCursor();
    }
    if(ui->rbtVainaDobleUTP->isChecked()){
        ui->rbtVainaDobleUTP->unsetCursor();
    }
    else if(ui->rbtVainaSimpleUTP->isChecked()){
        ui->rbtVainaSimpleUTP->unsetCursor();
    }
    ui->lePrecioUTP->clear();
}

void MainWindow::mostrarDatosDbFibra()
{
    QSqlQuery consultar = basededatos->Consultar("cablefibra");
    int fila=0;
    ui->qtwFibra->setRowCount(0);
    while(consultar.next()){
        ui->qtwFibra->insertRow(fila);
        ui->qtwFibra->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::limpiarCamposFibra()
{
    ui->qlwFibra->clear();
    ui->leMarcaFibra->clear();
    ui->leModeloFibra->clear();
    ui->leMetrosFibra->clear();
    ui->lePelosFibra->clear();
    if(ui->rbtMonomodo->isChecked()){
        ui->rbtMonomodo->unsetCursor();
    }
    else if(ui->rbtMultimodo->isChecked()){
        ui->rbtMultimodo->unsetCursor();
    }
    ui->lePrecioFibra->clear();
}

void MainWindow::mostrarDatosDbSFP()
{
    QSqlQuery consultar = basededatos->Consultar("modulosfp");
    int fila=0;
    ui->qtwSFP->setRowCount(0);
    while(consultar.next()){
        ui->qtwSFP->insertRow(fila);
        ui->qtwSFP->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,8, new QTableWidgetItem(consultar.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::limpiarCamposSFP()
{
    ui->qlwSFP->clear();
    ui->leMarcaSFP->clear();
    ui->leModeloSFP->clear();
    ui->leKmSFP->clear();
    ui->lePelosFibra->clear();
    if(ui->rbtMonomodoSFP->isChecked()){
        ui->rbtMonomodoSFP->unsetCursor();
    }
    else if(ui->rbtMultimodoSFP->isChecked()){
        ui->rbtMultimodoSFP->unsetCursor();
    }
    ui->lePrecioSFP->clear();
    ui->leCantidadSFP->clear();
}

void MainWindow::limpiarCamposRJ45()
{
    ui->qlwRJ45->clear();
    ui->leMarcaRJ45->clear();
    ui->leModeloRJ45->clear();
    if(ui->rbtComun->isChecked()){
        ui->rbtComun->unsetCursor();
    }
    else if(ui->rbtBlindada->isChecked()){
        ui->rbtBlindada->unsetCursor();
    }
    ui->lePrecioRJ45->clear();
    ui->leCantidadRJ45->clear();
}

void MainWindow::mostrarDatosDbRJ45()
{
    QSqlQuery consultar = basededatos->Consultar("ficharj45");
    int fila=0;
    ui->qtwRJ45->setRowCount(0);
    while(consultar.next()){
        ui->qtwRJ45->insertRow(fila);
        ui->qtwRJ45->setItem(fila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,1, new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,2, new QTableWidgetItem(consultar.value(3).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,3, new QTableWidgetItem(consultar.value(4).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,4, new QTableWidgetItem(consultar.value(5).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,5, new QTableWidgetItem(consultar.value(6).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,6, new QTableWidgetItem(consultar.value(7).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,7, new QTableWidgetItem(consultar.value(8).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::mensajeErrorIP()
{
    QMessageBox MsgBox;
    MsgBox.setText("El valor de cada octeto de una IP debe estar entre 0 y 254.");
    MsgBox.exec();
}

void MainWindow::on_pbBorrarListaW_clicked()
{
    QMessageBox::StandardButton dialogo;
    dialogo = QMessageBox::question(this, "Borrar", "¿Seguro que desea borrar toda la lista?", QMessageBox::Yes|QMessageBox::No);
    if(dialogo == QMessageBox::Yes){
    wireless->borrarListaWireless();
    mostrarDatosDbWireless();
    }
}

void MainWindow::on_pbtnPrevisualizarW_clicked()
{
    PrecioEnPesos *wirelessenpesos = new PrecioEnPesos();
    PrecioConIVA *wirelessconiva = new PrecioConIVA();
    wireless->setMarca(ui->leMarcaW->text().toStdString());
    wireless->setModelo(ui->leModeloW->text().toStdString());
    wireless->setCantidadBocas(ui->leBocasW->text().toInt());
    wireless->setIPbyte1(ui->leIPw->text().toInt());
    wireless->setIPbyte2(ui->leIPw_2->text().toInt());
    wireless->setIPbyte3(ui->leIPw_3->text().toInt());
    wireless->setIPbyte4(ui->leIPw_4->text().toInt());
    wireless->setPotencia(ui->lePotencia->text().toInt());
    wireless->setBanda(ui->cboBanda->currentText().toStdString());
    wireless->setTipoAntena(ui->cboAntena->currentText().toStdString());
    wireless->setDbi(ui->leDbi->text().toInt());
    wireless->setPrecioEnDolares(ui->lePrecioW->text().toDouble());
    wirelessenpesos->CalcularPrecio(ui->lePrecioW->text().toDouble(), parametro->getDolar());
    wireless->setPrecioEnPesos(wirelessenpesos->Resultado());
    wirelessconiva->CalcularPrecio(wirelessenpesos->Resultado());
    wireless->setPrecioIVA(wirelessconiva->Resultado());
    wireless->setFuncion(ui->leFuncionW->text().toStdString());
    ui->qlwWireless->addItem(wireless->MostrarDatos().data());
}

void MainWindow::on_pbtnGuardarS_clicked()
{
    switches->crearTablaSwitches();
    PrecioEnPesos *switchenpesos = new PrecioEnPesos();
    PrecioConIVA *switchconiva = new PrecioConIVA();
    switches->setMarca(ui->leMarcaSwitch->text().toUpper().toStdString());
    switches->setModelo(ui->leModeloSwitch->text().toUpper().toStdString());
    switches->setCantidadBocas(ui->leBocasS->text().toInt());
    bool siga1, siga2, siga3, siga4 = false;
    if(switches->VerificarIP(ui->leIPs->text().toInt())){
        switches->setIPbyte1(ui->leIPs->text().toInt());
        siga1 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPs->clearFocus();
        siga1 = false;
    }
    if(switches->VerificarIP(ui->leIPs_2->text().toInt())){
        switches->setIPbyte2(ui->leIPs_2->text().toInt());
        siga2 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPs_2->clearFocus();
        siga2 = false;
    }
    if(switches->VerificarIP(ui->leIPs_3->text().toInt())){
        switches->setIPbyte3(ui->leIPs_3->text().toInt());
        siga3 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPs_3->clearFocus();
        siga3 = false;
    }
    if(switches->VerificarIP(ui->leIPs_4->text().toInt())){
        switches->setIPbyte4(ui->leIPs_4->text().toInt());
        siga4 = true;
    }
    else{
        mensajeErrorIP();
        ui->leIPs_4->clearFocus();
        siga4 = false;
    }
    if (siga1 && siga2 && siga3 && siga4){
        if(ui->rbGestionable->isChecked()){
            switches->setGestionable("gestionable");
        }
        else if(ui->rbNoGestionable->isChecked()){
            switches->setGestionable("no gestionable");
        }
    switches->setUser(ui->leUserS->text().toStdString());
    switches->setPass(ui->lePassS->text().toStdString());
    switches->setPrecioEnDolares(ui->lePrecioS->text().toDouble());
    switchenpesos->CalcularPrecio(ui->lePrecioS->text().toDouble(), basededatos->valorDolar());
    switches->setPrecioEnPesos(switchenpesos->Resultado());
    switchconiva->CalcularPrecio(switchenpesos->Resultado());
    switches->setPrecioIVA(switchconiva->Resultado());
    switches->setFuncion(ui->leFuncionS->text().toStdString());
    if(ui->qtwSwitch->selectedItems().empty()){
        switches->insertarSwitch();
    }
    else{
        switches->actualizarSwitch();
    }
    mostrarDatosDbSwitch();
    limpiarCamposSwitch();
    }
}

void MainWindow::on_pbtnBorrarListaS_clicked()
{
    switches->borrarListaSwitches();
    mostrarDatosDbSwitch();
}

void MainWindow::on_pbtnPrevisualizarS_clicked()
{
    switches->crearTablaSwitches();
    PrecioEnPesos *switchenpesos = new PrecioEnPesos();
    PrecioConIVA *switchconiva = new PrecioConIVA();
    switches->setMarca(ui->leMarcaSwitch->text().toStdString());
    switches->setModelo(ui->leModeloSwitch->text().toStdString());
    switches->setCantidadBocas(ui->leBocasS->text().toInt());
    switches->setIPbyte1(ui->leIPs->text().toInt());
    switches->setIPbyte2(ui->leIPs_2->text().toInt());
    switches->setIPbyte3(ui->leIPs_3->text().toInt());
    switches->setIPbyte4(ui->leIPs_2->text().toInt());
        if(ui->rbGestionable->isChecked()){
            switches->setGestionable("gestionable");
        }
        else if(ui->rbNoGestionable->isChecked()){
            switches->setGestionable("no gestionable");
        }
    switches->setUser(ui->leUserS->text().toStdString());
    switches->setPass(ui->lePassS->text().toStdString());
    switches->setPrecioEnDolares(ui->lePrecioS->text().toDouble());
    switchenpesos->CalcularPrecio(ui->lePrecioS->text().toDouble(), parametro->getDolar());
    switches->setPrecioEnPesos(switchenpesos->Resultado());
    switchconiva->CalcularPrecio(switchenpesos->Resultado());
    switches->setPrecioIVA(switchconiva->Resultado());
    switches->setFuncion(ui->leFuncionS->text().toStdString());
    ui->qlwSwitch->addItem(switches->MostrarDatos().data());
}

void MainWindow::on_pbtnGuardarUTP_clicked()
{
    cableutp->crearTablaUTP();
    PrecioEnPesos *utpenpesos = new PrecioEnPesos();
    PrecioConIVA *utpconiva = new PrecioConIVA();
    cableutp->setMarca(ui->leMarcaUTP->text().toUpper().toStdString());
    cableutp->setModelo(ui->leModeloUTP->text().toUpper().toStdString());
    cableutp->setMetros(ui->leMetrosUTP->text().toInt());
    if(ui->rbtInteriorUTP->isChecked()){
        cableutp->setInteriorExterior("interior");
    }
    else if(ui->rbtExteriorUTP->isChecked()){
        cableutp->setInteriorExterior("exterior");
    }
    if(ui->rbtVainaSimpleUTP->isChecked()){
        cableutp->setVaina("simple");
    }
    else if(ui->rbtVainaDobleUTP->isChecked()){
        cableutp->setVaina("doble");
    }
    cableutp->setPrecioEnDolares(ui->lePrecioUTP->text().toDouble());
    utpenpesos->CalcularPrecio(ui->lePrecioUTP->text().toDouble(), parametro->getDolar());
    cableutp->setPrecioEnPesos(utpenpesos->Resultado());
    utpconiva->CalcularPrecio(utpenpesos->Resultado());
    cableutp->setPrecioIVA(utpconiva->Resultado());
    if(ui->qtwUTP->selectedItems().empty()){
        cableutp->insertarUTP();
    }
    else{
        cableutp->actualizarUTP();
    }
    mostrarDatosDbUTP();
    limpiarCamposUTP();
}

void MainWindow::on_pbtnPrevisualizarUTP_clicked()
{
    cableutp->crearTablaUTP();
    PrecioEnPesos *utpenpesos = new PrecioEnPesos();
    PrecioConIVA *utpconiva = new PrecioConIVA();
    cableutp->setMarca(ui->leMarcaUTP->text().toStdString());
    cableutp->setModelo(ui->leModeloUTP->text().toStdString());
    cableutp->setMetros(ui->leMetrosUTP->text().toInt());
    if(ui->rbtInteriorUTP->isChecked()){
        cableutp->setInteriorExterior("interior");
    }
    else if(ui->rbtExteriorUTP->isChecked()){
        cableutp->setInteriorExterior("exterior");
    }
    if(ui->rbtVainaDobleUTP->isChecked()){
        cableutp->setVaina("simple");
    }
    else if(ui->rbtVainaDobleUTP->isChecked()){
        cableutp->setVaina("doble");
    }
    cableutp->setPrecioEnDolares(ui->lePrecioUTP->text().toDouble());
    utpenpesos->CalcularPrecio(ui->lePrecioUTP->text().toDouble(), basededatos->valorDolar());
    cableutp->setPrecioEnPesos(utpenpesos->Resultado());
    utpconiva->CalcularPrecio(utpenpesos->Resultado());
    cableutp->setPrecioIVA(utpconiva->Resultado());
    ui->qlwUTP->addItem(cableutp->MostrarDatos().data());
}

void MainWindow::on_pbBorrarListaUTP_clicked()
{
    cableutp->borrarListaUTP();
    mostrarDatosDbUTP();
}

void MainWindow::on_pbtnPrevisualizarFibra_clicked()
{
    cablefibra->crearTablaFibra();
    PrecioEnPesos *fibraenpesos = new PrecioEnPesos();
    PrecioConIVA *fibraconiva = new PrecioConIVA();
    cablefibra->setMarca(ui->leMarcaFibra->text().toStdString());
    cablefibra->setModelo(ui->leModeloFibra->text().toStdString());
    cablefibra->setMetros(ui->leMetrosFibra->text().toInt());
    cablefibra->setPelos(ui->lePelosFibra->text().toInt());
    if(ui->rbtMonomodo->isChecked()){
        cablefibra->setModo("monomodo");
    }
    else if(ui->rbtMultimodo->isChecked()){
        cablefibra->setModo("exterior");
    }
    cablefibra->setPrecioEnDolares(ui->lePrecioFibra->text().toDouble());
    fibraenpesos->CalcularPrecio(ui->lePrecioFibra->text().toDouble(), basededatos->valorDolar());
    cablefibra->setPrecioEnPesos(fibraenpesos->Resultado());
    fibraconiva->CalcularPrecio(cablefibra->getPrecioEnPesos());
    cablefibra->setPrecioIVA(fibraconiva->Resultado());
    ui->qlwFibra->addItem(cablefibra->MostrarDatos().data());
}

void MainWindow::on_pbBorrarListaFibra_clicked()
{
    cablefibra->borrarListaFibra();
    mostrarDatosDbFibra();
}

void MainWindow::on_pbtnGuardarSFP_clicked()
{
    modulosfp->crearTablaSFP();
    PrecioEnPesos *sfpenpesos = new PrecioEnPesos();
    PrecioConIVA *sfpconiva = new PrecioConIVA();
    modulosfp->setMarca(ui->leMarcaSFP->text().toUpper().toStdString());
    modulosfp->setModelo(ui->leModeloSFP->text().toUpper().toStdString());
    modulosfp->setCantidad(ui->leCantidadSFP->text().toInt());
    modulosfp->setKilometrosSoportados(ui->leKmSFP->text().toInt());
    if(ui->rbtMonomodoSFP->isChecked()){
        modulosfp->setModo("monomodo");
    }
    else if(ui->rbtMultimodoSFP->isChecked()){
        modulosfp->setModo("multimodo");
    }
    modulosfp->setPrecioEnDolares(ui->lePrecioSFP->text().toDouble());
    sfpenpesos->CalcularPrecio(ui->lePrecioSFP->text().toDouble(), basededatos->valorDolar());
    modulosfp->setPrecioEnPesos(sfpenpesos->Resultado());
    sfpconiva->CalcularPrecio(modulosfp->getPrecioEnPesos());
    modulosfp->setPrecioIVA(sfpconiva->Resultado());
    if(ui->qtwSFP->selectedItems().empty()){
    modulosfp->insertarSFP();
    }
    else{
    modulosfp->actualizarSFP();
    }
    mostrarDatosDbSFP();
    limpiarCamposSFP();
}

void MainWindow::on_pbtnPrevisualizarSFP_clicked()
{
    modulosfp->crearTablaSFP();
    PrecioEnPesos *sfpenpesos = new PrecioEnPesos();
    PrecioConIVA *sfpconiva = new PrecioConIVA();
    modulosfp->setMarca(ui->leMarcaSFP->text().toStdString());
    modulosfp->setModelo(ui->leModeloSFP->text().toStdString());
    modulosfp->setCantidad(ui->leCantidadSFP->text().toInt());
    modulosfp->setKilometrosSoportados(ui->leKmSFP->text().toInt());
    if(ui->rbtMonomodoSFP->isChecked()){
        modulosfp->setModo("monomodo");
    }
    else if(ui->rbtMultimodoSFP->isChecked()){
        modulosfp->setModo("multimodo");
    }
    modulosfp->setPrecioEnDolares(ui->lePrecioSFP->text().toDouble());
    sfpenpesos->CalcularPrecio(ui->lePrecioSFP->text().toDouble(), basededatos->valorDolar());
    modulosfp->setPrecioEnPesos(sfpenpesos->Resultado());
    sfpconiva->CalcularPrecio(modulosfp->getPrecioEnPesos());
    modulosfp->setPrecioIVA(sfpconiva->Resultado());
    ui->qlwSFP->addItem(modulosfp->MostrarDatos().data());
}

void MainWindow::on_pbBorrarListaSFP_clicked()
{
    modulosfp->borrarSFP();
    mostrarDatosDbSFP();
}

void MainWindow::on_pbtnGuardarRJ45_clicked()
{
    ficharj45->crearTablaRJ45();
    PrecioEnPesos *rj45enpesos = new PrecioEnPesos();
    PrecioConIVA *rj45coniva = new PrecioConIVA();
    ficharj45->setMarca(ui->leMarcaRJ45->text().toUpper().toStdString());
    ficharj45->setModelo(ui->leModeloRJ45->text().toUpper().toStdString());
    ficharj45->setCantidad(ui->leCantidadRJ45->text().toInt());
    if(ui->rbtComun->isChecked()){
        ficharj45->setComunOBlindada("común");
    }
    else if(ui->rbtBlindada->isChecked()){
        ficharj45->setComunOBlindada("blindada");
    }
    ficharj45->setPrecioEnDolares(ui->lePrecioRJ45->text().toDouble());
    rj45enpesos->CalcularPrecio(ui->lePrecioRJ45->text().toDouble(), basededatos->valorDolar());
    ficharj45->setPrecioEnPesos(rj45enpesos->Resultado());
    rj45coniva->CalcularPrecio(ficharj45->getPrecioEnPesos());
    ficharj45->setPrecioIVA(rj45coniva->Resultado());
    if(ui->qtwRJ45->selectedItems().empty()){
        ficharj45->insertarRJ45();
    }
    else{
        ficharj45->actualizarRJ45();
    }
    mostrarDatosDbRJ45();
    limpiarCamposRJ45();
}

void MainWindow::on_pbtnPrevisualizarRJ45_clicked()
{
    ficharj45->crearTablaRJ45();
    PrecioEnPesos *rj45enpesos = new PrecioEnPesos();
    PrecioConIVA *rj45coniva = new PrecioConIVA();
    ficharj45->setMarca(ui->leMarcaRJ45->text().toStdString());
    ficharj45->setModelo(ui->leModeloRJ45->text().toStdString());
    ficharj45->setCantidad(ui->leCantidadRJ45->text().toInt());
    if(ui->rbtComun->isChecked()){
        ficharj45->setComunOBlindada("común");
    }
    else if(ui->rbtBlindada->isChecked()){
        ficharj45->setComunOBlindada("blindada");
    }
    ficharj45->setPrecioEnDolares(ui->lePrecioRJ45->text().toDouble());
    rj45enpesos->CalcularPrecio(ui->lePrecioRJ45->text().toDouble(), basededatos->valorDolar());
    ficharj45->setPrecioEnPesos(rj45enpesos->Resultado());
    rj45coniva->CalcularPrecio(ficharj45->getPrecioEnPesos());
    ficharj45->setPrecioIVA(rj45coniva->Resultado());
    ui->qlwRJ45->addItem(ficharj45->MostrarDatos().data());
}

void MainWindow::on_pbBorrarListaRJ45_clicked()
{
    ficharj45->borrarRJ45();
    mostrarDatosDbRJ45();
}

void MainWindow::on_pbtnLimpiarS_clicked()
{
    limpiarCamposSwitch();
}

void MainWindow::on_pbtnLimpiarW_clicked()
{
    limpiarCamposWireless();
}

void MainWindow::on_pbtnEditarW_clicked()
{
    limpiarCamposWireless();
    if(!ui->qtwWireless->selectedItems().empty()){
        int row = ui->qtwWireless->currentRow();
        wireless->setId(ui->qtwWireless->item(row, 0)->text().toInt());
        ui->leMarcaW->insert(ui->qtwWireless->item(row, 1)->text());
        ui->leModeloW->insert(ui->qtwWireless->item(row, 2)->text());
        ui->leBocasW->insert(ui->qtwWireless->item(row, 3)->text());
        ui->leFuncionW->insert(ui->qtwWireless->item(row, 4)->text());
        QString strip = ui->qtwWireless->item(row,5)->text();
        QRegExp rx("(\\.)");
        QStringList query = strip.split(rx);
        ui->leIPw->insert(query[0]);
        ui->leIPw_2->insert(query[1]);
        ui->leIPw_3->insert(query[2]);
        ui->leIPw_4->insert(query[3]);
        ui->lePotencia->insert(ui->qtwWireless->item(row, 6)->text());
        ui->cboBanda->setCurrentText(ui->qtwWireless->item(row,7)->text());
        ui->cboAntena->setCurrentText(ui->qtwWireless->item(row, 8)->text());
        ui->leDbi->insert(ui->qtwWireless->item(row, 9)->text());
        ui->leUserW->insert(ui->qtwWireless->item(row, 10)->text());
        ui->lePassW->insert(ui->qtwWireless->item(row, 11)->text());
        ui->lePrecioW->insert(ui->qtwWireless->item(row, 12)->text());
    }
}

void MainWindow::on_pbtnEditarS_clicked()
{
    limpiarCamposSwitch();
    if(!ui->qtwSwitch->selectedItems().empty()){
        int row = ui->qtwSwitch->currentRow();
        switches->setId(ui->qtwSwitch->item(row, 0)->text().toInt());
        ui->leMarcaSwitch->insert(ui->qtwSwitch->item(row, 1)->text());
        ui->leModeloSwitch->insert(ui->qtwSwitch->item(row, 2)->text());
        ui->leBocasS->insert(ui->qtwSwitch->item(row, 3)->text());
        ui->leFuncionS->insert(ui->qtwSwitch->item(row, 4)->text());
        QString strip = ui->qtwSwitch->item(row,5)->text();
        QRegExp rx("(\\.)");
        QStringList query = strip.split(rx);
        ui->leIPs->insert(query[0]);
        ui->leIPs_2->insert(query[1]);
        ui->leIPs_3->insert(query[2]);
        ui->leIPs_4->insert(query[3]);
        if(ui->qtwSwitch->item(row, 6)->text() == "gestionable")
        {
            ui->rbGestionable->setChecked(true);
        }
        else if(ui->qtwSwitch->item(row, 6)->text() == "no gestionable")
        {
            ui->rbNoGestionable->setChecked(true);
        }
        ui->leUserS->insert(ui->qtwSwitch->item(row, 7)->text());
        ui->lePassS->insert(ui->qtwSwitch->item(row, 8)->text());
        ui->lePrecioS->insert(ui->qtwSwitch->item(row, 9)->text());
    }
}

void MainWindow::on_pbtnBorrarW_clicked()
{
    int row = ui->qtwWireless->currentRow();
    wireless->setId(ui->qtwWireless->item(row, 0)->text().toInt());
    wireless->borrarWireless();
    mostrarDatosDbWireless();
}

void MainWindow::on_pbtnMostrarTodoW_clicked()
{
    mostrarDatosDbWireless();
    limpiarCamposWireless();
}

void MainWindow::on_pbtnBuscarS_clicked()
{
    QSqlQuery consulta;
    QString qBuscarS = ui->leBuscarS->text().toUpper();
    if(ui->cboBuscarS->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("switches", qBuscarS);
    }
    else if(ui->cboBuscarS->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("switches", qBuscarS);
    }
    int fila=0;
    ui->qtwSwitch->setRowCount(0);
    while(consulta.next()){
        ui->qtwSwitch->insertRow(fila);
        ui->qtwSwitch->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwSwitch->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnMostrarTodoS_clicked()
{
    limpiarCamposSwitch();
    mostrarDatosDbSwitch();
}

void MainWindow::on_pbtnBorrarS_clicked()
{
    int row = ui->qtwSwitch->currentRow();
    switches->setId(ui->qtwSwitch->item(row, 0)->text().toInt());
    switches->borrarSwitch();
    mostrarDatosDbSwitch();
}

void MainWindow::on_pbtnEditarUTP_clicked()
{
    limpiarCamposUTP();
    if(!ui->qtwUTP->selectedItems().empty()){
        int row = ui->qtwUTP->currentRow();
        cableutp->setId(ui->qtwUTP->item(row, 0)->text().toInt());
        ui->leMarcaUTP->insert(ui->qtwUTP->item(row, 1)->text());
        ui->leModeloUTP->insert(ui->qtwUTP->item(row, 2)->text());
        ui->leMetrosUTP->insert(ui->qtwUTP->item(row, 3)->text());
        if(ui->qtwUTP->item(row, 4)->text() == "exterior")
        {
            ui->rbtExteriorUTP->setChecked(true);
        }
        else if(ui->qtwUTP->item(row, 4)->text() == "interior")
        {
            ui->rbtInteriorUTP->setChecked(true);
        }
        if(ui->qtwUTP->item(row, 5)->text().contains("doble"))
        {
            ui->rbtVainaDobleUTP->setChecked(true);
        }
        else if(ui->qtwUTP->item(row, 5)->text() == "simple")
        {
            ui->rbtVainaSimpleUTP->setChecked(true);
        }
        ui->lePrecioUTP->insert(ui->qtwUTP->item(row, 6)->text());
    }
}

void MainWindow::on_pbtnBorrarUTP_clicked()
{
    int row = ui->qtwUTP->currentRow();
    cableutp->setId(ui->qtwUTP->item(row, 0)->text().toInt());
    cableutp->borrarUTP();
    mostrarDatosDbUTP();
}

void MainWindow::on_pbtnEditarRJ45_clicked()
{
    limpiarCamposRJ45();
    if(!ui->qtwRJ45->selectedItems().empty()){
        int row = ui->qtwRJ45->currentRow();
        ficharj45->setId(ui->qtwRJ45->item(row, 0)->text().toInt());
        ui->leMarcaRJ45->insert(ui->qtwRJ45->item(row, 1)->text());
        ui->leModeloRJ45->insert(ui->qtwRJ45->item(row, 2)->text());
        if(ui->qtwRJ45->item(row, 3)->text() == "común")
        {
            ui->rbtComun->setChecked(true);
        }
        else if(ui->qtwRJ45->item(row, 3)->text() == "blindada")
        {
            ui->rbtBlindada->setChecked(true);
        }
        ui->leCantidadRJ45->insert(ui->qtwRJ45->item(row, 4)->text());

        ui->lePrecioRJ45->insert(ui->qtwRJ45->item(row, 5)->text());
    }
}

void MainWindow::on_pbtnBorrarRJ45_clicked()
{
    int row = ui->qtwRJ45->currentRow();
    ficharj45->setId(ui->qtwRJ45->item(row, 0)->text().toInt());
    ficharj45->borrarRJ45();
    mostrarDatosDbRJ45();
}

void MainWindow::on_pbtnEditarFibra_clicked()
{
    limpiarCamposFibra();
    if(!ui->qtwFibra->selectedItems().empty()){
        int row = ui->qtwFibra->currentRow();
        cablefibra->setId(ui->qtwFibra->item(row, 0)->text().toInt());
        ui->leMarcaFibra->insert(ui->qtwFibra->item(row, 1)->text());
        ui->leModeloFibra->insert(ui->qtwFibra->item(row, 2)->text());
        ui->leMetrosFibra->insert(ui->qtwFibra->item(row, 3)->text());

        if(ui->qtwFibra->item(row, 4)->text() == "monomodo")
        {
            ui->rbtMonomodo->setChecked(true);
        }
        else if(ui->qtwFibra->item(row, 4)->text() == "multimodo")
        {
            ui->rbtMultimodo->setChecked(true);
        }
        ui->lePelosFibra->insert(ui->qtwFibra->item(row, 5)->text());
        ui->lePrecioFibra->insert(ui->qtwFibra->item(row, 6)->text());
    }
}

void MainWindow::on_pbtnEditarSFP_clicked()
{
    limpiarCamposSFP();
    if(!ui->qtwSFP->selectedItems().empty()){
        int row = ui->qtwSFP->currentRow();
        modulosfp->setId(ui->qtwSFP->item(row, 0)->text().toInt());
        ui->leMarcaSFP->insert(ui->qtwSFP->item(row, 1)->text());
        ui->leModeloSFP->insert(ui->qtwSFP->item(row, 2)->text());
        if(ui->qtwSFP->item(row, 3)->text() == "monomodo")
        {
            ui->rbtMonomodoSFP->setChecked(true);
        }
        else if(ui->qtwSFP->item(row, 3)->text() == "multimodo")
        {
            ui->rbtMultimodoSFP->setChecked(true);
        }
        ui->leKmSFP->insert(ui->qtwSFP->item(row, 4)->text());
        ui->leCantidadSFP->insert(ui->qtwSFP->item(row, 5)->text());
        ui->lePrecioSFP->insert(ui->qtwSFP->item(row, 6)->text());
    }
}

void MainWindow::on_pbtnBuscarUTP_clicked()
{
    QSqlQuery consulta;
    QString qBuscarUTP = ui->leBuscarUTP->text().toUpper();
    if(ui->cboBuscarUTP->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("cableutp", qBuscarUTP);
    }
    else if(ui->cboBuscarUTP->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("cableutp", qBuscarUTP);
    }
    int fila=0;
    ui->qtwUTP->setRowCount(0);
    while(consulta.next()){
        ui->qtwUTP->insertRow(fila);
        ui->qtwUTP->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwUTP->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnBuscarRJ45_clicked()
{
    QSqlQuery consulta;
    QString qBuscarRJ45 = ui->leBuscarRJ45->text().toUpper();
    if(ui->cboBuscarRJ45->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("ficharj45", qBuscarRJ45);
    }
    else if(ui->cboBuscarRJ45->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("ficharj45", qBuscarRJ45);
    }
    int fila=0;
    ui->qtwRJ45->setRowCount(0);
    while(consulta.next()){
        ui->qtwRJ45->insertRow(fila);
        ui->qtwRJ45->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwRJ45->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnBuscarFibra_clicked()
{
    QSqlQuery consulta;
    QString qBuscarFibra = ui->leBuscarFibra->text().toUpper();
    if(ui->cboBuscarFibra->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("cablefibra", qBuscarFibra);
    }
    else if(ui->cboBuscarRJ45->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("cablefibra", qBuscarFibra);
    }
    int fila=0;
    ui->qtwFibra->setRowCount(0);
    while(consulta.next()){
        ui->qtwFibra->insertRow(fila);
        ui->qtwFibra->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwFibra->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnGuardarFibra_clicked()
{
    cablefibra->crearTablaFibra();
    PrecioEnPesos *fibraenpesos = new PrecioEnPesos();
    PrecioConIVA *fibraconiva = new PrecioConIVA();
    cablefibra->setMarca(ui->leMarcaFibra->text().toUpper().toStdString());
    cablefibra->setModelo(ui->leModeloFibra->text().toUpper().toStdString());
    cablefibra->setMetros(ui->leMetrosFibra->text().toInt());
    if(ui->rbtMonomodo->isChecked()){
        cablefibra->setModo("monomodo");
    }
    else if(ui->rbtMultimodo->isChecked()){
        cablefibra->setModo("multimodo");
    }
    cablefibra->setPelos(ui->lePelosFibra->text().toInt());
    cablefibra->setPrecioEnDolares(ui->lePrecioFibra->text().toDouble());
    fibraenpesos->CalcularPrecio(ui->lePrecioFibra->text().toDouble(), basededatos->valorDolar());
    cablefibra->setPrecioEnPesos(fibraenpesos->Resultado());
    fibraconiva->CalcularPrecio(cablefibra->getPrecioEnPesos());
    cablefibra->setPrecioIVA(fibraconiva->Resultado());
    if(ui->qtwFibra->selectedItems().empty()){
    cablefibra->insertarFibra();
    }
    else{
    cablefibra->actualizarFibra();
    }
    mostrarDatosDbFibra();
    limpiarCamposFibra();
}

void MainWindow::on_pbtnBuscarRouter_clicked()
{
    QSqlQuery consulta;
    QString qBuscarR = ui->leBuscarR->text().toUpper();
    if(ui->cboBuscarR->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("routers", qBuscarR);
    }
    else if(ui->cboBuscarR->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("routers", qBuscarR);
    }
    int fila=0;
    ui->qtwRouter->setRowCount(0);
    while(consulta.next()){
        ui->qtwRouter->insertRow(fila);
        ui->qtwRouter->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwRouter->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnMostrarTodoRouter_clicked()
{
    mostrarDatosDbRouter();
    limpiarCamposRouter();
}

void MainWindow::on_pbtnBuscarSFP_clicked()
{
    QSqlQuery consulta;
    QString qBuscarSFP = ui->leBuscarSFP->text().toUpper();
    if(ui->cboBuscarSFP->currentText().toStdString() == "Modelo"){
        consulta = basededatos->BuscarModelo("modulosfp", qBuscarSFP);
    }
    else if(ui->cboBuscarSFP->currentText().toStdString() == "Marca"){
        consulta = basededatos->BuscarMarca("modulosfp", qBuscarSFP);
    }
    int fila=0;
    ui->qtwSFP->setRowCount(0);
    while(consulta.next()){
        ui->qtwSFP->insertRow(fila);
        ui->qtwSFP->setItem(fila,0, new QTableWidgetItem(consulta.value(1).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,1, new QTableWidgetItem(consulta.value(2).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,2, new QTableWidgetItem(consulta.value(3).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,3, new QTableWidgetItem(consulta.value(4).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,4, new QTableWidgetItem(consulta.value(5).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,5, new QTableWidgetItem(consulta.value(6).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,6, new QTableWidgetItem(consulta.value(7).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,7, new QTableWidgetItem(consulta.value(8).toByteArray().constData()));
        ui->qtwSFP->setItem(fila,8, new QTableWidgetItem(consulta.value(9).toByteArray().constData()));
        fila++;
    }
}

void MainWindow::on_pbtnLimpiarUTP_clicked()
{
    limpiarCamposUTP();
}

void MainWindow::on_pbtnLimpiarFibra_clicked()
{
    limpiarCamposFibra();
}

void MainWindow::on_pbtnLimpiarRJ45_clicked()
{
    limpiarCamposRJ45();
}

void MainWindow::on_pbtnLimpiarSFP_clicked()
{
    limpiarCamposSFP();
}

void MainWindow::on_pbtnMostrarTodoUTP_clicked()
{
    limpiarCamposUTP();
    mostrarDatosDbUTP();
}

void MainWindow::on_pbtnMostrarTodoRJ45_clicked()
{
    limpiarCamposRJ45();
    mostrarDatosDbRJ45();
}

void MainWindow::on_pbtnMostrarTodoFibra_clicked()
{
    limpiarCamposFibra();
    mostrarDatosDbFibra();
}

void MainWindow::on_pbtnMostrarTodoSFP_clicked()
{
    limpiarCamposSFP();
    mostrarDatosDbSFP();
}

void MainWindow::on_pbtnBorrarFibra_clicked()
{
    int row = ui->qtwFibra->currentRow();
    cablefibra->setId(ui->qtwFibra->item(row, 0)->text().toInt());
    cablefibra->borrarFibra();
    mostrarDatosDbFibra();
}

void MainWindow::on_pbtnBorrarSFP_clicked()
{
    int row = ui->qtwSFP->currentRow();
    modulosfp->setId(ui->qtwSFP->item(row, 0)->text().toInt());
    modulosfp->borrarSFP();
    mostrarDatosDbSFP();
}

void MainWindow::on_actionPar_metros_triggered()
{
    parametro = new Parametros();
    parametro->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete router;
    delete wireless;
    delete switches;
    delete cableutp;
    delete cablefibra;
    delete ficharj45;
    delete modulosfp;
    delete parametro;
    delete basededatos;
}
