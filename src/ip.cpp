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
    setTipoServicio();
    setLogTotal();
    setIdentificador();
    setProtocolo();
    setTtl();
    setIPs();
    setFlags();
    setCheckSum();

}
void IPv4::asignarBytes(string cadenaBytes) //Se encarga de repartir las palabras con sus bytes correspondientes a cada variable
{
    this->cVersionTCabecera = cadenaBytes[0];
    this->cTServicio = cadenaBytes[1];
    this->cLongTotal[0] = cadenaBytes[2];
    this->cLongTotal[1] = cadenaBytes[3];
    this->cId[0] = cadenaBytes[4];
    this->cId[1] = cadenaBytes[5];
    this->cFlagsPFrag[0] =  cadenaBytes[6];
    this->cFlagsPFrag[1] =  cadenaBytes[7];
    this->cTVida = cadenaBytes[8];
    this->cProtocolo = cadenaBytes[9];
    this->cCheckSum[0] =  cadenaBytes[10];
    this->cCheckSum[1] =  cadenaBytes[11];
    for(int i=0; i<4; i++)
    {
        this->cIpOrigen[i] = cadenaBytes[12+i];
        this->cIpDestino[i] = cadenaBytes[16+i];
    }
    for(int i=20; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];
    //print();
}


void IPv4::setVersion()
{
    string bin;
    string version = "";
    string tamCab = "";
    bin = char_bin(this->cVersionTCabecera);
    for(int i=0; i<bin.size(); i++)
    {
        if(i<4)
            version+=bin[i];
        else
            tamCab+=bin[i];
    }
    this->version = bin_dec(version);
    this->tamCabecera = bin_dec(tamCab);
}


void IPv4::setTipoServicio()
{
    this->desgloseBits = char_bin(this->cTServicio);
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
        default:
            this->tipoServicio = "Tipo de servicio no identificado";

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
    string n = "";
    n+=this->cLongTotal[0];
    n+=this->cLongTotal[1];
   this->logTotal = bin_dec(string_bin(n));
}

void IPv4::setIdentificador()
{
    string n = "";
    n+=this->cId[0];
    n+=this->cId[1];
    this->identificador = bin_dec(string_bin(n));
}

void IPv4::setProtocolo()
{
    switch(int(this->cProtocolo))
    {
    case 1:
        this->protocolo = "ICMPv4";
        break;
    case 6:
        this->protocolo = "TCP";
        break;
    case 17:
        this->protocolo = "UDP";
        break;
    case 58:
        this->protocolo = "ICMPv6";
        break;
    case 118:
        this->protocolo = "STP";
        break;
    case 121:
        this->protocolo = "SMP";
        break;
    default:
        this->protocolo = "No identificado";
    }
}

void IPv4::setTtl()
{
    this->ttl = int(this->cTVida);
}
void IPv4::setIPs()
{
    for(int i=0; i<4; i++)
    {
        this->ipOrtigen += to_string(int(this->cIpOrigen[i]));
        this->ipDestino += to_string(int(this->cIpDestino[i]));
        if(i<3)
        {
            this->ipOrtigen += ".";
            this->ipDestino += ".";
        }
    }
}

void IPv4::setFlags()
{
    string n = "";
    n+=this->cFlagsPFrag[0];
    n+=this->cFlagsPFrag[1];
    string bin = string_bin(n);
    if(bin[0] == '0')
        this->flagBit1 = "0 (Reservado)";
    else
        this->flagBit1 = "1 (desconocido)";
    if(bin[1] == '0')
        this->flagBit2 = "0 (No divisible)";
    else
        this->flagBit2 = "1 (Divisible)";
    if(bin[2] == '0')
        this->flagBit3 = "0 (Ultimo fragmento)";
    else
        this->flagBit3 = "1 (Fragmento intermedio)";

    string newBin = "";
    for(int i=3; i<bin.size(); i++)
        newBin+= bin[i];
    this->posFragmento = bin_dec(newBin);
}

void IPv4::setCheckSum()
{
    this->checkSum[0] = dec_hex(int(this->cCheckSum[0]));
    this->checkSum[1] = dec_hex(int(this->cCheckSum[1]));
}


void IPv4::printDivBytes() //Imprime la reparticion de palabras para comprovar que la reparticion sea correcta
{
    cout<<"\nReparticion de bytes"<<endl;
    cout<<"versionTCabecera: "<<endl;
    printf ("%02x",this->cVersionTCabecera);
    cout<<"\ntServicio: "<<endl;
    printf ("%02x",this->cTServicio);
    cout<<"\nlongTotal: "<<endl;
    printf ("%02x:",this->cLongTotal[0]);
    printf ("%02x",this->cLongTotal[1]);
    cout<<"\nid: "<<endl;
    printf ("%02x:",this->cId[0]);
    printf ("%02x",this->cId[1]);
    cout<<"\nflagsPFrag: "<<endl;
    printf ("%02x:",this->cFlagsPFrag[0]);
    printf ("%02x",this->cFlagsPFrag[1]);
    cout<<"\ntvida: "<<endl;
    printf ("%02x",this->cTVida);
    cout<<"\nprotocolo: "<<endl;
    printf ("%02x",this->cProtocolo);
    cout<<"\nCheckSum: "<<endl;
    printf ("%02x:",this->cCheckSum[0]);
    printf ("%02x",this->cCheckSum[1]);
    cout<<"\nipOrigen: "<<endl;
    printf ("%02x:",this->cIpOrigen[0]);
    printf ("%02x:",this->cIpOrigen[1]);
    printf ("%02x:",this->cIpOrigen[2]);
    printf ("%02x",this->cIpOrigen[3]);
    cout<<"\nipDestino: "<<endl;
    printf ("%02x:",this->cIpDestino[0]);
    printf ("%02x:",this->cIpDestino[1]);
    printf ("%02x:",this->cIpDestino[2]);
    printf ("%02x",this->cIpDestino[3]);

}

void IPv4::printInfo()
{
    cout<<"\n-------------IPv4--------------"<<endl;
    cout<<"Version: "<<this->version<<endl;
    cout<<"Tamano de cabecera: "<<this->tamCabecera<<endl;
    cout<<"Tipo de servicio: "<<this->tipoServicio<<endl;
    cout<<"\tRetardo: "<<this->retardo<<endl;
    cout<<"\tRendimiento: "<<this->rendimiento<<endl;
    cout<<"\tFiabilidad: "<<this->fiabilidad<<endl;
    cout<<"Longitud Total: "<<this->logTotal<<endl;
    cout<<"Identificador: "<<this->identificador<<endl;
    cout<<"Flags: "<<endl;
    cout<<"\tBit 1: "<<this->flagBit1<<endl;
    cout<<"\tBit 2: "<<this->flagBit2<<endl;
    cout<<"\tBit 3: "<<this->flagBit3<<endl;
    cout<<"Posicion de fragmento: "<<this->posFragmento<<endl;
    cout<<"Tiempo de vida: "<<this->ttl<<endl;
    cout<<"Protocolo: "<<this->protocolo<<endl;
    cout<<"Checksum: "<<this->checkSum[0]<<":"<<this->checkSum[1]<<endl;
    cout<<"IP origen: "<<this->ipOrtigen<<endl;
    cout<<"IP destino: "<<this->ipDestino<<endl;
    cout<<"Informacion: "<<endl;
    unsigned char palabra;
    for(int i=0; i<this->infoRest.size(); i++)
    {
        palabra = this->infoRest[i];
        printf ("%02x:",palabra);
    }
}
