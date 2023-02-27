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
        ICMPv4();
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

void IPv4::ICMPv4()
{
    unsigned char ICMPv4[4];
    for(int i=0; i<4; i++)
        ICMPv4[i] = infoRest[i];
    switch(int(ICMPv4[0]))
    {
    case 0:
        this->ICMPv4Type="Echo Reply";
        break;
    case 3:
        this->ICMPv4Type="Destination Unreacheable";
        break;
    case 4:
        this->ICMPv4Type="Source Quench";
        break;
    case 5:
        this->ICMPv4Type="Redirect";
        break;
    case 8:
        this->ICMPv4Type="Echo";
        break;
    case 11:
        this->ICMPv4Type="Time Exceeded";
        break;
    case 12:
        this->ICMPv4Type="Parameter Problem";
        break;
    case 13:
        this->ICMPv4Type="Timestamp";
        break;
    case 14:
        this->ICMPv4Type="Timestamp Reply ";
        break;
    case 15:
        this->ICMPv4Type="Information Request ";
        break;
    case 16:
        this->ICMPv4Type="Information Reply ";
        break;
    case 17:
        this->ICMPv4Type="Addressmask";
        break;
    case 18:
        this->ICMPv4Type="Addressmask Reply ";
        break;
    default:
        this->ICMPv4Type="Irreconocible";

    }
    switch(int(ICMPv4[1]))
    {
    case 0:
        this->ICMPv4Code="No se puede llegar a la red";
        break;
    case 1:
        this->ICMPv4Code="No se puede llegar al host o aplicación de destino";
        break;
    case 2:
        this->ICMPv4Code="El destino no dispone del protocolo solicitado";
        break;
    case 3:
        this->ICMPv4Code="No se puede llegar al puerto destino o la aplicación destino no está libre";
        break;
    case 4:
        this->ICMPv4Code="Se necesita aplicar fragmentación, pero el flag correspondiente indica lo contrario";
        break;
    case 5:
        this->ICMPv4Code="La ruta de origen no es correcta";
        break;
    case 6:
        this->ICMPv4Code="No se conoce la red destino";
        break;
    case 7:
        this->ICMPv4Code="No se conoce el host destino";
        break;
    case 8:
        this->ICMPv4Code="El host origen está aislado";
        break;
    case 9:
        this->ICMPv4Code="La comunicación con la red destino está prohibida por razones administrativas";
        break;
    case 10:
        this->ICMPv4Code="La comunicación con el host destino está prohibida por razones administrativas";
        break;
    case 11:
        this->ICMPv4Code="No se puede llegar a la red destino debido al Tipo de servicio";
        break;
    case 12:
        this->ICMPv4Code="No se puede llegar al host destino debido al Tipo de servicio";
        break;

    }
    this->ICMPv4Checksum[0] = dec_hex(int(ICMPv4[2]));
    this->ICMPv4Checksum[1] = dec_hex(int(ICMPv4[3]));
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
    cout<<"\n ipDestino: "<<endl;
    printf ("%02x:",this->cIpDestino[0]);
    printf ("%02x:",this->cIpDestino[1]);
    printf ("%02x:",this->cIpDestino[2]);
    printf ("%02x",this->cIpDestino[3]);

}

void IPv4::printInfo()
{

    cout<<"\n-------------IPv4--------------"<<endl;
    cout<<"Version: "<<this->version<<endl;
    cout<<"Tamano de cabecera: "<<this->tamCabecera<<" palabras"<<endl;
    cout<<"Tipo de servicio: "<<this->tipoServicio<<endl;
    cout<<"\tRetardo: "<<this->retardo<<endl;
    cout<<"\tRendimiento: "<<this->rendimiento<<endl;
    cout<<"\tFiabilidad: "<<this->fiabilidad<<endl;
    cout<<"Longitud Total: "<<this->logTotal<<" bytes"<<endl;
    cout<<"Identificador: "<<this->identificador<<endl;
    cout<<"Flags: "<<endl;
    cout<<"\tBit 1: "<<this->flagBit1<<endl;
    cout<<"\tBit 2: "<<this->flagBit2<<endl;
    cout<<"\tBit 3: "<<this->flagBit3<<endl;
    cout<<"Posicion de fragmento: "<<this->posFragmento<<endl;
    cout<<"Tiempo de vida: "<<this->ttl<<endl;
    cout<<"Protocolo: "<<this->protocolo<<endl;
    fflush(stdin);
    if(this->protocolo == "ICMPv4")
    {
        cout<<"\tICMPv4 Type: "<<this->ICMPv4Type<<endl;
        cout<<"\tICMPv4 Code: "<<this->ICMPv4Code<<endl;
        cout<<"\tICMPv4 Checksum: "<<this->ICMPv4Checksum[0]<<":"<<this->ICMPv4Checksum[1]<<endl;
    }
    cout<<"Checksum: "<<this->checkSum[0]<<":"<<this->checkSum[1]<<endl;
    cout<<"IP origen: "<<this->ipOrtigen<<endl;
    cout<<"IP destino: "<<this->ipDestino<<endl;
    cout<<"Informacion: "<<endl;

    unsigned char palab;
    for(int i=0; i<this->infoRest.size(); i++)
    {
        palab = this->infoRest[i];
        printf ("%02x:",palab);
    }

}




