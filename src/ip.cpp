#include "ip.h"
#include "funcionesAux.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

IPv4::IPv4()
{

}
void IPv4::setVersion(char palabra)
{
    string version;
   for(int i=7;i>=4;i--)
        version+=((palabra & (1 << i)) ? '1' : '0');
    this->version= bin_dec(version);
}

void IPv4::setTamCabecera(char palabra)
{
    string longitud;
   for(int i=3;i>=0;i--)
        longitud+=((palabra & (1 << i)) ? '1' : '0');
    this->tamCabecera = bin_dec(longitud);
}

void IPv4::setTipoServicio(char palabra)
{
    this->tipoServicio = hex_bin(palabra, 8);
    this->setDesgloseBits();

}


void IPv4::setDesgloseBits()
{
    string tipo = "";
    for(int i=0; i<3; i++)
        tipo+= this->tipoServicio[i];
    switch(bin_dec(tipo))
    {
        case 0:
            this->desgloseBits = "De rutina";
        break;
        case 1:
            this->desgloseBits = "Prioritario";
        break;
        case 2:
            this->desgloseBits = "Inmediato";
        break;
        case 3:
            this->desgloseBits = "Relampago";
        break;
        case 4:
            this->desgloseBits = "Invalidacion relampago";
        break;
        case 5:
            this->desgloseBits = "Procesado llamada critica y de emergencia";
        break;
        case 6:
            this->desgloseBits = "Control de trabajo de internet";
        break;
        case 7:
            this->desgloseBits = "Control de red";
        break;

    }
        if(this->tipoServicio[4] == '1')
                this->retardo = "bajo";
        else
             this->retardo = "normal";

        if(this->tipoServicio[6] == '1')
                this->fiabilidad = "alta";
        else
             this->fiabilidad = "normal";

        if(this->tipoServicio[5] == '1')
                this->rendimiento = "alto";
        else
             this->rendimiento = "normal";


}

void IPv4::setLogTotal(char palabra1, char palabra2)
{

}
