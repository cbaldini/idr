#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//Librerias de bases de datos
#include "basededatos.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public BaseDeDatos
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Declaración de función para base de datos
    void mostrarDatosDbRouter();
    void limpiarCamposRouter();
    void mostrarDatosDbWireless();
    void limpiarCamposWireless();
    void mostrarDatosDbSwitch();
    void limpiarCamposSwitch();
    void mostrarDatosDbUTP();
    void limpiarCamposUTP();
    void mostrarDatosDbFibra();
    void limpiarCamposFibra();
    void mostrarDatosDbSFP();
    void limpiarCamposSFP();
    void mostrarDatosDbRJ45();
    void limpiarCamposRJ45();
    void mensajeErrorIP();
private slots:

    void on_pbtnGuardarR_clicked();
    void on_pbtnGuardarW_clicked();

    void on_pbtnPrevisualizarR_clicked();

    void on_pbBorrarListaR_clicked();

    void on_pbtnPrevisualizarW_clicked();

    void on_pbBorrarListaW_clicked();

    void on_pbtnGuardarS_clicked();

    void on_pbtnPrevisualizarS_clicked();

    void on_pbtnGuardarUTP_clicked();

    void on_pbtnPrevisualizarUTP_clicked();

    void on_pbBorrarListaUTP_clicked();

    void on_pbtnGuardarFibra_clicked();

    void on_pbtnPrevisualizarFibra_clicked();

    void on_pbBorrarListaFibra_clicked();

    void on_pbtnGuardarSFP_clicked();

    void on_pbtnPrevisualizarSFP_clicked();

    void on_pbBorrarListaSFP_clicked();

    void on_pbtnGuardarRJ45_clicked();

    void on_pbtnPrevisualizarRJ45_clicked();

    void on_pbBorrarListaRJ45_clicked();

    void on_pbtnEditarR_clicked();

    void on_pbtnBorrarR_clicked();

    void on_pbtnLimpiarS_clicked();

    void on_pbtnLimpiarW_clicked();

    void on_pbtnEditarW_clicked();

    void on_pbtnBorrarListaS_clicked();

    void on_pbtnEditarS_clicked();

    void on_pbtnBorrarW_clicked();

    void on_pbtnLimpiarR_clicked();

    void on_pbtnBuscarW_clicked();

    void on_pbtnMostrarW_clicked();

    void on_pbtnMostrarTodoW_clicked();

    void on_pbtnBuscarS_clicked();

    void on_pbtnMostrarTodoS_clicked();

    void on_pbtnBorrarS_clicked();

    void on_pbtnEditarUTP_clicked();

    void on_pbtnBorrarUTP_clicked();

    void on_pbtnEditarRJ45_clicked();

    void on_pbtnBorrarRJ45_clicked();

    void on_pbtnEditarFibra_clicked();

    void on_pbtnEditarSFP_clicked();

    void on_pbtnBuscarUTP_clicked();

    void on_pbtnBuscarRJ45_clicked();

    void on_pbtnBuscarFibra_clicked();

    void on_pbtnBuscarRouter_clicked();

    void on_pbtnMostrarTodoRouter_clicked();

    void on_pbtnBuscarSFP_clicked();

    void on_pbtnLimpiarUTP_clicked();

    void on_pbtnLimpiarFibra_clicked();

    void on_pbtnLimpiarRJ45_clicked();

    void on_pbtnLimpiarSFP_clicked();

    void on_pbtnMostrarTodoUTP_clicked();

    void on_pbtnMostrarTodoRJ45_clicked();

    void on_pbtnMostrarTodoFibra_clicked();

    void on_pbtnMostrarTodoSFP_clicked();

    void on_pbtnBorrarFibra_clicked();

    void on_pbtnBorrarSFP_clicked();

    void on_actionPar_metros_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
