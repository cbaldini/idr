#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <QDialog>
#include <basededatos.h>

namespace Ui {
class Parametros;
}

class Parametros : public QDialog
{
    Q_OBJECT

public:
    explicit Parametros(QWidget *parent = nullptr);
    double getDolar();
    void setDolar(double dolar);
    void crearTablaMonedas();
    void insertarMoneda();
    void borrarMoneda();
    void borrarMonedas();
    void actualizarMoneda();
    int getId();
    void setId(int id);

protected:
    double _dblDolar;
    int _id;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Parametros *ui;
};

#endif // PARAMETROS_H