//ARP
ARP::ARP(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    defTipoHardware();
    defTipoProtocolo();
    defCodigoOperacion();
    setIPsARP();
    setMACsARP();
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
        unsigned char c = cadenaBytes[cont];
        this->cDireccionHEmisor+=c;
        cont++;
    }
    for(int i=0;i<longProtocolo;i++){
        unsigned char c = cadenaBytes[cont];
        this->cDireccionIPEmisor+=c;
        cont++;
    }
    for(int i=0;i<longHardware;i++){
        unsigned char c = cadenaBytes[cont];
        this->cDireccionHReceptor+=c;
        cont++;
    }
    for(int i=0;i<longProtocolo;i++){
        unsigned char c = cadenaBytes[cont];
        this->cDireccionIPReceptor+=c;
        cont++;
    }
    for(int i=cont; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];

}

void ARP::defTipoHardware(){
    string aux="";
    int tHardware;
    aux+=this->cTipoHardware[0];
    aux+=this->cTipoHardware[1];
    tHardware=bin_dec(string_bin(aux));
    switch (tHardware){
        case 1:
            this->tipoHardware="Ethernet(10Mb)";
            break;
        case 6:
            this->tipoHardware="IEEE 802 Networks";
            break;
        case 7:
            this->tipoHardware="ARCNET";
            break;
        case 15:
            this->tipoHardware="Frame Relay";
            break;
        case 16:
            this->tipoHardware="Asynchronus Transfer Mode(ATM)";
            break;
        case 17:
            this->tipoHardware="HDLC";
            break;
        case 18:
            this->tipoHardware="Fibre Channel";
            break;
        case 19:
            this->tipoHardware="Asynchronus Transfer Mode(ATM)";
            break;
        case 20:
            this->tipoHardware="Serial Line";
            break;
        default:
            this->tipoHardware="Desconocido";
            break;
    }
}

void ARP::defTipoProtocolo(){
    unsigned char aux;
    aux+=this->cTipoProtocolo[0];
    aux+=this->cTipoProtocolo[1];

    switch(int(aux)){
    case 8:
        this->tipoProtocolo="IPv4";
        break;
    case 14:
        this->tipoProtocolo="ARP";
        break;
    case 181:
        this->tipoProtocolo="RARP";
        break;
    case 355:
        this->tipoProtocolo="IPv6";
        break;
    default:
        this->tipoProtocolo="Desconocido";
        break;

    }
}

void ARP::defCodigoOperacion(){
    string aux="";
    int tCOperacion;
    aux+=this->cCodigoOperacion[0];
    aux+=this->cCodigoOperacion[1];
    tCOperacion=bin_dec(string_bin(aux));
    switch (tCOperacion){
        case 1:
            this->codigoOperacion="Solicitud ARP";
            break;
        case 2:
            this->codigoOperacion="Respuesta ARP";
            break;
        case 3:
            this->codigoOperacion="Solicitud RARP";
            break;
        case 4:
            this->codigoOperacion="Respuesta RARP";
            break;
        default:
            this->codigoOperacion="Desconocido";
            break;
    }
}

void ARP::setIPsARP()
{
    unsigned char unsignedChar;
    for(int i=0; i<this->longProtocolo; i++)
    {
        unsignedChar=this->cDireccionIPEmisor[i];
        this->ipEmisor+= to_string(int(unsignedChar));
        unsignedChar=this->cDireccionIPReceptor[i];
        this->ipReceptor+= to_string(int(unsignedChar));
        if(i<this->longProtocolo-1)
        {
            this->ipEmisor += ".";
            this->ipReceptor += ".";
        }
    }
}

