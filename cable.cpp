#include "cable.h"

Cable::Cable()
{

}

int Cable::getMetros(){
    return this->_intMetros;
}
int Cable::setMetros(int metros){
    return this->_intMetros = metros;
}

string Cable::EstablecerTipo(){
    return "Cable";
}
