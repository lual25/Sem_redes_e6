#include "ip.h"
#include "funcionesAux.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

IPv4::IPv4(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    setVersion();
    //setTamCabecera();
    setTipoServicio();

}
void IPv4::asignarBytes(string cadenaBytes) //Se encarga de repartir las palabras con sus bytes correspondientes a cada variable
{
    this->versionTCabecera = cadenaBytes[0];
    this->tServicio = cadenaBytes[1];
    this->longTotal[0] = cadenaBytes[2];
    this->longTotal[1] = cadenaBytes[3];
    this->id[0] = cadenaBytes[4];
    this->id[1] = cadenaBytes[5];
    this->flagsPFrag[0] =  cadenaBytes[6];
    this->flagsPFrag[1] =  cadenaBytes[7];
    this->tVida = cadenaBytes[8];
    this->protocolo = cadenaBytes[9];
    this->checkSum[0] =  cadenaBytes[10];
    this->checkSum[1] =  cadenaBytes[11];
    for(int i=0; i<3; i++)
    {
        this->ipOrigen[i] = cadenaBytes[12+i];
        this->ipDestino[i] = cadenaBytes[16+i];
    }
    for(int i=20; i<cadenaBytes.length(); i++)
        this->infoRest += cadenaBytes[i];
    //print();
}


void IPv4::setVersion()
{
    string bin;
    string version = "";
    string tamCab = "";
    bin = hex_bin(this->versionTCabecera, 8);
    for(int i=0; i<bin.length(); i++)
    {
        if(i<4)
            version+=bin[i];
        else
            tamCab+=bin[i];
    }
    this->version = bin_dec(version);
    this->tamCabecera = bin_dec(tamCab);
}

/*
void IPv4::setTamCabecera()
{
    string longitud;
   for(int i=3;i>=0;i--)
        longitud+=((this->versionTCabecera & (1 << i)) ? '1' : '0');
    this->tamCabecera = bin_dec(longitud);
}*/

void IPv4::setTipoServicio()
{
    this->desgloseBits = hex_bin(this->tServicio, 8);
    this->desglosarBits();

}


void IPv4::desglosarBits()
{
    string tipo = "";
    for(int i=0; i<3; i++)
        tipo+= this->desgloseBits[i];
    switch(bin_dec(tipo))
    {
        case 0:
            this->tipoServicio = "De rutina";
        break;
        case 1:
            this->tipoServicio = "Prioritario";
        break;
        case 2:
            this->tipoServicio = "Inmediato";
        break;
        case 3:
            this->tipoServicio = "Relampago";
        break;
        case 4:
            this->tipoServicio = "Invalidacion relampago";
        break;
        case 5:
            this->tipoServicio = "Procesado llamada critica y de emergencia";
        break;
        case 6:
            this->tipoServicio = "Control de trabajo de internet";
        break;
        case 7:
            this->tipoServicio = "Control de red";
        break;

    }
        if(this->desgloseBits[4] == '1')
                this->retardo = "bajo";
        else
             this->retardo = "normal";

        if(this->desgloseBits[6] == '1')
                this->fiabilidad = "alta";
        else
             this->fiabilidad = "normal";

        if(this->desgloseBits[5] == '1')
                this->rendimiento = "alto";
        else
             this->rendimiento = "normal";


}

void IPv4::setLogTotal()
{

}

void IPv4::printDivBytes() //Imprime la reparticion de palabras para comprovar que la reparticion sea correcta
{
    cout<<"Reparticion de bytes"<<endl;
    cout<<"versionTCabecera: "<<endl;
    printf ("%02x",this->versionTCabecera);
    cout<<"\ntServicio: "<<endl;
    printf ("%02x",this->tServicio);
    cout<<"\nlongTotal: "<<endl;
    printf ("%02x:",this->longTotal[0]);
    printf ("%02x",this->longTotal[1]);
    cout<<"\nid: "<<endl;
    printf ("%02x:",this->id[0]);
    printf ("%02x",this->id[1]);
    cout<<"\nflagsPFrag: "<<endl;
    printf ("%02x:",this->flagsPFrag[0]);
    printf ("%02x",this->flagsPFrag[1]);
    cout<<"\ntvida: "<<endl;
    printf ("%02x",this->tVida);
    cout<<"\nprotocolo: "<<endl;
    printf ("%02x",this->protocolo);
    cout<<"\nprotocolo: "<<endl;
    printf ("%02x",this->protocolo);
    cout<<"\nCheckSum: "<<endl;
    printf ("%02x:",this->checkSum[0]);
    printf ("%02x",this->checkSum[1]);
    cout<<"\nipOrigen: "<<endl;
    printf ("%02x:",this->ipOrigen[0]);
    printf ("%02x:",this->ipOrigen[1]);
    printf ("%02x:",this->ipOrigen[2]);
    printf ("%02x",this->ipOrigen[3]);
    cout<<"\nipDestino: "<<endl;
    printf ("%02x:",this->ipDestino[0]);
    printf ("%02x:",this->ipDestino[1]);
    printf ("%02x:",this->ipDestino[2]);
    printf ("%02x",this->ipDestino[3]);

}

void IPv4::printInfo()
{
    cout<<"\n-------------IPv4--------------"<<endl;
    cout<<"\tVersion: "<<this->version<<endl;
    cout<<"\tTamano de cabecera: "<<this->tamCabecera<<endl;
    cout<<"\tTipo de servicio: "<<this->tipoServicio<<endl;
    cout<<"\t\tRetardo: "<<this->retardo<<endl;
    cout<<"\t\tRendimiento: "<<this->rendimiento<<endl;
    cout<<"\t\tFiabilidad: "<<this->fiabilidad<<endl;
}
