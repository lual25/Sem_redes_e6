#include "ARP.h"

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

ARP::ARP(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
}

void ARP::asignarBytes(string cadenaBytes){
    this->cTipoHardware[0]=cadenaBytes[0];
    this->cTipoHardware[1]=cadenaBytes[1];
    this->cTipoProtocolo[0]=cadenaBytes[2];
    this->cTipoProtocolo[1]=cadenaBytes[3];
    this->cLongitudHardware=cadenaBytes[4];
    this->cLongitudProtocolo=cadenaBytes[5];
    this->cCodigoOperacion[0]=cadenaBytes[6];
    this->cCodigoOperacion[1]=cadenaBytes[7];
    this->longHardware=int(this->cLongitudHardware);
    this->longProtocolo=int(this->cLongitudProtocolo);
    int cont=8;
    for(int i=0;i<longHardware;i++){
        this->cDireccionHEmisor+=cadenaBytes[cont];
        cont++;
    }
    for(int i=0;i<longProtocolo;i++){
        this->cDireccionIPEmisor+=cadenaBytes[cont];
        cont++;
    }
    for(int i=0;i<longHardware;i++){
        this->cDireccionHReceptor+=cadenaBytes[cont];
        cont++;
    }
    for(int i=0;i<longProtocolo;i++){
        this->cDireccionIPReceptor+=cadenaBytes[cont];
        cont++;
    }
    for(int i=cont; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];
}