void ARP::setMACsARP()
{
    unsigned char unsignedChar;
    for(int i=0; i<this->longHardware; i++)
    {
        unsignedChar=this->cDireccionHEmisor[i];
        this->macEmisor+= dec_hex(int(unsignedChar));
        unsignedChar=this->cDireccionHReceptor[i];
        this->macReceptor+= dec_hex(int(unsignedChar));
        if(i<this->longHardware-1)
        {
            this->macEmisor += ":";
            this->macReceptor += ":";
        }
    }
}

void ARP::printInfoARP(){
 cout<<"\n-------------ARP---------------"<<endl;
    cout<<"Tipo de Hardware: "<<this->tipoHardware<<endl;
    cout<<"Tipo de protocolo: "<<this->tipoProtocolo<<endl;
    cout<<"Longitud direccion de Hardware: "<<this->longHardware<<" bytes"<<endl;
    cout<<"Longitud direccion de Protocolo: "<<this->longProtocolo<<" bytes"<<endl;
    cout<<"Codigo de operacion: "<<this->codigoOperacion<<endl;
    cout<<"Direccion hardware del emisor: "<<this->macEmisor<<endl;
    cout<<"Direccion IP del emisor: "<<this->ipEmisor<<endl;
    cout<<"Direccion hardware del receptor: "<<this->macReceptor<<endl;
    cout<<"Direccion IP del receptor: "<<this->ipReceptor<<endl;
    cout<<"Informacion: "<<endl;
    unsigned char palab;
    for(int i=0; i<this->infoRest.size(); i++)
    {
        palab = this->infoRest[i];
        printf ("%02x:",palab);
    }

}

//IPv6

IPv6::IPv6(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    defVersion();

}

void IPv6::asignarBytes(string cadenaBytes)
{
    for(int i=0; i<4; i++)
        this->cfirs4bytes[i] = cadenaBytes[i];
    this->cTamanoDatos[0] = cadenaBytes[4];
    this->cTamanoDatos[1] = cadenaBytes[5];
    this->cEncabezadoSiguiente = cadenaBytes[6];
    this->cLimiteSalto = cadenaBytes[7];
    this->cDireccionOrigen[0] = cadenaBytes[8];
    this->cDireccionOrigen[1] = cadenaBytes[9];
    this->cDireccionDestino[0] = cadenaBytes[10];
    this->cDireccionDestino[1] = cadenaBytes[11];

}

void IPv6::defVersion()
{
    string bin1 = char_bin(this->cfirs4bytes[0]);
    string bin2 = char_bin(this->cfirs4bytes[1]);
    string version = "";
    string ctrafico = "";
    string eflujo = "";
    for(int i=0; i<bin1.size(); i++)
    {
        if(i<4)
            version+=bin1[i];
        else
            ctrafico+=bin1[i];
    }
    for(int i=0; i<bin1.size(); i++)
    {
        if(i<4)
            ctrafico+=bin2[i];
        else
            eflujo+=bin2[i];
    }
    cout<<eflujo<<endl;
    this->version = bin_dec(version);
    this->claseTrafico = ctrafico;
    desglosarBits();
    this->etiquetaFlujo = bin_dec(eflujo);
}

void IPv6::desglosarBits()
{
    string tipo = "";
    for(int i=0; i<3; i++)
        tipo+= this->claseTrafico[i];
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
        if(this->claseTrafico[4] == '1')
                this->retardo = "bajo";
        else
             this->retardo = "normal";

        if(this->claseTrafico[6] == '1')
                this->fiabilidad = "alta";
        else
             this->fiabilidad = "normal";

        if(this->claseTrafico[5] == '1')
                this->rendimiento = "alto";
        else
             this->rendimiento = "normal";


}
void IPv6::defTamDatos()
{
    this->tamDatos = int(cTamanoDatos[0]) + int(this->cTamanoDatos[1]);
}
void IPv6::printInfo()
{

    cout<<"\n-------------IPv6--------------"<<endl;
    cout<<"Version: "<<this->version<<endl;
    cout<<"clase Trafico: "<<this->claseTrafico<<endl;
    cout<<"Tipo de servicio: "<<this->tipoServicio<<endl;
    cout<<"\tRetardo: "<<this->retardo<<endl;
    cout<<"\tRendimiento: "<<this->rendimiento<<endl;
    cout<<"\tFiabilidad: "<<this->fiabilidad<<endl;
    cout<<"Etiqueta de Flujo: "<<this->etiquetaFlujo<<endl;
    cout<<"Tamano de datos: "<<this->tamDatos<<endl;


}

