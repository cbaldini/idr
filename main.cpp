#include <router.h>
#include <iostream>

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    Router *mirouter = new Router();
//    string inmarca;
    int opcion = 2;
//    cout<<"1-Consola 2-GUI"<<endl;
//    cin>>opcion;

switch (opcion){
case 1:
//    cout<<"Ingresa la marca del router: ";
//    cin>>inmarca;
//    mirouter->setMarca(inmarca);

//    cout<<mirouter->MostrarEnLista()<<endl;
//    return 0;
case 2:
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


}
