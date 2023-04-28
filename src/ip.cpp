#include "ip.h"
#include "funcionesAux.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

IPv4::IPv4(string cadenaBytes){
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
void IPv4::asignarBytes(string cadenaBytes){
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
void IPv4::setVersion(){
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
void IPv4::setTipoServicio(){
    this->desgloseBits = char_bin(this->cTServicio);
    this->desglosarBits();

}
void IPv4::desglosarBits(){
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
void IPv4::setLogTotal(){
    string n = "";
    n+=this->cLongTotal[0];
    n+=this->cLongTotal[1];
   this->logTotal = bin_dec(string_bin(n));
}
void IPv4::setIdentificador(){
    string n = "";
    n+=this->cId[0];
    n+=this->cId[1];
    this->identificador = bin_dec(string_bin(n));
}
void IPv4::setProtocolo(){
    switch(int(this->cProtocolo))
    {
    case 1:
        this->protocolo = "ICMPv4";
        ICMPv4();
        break;
    case 6:
        {
            this->protocolo = "TCP";
            break;
        }
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
void IPv4::setTtl(){
    this->ttl = int(this->cTVida);
}
void IPv4::setIPs(){
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
void IPv4::setFlags(){
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
void IPv4::setCheckSum(){
    this->checkSum[0] = dec_hex(int(this->cCheckSum[0]));
    this->checkSum[1] = dec_hex(int(this->cCheckSum[1]));
}
void IPv4::ICMPv4(){
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
void IPv4::printDivBytes(){
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
void IPv4::printInfo(){



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


    if(this->protocolo == "TCP")
    {
        TCP _tcp(this->infoRest);
        _tcp.printInfo();
    }
    if(this->protocolo == "UDP")
    {
        UDP _udp(this->infoRest);
        _udp.printInfo();
    }

}




//ARP
ARP::ARP(string cadenaBytes){
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
void ARP::setIPsARP(){
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
void ARP::setMACsARP(){
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

IPv6::IPv6(string cadenaBytes){
    asignarBytes(cadenaBytes);
    defVersion();
    defTamDatos();
    defEncabezadoSiguiente();
    defLimiteSalto();
    defDirecciones();

}
void IPv6::asignarBytes(string cadenaBytes){
    for(int i=0; i<4; i++)
        this->cfirs4bytes[i] = cadenaBytes[i];
    this->cTamanoDatos[0] = cadenaBytes[4];
    this->cTamanoDatos[1] = cadenaBytes[5];
    this->cEncabezadoSiguiente = cadenaBytes[6];
    this->cLimiteSalto = cadenaBytes[7];
    for(int i=0; i<16; i++)
    {
        this->cDireccionOrigen[i] = cadenaBytes[8+i];
        this->cDireccionDestino[i] = cadenaBytes[23+i];
    }

    for(int i=40; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];


}
void IPv6::defVersion(){
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
    this->version = bin_dec(version);
    this->claseTrafico = ctrafico;
    desglosarBits();
    this->etiquetaFlujo = bin_dec(eflujo);
}
void IPv6::desglosarBits(){

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
void IPv6::defTamDatos(){
    this->tamDatos = int(cTamanoDatos[0]) + int(this->cTamanoDatos[1]);
}
void IPv6::defEncabezadoSiguiente(){
    switch(int(this->cEncabezadoSiguiente))
    {
    case 1:
        this->encabezadoSiguiente = "ICMPv4";
        break;
    case 6:
        this->encabezadoSiguiente = "TCP";
        break;
    case 17:
        this->encabezadoSiguiente = "UDP";
        break;
    case 58:
        this->encabezadoSiguiente = "ICMPv6";
        ICMPv6();
        break;
    case 118:
        this->encabezadoSiguiente = "STP";
        break;
    case 121:
        this->encabezadoSiguiente = "SMP";
        break;
    default:
        this->encabezadoSiguiente = "No identificado";
    }
}
void IPv6::defLimiteSalto(){
    this->limiteSalto = int(this->cLimiteSalto);
}
void IPv6::defDirecciones(){

    for(int i=0; i<16; i++)
    {
        this->direccionOrigen+= dec_hex(int(this->cDireccionOrigen[i]));
        this->direccionDestino+= dec_hex(int(this->cDireccionDestino[i]));
        if(i<15 && (i+1)%2 == 0)
        {
            this->direccionOrigen += ":";
            this->direccionDestino += ":";
        }
    }
}
void IPv6::ICMPv6(){
    unsigned char ICMPv6[4];
    for(int i=0; i<4; i++)
        ICMPv6[i] = infoRest[i];

    this->ICMPv6Tipo=int(ICMPv6[0]);
    this->ICMPv6Codigo=int(ICMPv6[1]);

    this->ICMPv6Checksum[0]=dec_hex(int(ICMPv6[2]));
    this->ICMPv6Checksum[1]=dec_hex(int(ICMPv6[3]));

    string new_info;
    for(int i=4; i<this->infoRest.size(); i++)
    {
       new_info += this->infoRest[i];
    }
    this->infoRest = new_info;
    ICMPv6_tipo();
}
void IPv6::ICMPv6_tipo(){
    switch(this->ICMPv6Tipo)
    {
        case 1:{
            this->ICMPV6_mensaje = "Mensaje de destino inalcanzable";
            switch(this->ICMPv6Codigo)
            {
                case 0:
                {
                    this->ICMPV6_descripcionCodigo = "No existe ruta destino";
                    break;
                }
                case 1:
                {
                    this->ICMPV6_descripcionCodigo = "Comunicacion con el destino administrativamente prohibida";
                    break;
                }
                case 2:
                {
                    this->ICMPV6_descripcionCodigo = "No asignado";
                    break;
                }
                case 3:
                {
                    this->ICMPV6_descripcionCodigo = "Direccion inalcanzable";
                    break;
                }
            }
            break;
        }
        case 2:{
            this->ICMPV6_mensaje = "Mensaje de etiqueta demasiado grande";
            break;
        }
        case 3:{
            this->ICMPV6_mensaje = "Time Exceeded Message";
            switch(this->ICMPv6Codigo)
            {
                case 0:
                    {
                        this->ICMPV6_descripcionCodigo = "El limite de salto excedido";
                        break;
                    }
                case 1:
                    {
                         this->ICMPV6_descripcionCodigo = "Tiempo de reesamble de fragmento excedido";
                        break;
                    }
                default:
                    this->ICMPV6_descripcionCodigo = "Descripcion no encontrada";
            }
            break;
        }
        case 4:{
            this->ICMPV6_mensaje = "Mensaje de problema de parametro";
             switch(this->ICMPv6Codigo)
            {
                case 0:
                    {
                        this->ICMPV6_descripcionCodigo = "El campo de encabezado erroneo encontro";
                        break;
                    }
                case 1:
                    {
                         this->ICMPV6_descripcionCodigo = "El tipo siguiente desconocido de la encabezado encontro";
                        break;
                    }
                case 2:
                    {
                         this->ICMPV6_descripcionCodigo = "Opcion desconocida del IPv6 encontrada";
                        break;
                    }
                default:
                    this->ICMPV6_descripcionCodigo = "Descripcion no encontrada";
            }
            break;
        }
        case 128:{
            this->ICMPV6_mensaje = "Mensaje del pedido de eco";
            break;
        }
        case 129:{
            this->ICMPV6_mensaje = "Mensaje de respuesta de eco";
            break;
        }
        case 133:{
            this->ICMPV6_mensaje = "Mensaje de solicitud del router";
            break;
        }
        case 134:{
            this->ICMPV6_mensaje = "Mensaje de anuncio del router";
            break;
        }
        case 135:{
            this->ICMPV6_mensaje = "Mensaje de solicitud vecino";
            break;
        }
        case 136:{
            this->ICMPV6_mensaje = "Mensaje de anuncio de vecino";
            break;
        }
        case 137:{
            this->ICMPV6_mensaje = "Reoriente el mensaje";
            break;
        }
        default:
            {
                this->ICMPV6_mensaje = "Mensaje no identificado";
            }
    }
}
void IPv6::printInfo(){

    cout<<"\n-------------IPv6--------------"<<endl;
    cout<<"Version: "<<this->version<<endl;
    cout<<"clase Trafico: "<<this->claseTrafico<<endl;
    cout<<"Tipo de servicio: "<<this->tipoServicio<<endl;
    cout<<"\tRetardo: "<<this->retardo<<endl;
    cout<<"\tRendimiento: "<<this->rendimiento<<endl;
    cout<<"\tFiabilidad: "<<this->fiabilidad<<endl;
    cout<<"Etiqueta de Flujo: "<<this->etiquetaFlujo<<endl;
    cout<<"Tamano de datos: "<<this->tamDatos<<endl;
    cout<<"Tipo de encabezado siguiente: "<<this->encabezadoSiguiente<<endl;
    cout<<"Limite de salto: "<<this->limiteSalto<<endl;
    cout<<"Direccion Origen: "<<this->direccionOrigen<<endl;
    cout<<"Direccion destino: "<<this->direccionDestino<<endl;

    if(this->encabezadoSiguiente == "ICMPv6")
    {
        cout<<"\tICMPv6 Type: "<<this->ICMPV6_mensaje<<endl;
        cout<<"\tICMPv6 Code: "<<this->ICMPV6_descripcionCodigo<<endl;
        cout<<"\tICMPv6 Checksum: "<<this->ICMPv6Checksum[0]<<":"<<this->ICMPv6Checksum[1]<<endl;
    }

    unsigned char palab;
    for(int i=0; i<this->infoRest.size(); i++)
    {
        palab = this->infoRest[i];
        printf ("%02x:",palab);
    }

    if(this->encabezadoSiguiente == "TCP")
    {
        TCP _tcp(this->infoRest);
        _tcp.printInfo();
    }

    if(this->encabezadoSiguiente == "UDP")
    {
        UDP _udp(this->infoRest);
        _udp.printInfo();
    }

}


//TCP
TCP::TCP(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    defPuertos();
    defNSecuencia();
    defLCabecera();
    defTamVentana();
    defChecksum();
}

void TCP::asignarBytes(string cadenaBytes)
{
    this->cPuertoOrigen[0] = cadenaBytes[0];
    this->cPuertoOrigen[1] = cadenaBytes[1];
    this->cPuertoDestino[0] = cadenaBytes[2];
    this->cPuertoDestino[1] = cadenaBytes[3];
    for(int i=0; i<3; i++)
    {
        this->cNSecuencia[i] = cadenaBytes[4+i];
        this->cNAcuseRecibo[i] = cadenaBytes[8+i];
    }
    this->cLCabecera[0] = cadenaBytes[12];
    this->cLCabecera[1] = cadenaBytes[13];
    this->cTVentana[0] = cadenaBytes[14];
    this->cTVentana[1] = cadenaBytes[15];
    this->cSumVerificacion[0] = cadenaBytes[16];
    this->cSumVerificacion[1] = cadenaBytes[17];
    this->cPunteroUrgente[0] = cadenaBytes[18];
    this->cPunteroUrgente[1] = cadenaBytes[19];
}

void TCP::defPuertos()
{
    string aux = "" + char_bin(this->cPuertoOrigen[0]) + char_bin(this->cPuertoOrigen[1]);
    this->puertoOrigen = bin_dec(aux);
    aux = "" + char_bin(this->cPuertoDestino[0]) + char_bin(this->cPuertoDestino[1]);
    this->puertoDestino = bin_dec(aux);
    if(this->puertoDestino>0 && this->puertoDestino<1023)
        this->tipoPuertoDestino = "Puerto bien conocido";
    if(this->puertoDestino>1024 && this->puertoDestino<49151)
        this->tipoPuertoDestino = "Puerto Registrado";
    if(this->puertoDestino>49152 && this->puertoDestino<65535)
        this->tipoPuertoDestino = "Puerto Dinamico o Privado";

    if(this->puertoOrigen>0 && this->puertoOrigen<1023)
        this->tipoPuertoOrigen = "Puerto bien conocido";
    if(this->puertoOrigen>1024 && this->puertoOrigen<49151)
        this->tipoPuertoOrigen = "Puerto Registrado";
    if(this->puertoOrigen>49152 && this->puertoOrigen<65535)
        this->tipoPuertoOrigen = "Puerto Dinamico o Privado";

    switch(this->puertoDestino){
    case 20:
        this->servicioDestino="FTP";
        break;
    case 21:
        this->servicioDestino="FTP";
        break;
    case 22:
        this->servicioDestino="SSH";
        break;
    case 23:
        this->servicioDestino="TELNET";
        break;
    case 25:
        this->servicioDestino="SMTP";
        break;
    case 53:
        this->servicioDestino="DNS";
        break;
    case 67:
        this->servicioDestino="DHCP";
        break;
    case 68:
        this->servicioDestino="DHCP";
        break;
    case 69:
        this->servicioDestino="TFTP";
        break;
    case 80:
        this->servicioDestino="HTTP";
        break;
    case 110:
        this->servicioDestino="POP3";
        break;
    case 143:
        this->servicioDestino="IMAP";
        break;
    case 443:
        this->servicioDestino="HTTPS";
        break;
    case 993:
        this->servicioDestino="IMAP SSL";
        break;
    case 995:
        this->servicioDestino="POP SSL";
        break;
    default:
        this->servicioDestino="Otro";
        break;
}
switch(this->puertoOrigen){
    case 20:
        this->servicioOrigen="FTP";
        break;
    case 21:
        this->servicioOrigen="FTP";
        break;
    case 22:
        this->servicioOrigen="SSH";
        break;
    case 23:
        this->servicioOrigen="TELNET";
        break;
    case 25:
        this->servicioOrigen="SMTP";
        break;
    case 53:
        this->servicioOrigen="DNS";
        break;
    case 67:
        this->servicioOrigen="DHCP";
        break;
    case 68:
        this->servicioOrigen="DHCP";
        break;
    case 69:
        this->servicioOrigen="TFTP";
        break;
    case 80:
        this->servicioOrigen="HTTP";
        break;
    case 110:
        this->servicioOrigen="POP3";
        break;
    case 143:
        this->servicioOrigen="IMAP";
        break;
    case 443:
        this->servicioOrigen="HTTPS";
        break;
    case 993:
        this->servicioOrigen="IMAP SSL";
        break;
    case 995:
        this->servicioOrigen="POP SSL";
        break;
    default:
        this->servicioOrigen="Otro";
        break;
}
}
void TCP::defNSecuencia()
{
    string aux = ""+char_bin(this->cNSecuencia[0]) + char_bin(this->cNSecuencia[1]) + char_bin(this->cNSecuencia[2]) + char_bin(this->cNSecuencia[3]);
    this->nSecuencia = bin_double(aux);
    aux = ""+char_bin(this->cNAcuseRecibo[0]) + char_bin(this->cNAcuseRecibo[1]) + char_bin(this->cNAcuseRecibo[2]) + char_bin(this->cNAcuseRecibo[3]);
    this->nAcuseRecibo = bin_double(aux);
}
void TCP::defTamVentana()
{
    string aux = "" + char_bin(this->cTVentana[0]) + char_bin(this->cTVentana[1]);
    this->Tamventana = bin_dec(aux);
    aux = "" + char_bin(this->cPunteroUrgente[0]) + char_bin(this->cPunteroUrgente[1]);
    this->PunteroUrgente = bin_dec(aux);
}
void TCP::defLCabecera()
{
    string bin = "" + char_bin(this->cLCabecera[0]) + char_bin(this->cLCabecera[1]);
    string lCabecera = "";
    string banderas = "";
    for(int i=0; i<bin.size(); i++)
    {
        if(i<4)
            lCabecera += bin[i];
        else
            if(i>6)
                banderas += bin[i];
    }
    this->lCabecera=bin_dec(lCabecera);
    for(int i = 0; i<banderas.size(); i++)
        this->banderas[i] = banderas[i];

}

void TCP::defChecksum()
{
    this->checksum[0] = dec_hex(this->cSumVerificacion[0]);
    this->checksum[1] = dec_hex(this->cSumVerificacion[1]);
}

void TCP::printInfo()
{
     cout<<"\n-------------TCP--------------"<<endl;
     cout<<" Puerto Origen: "<<this->puertoOrigen<<" "<<this->tipoPuertoOrigen<<endl;
     cout<<"\t Tipo de servicio: "<<this->servicioOrigen<<endl;
     cout<<" Puerto Destino: "<<this->puertoDestino<<" "<<this->tipoPuertoDestino<<endl;
     cout<<"\t Tipo de servicio: "<<this->servicioDestino<<endl;
     cout<<" Numero de secuencia: "<<this->nSecuencia<<endl;
     cout<<" Numero acuse de recivo: "<<this->nAcuseRecibo<<endl;
    cout<<" Longitud de cabecera: "<<this->lCabecera<<" palabras"<<endl;
    cout<<" Banderas de comunicacion:"<<endl;
      cout<<"\tNS: "<<this->banderas[0]<<endl;
      cout<<"\tCWR: "<<this->banderas[1]<<endl;
      cout<<"\tECE: "<<this->banderas[2]<<endl;
      cout<<"\tURG: "<<this->banderas[3]<<endl;
      cout<<"\tACK: "<<this->banderas[4]<<endl;
      cout<<"\tPSH: "<<this->banderas[5]<<endl;
      cout<<"\tRST: "<<this->banderas[6]<<endl;
      cout<<"\tSYN: "<<this->banderas[7]<<endl;
      cout<<"\tFIN: "<<this->banderas[8]<<endl;
      cout<<" Tamano Ventana: "<<this->Tamventana<<" bytes"<<endl;
      cout<<" Suma de verificacion: "<<this->checksum[0]<<":"<<this->checksum[1]<<endl;
      cout<<" Puntero Urgente: "<<this->PunteroUrgente<<endl;
}

//UDP

UDP::UDP(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    defPuertos();
    defLTotal();
    defChecksum();
}

void UDP::asignarBytes(string cadenaBytes)
{
    this->cPuertoOrigen[0] = cadenaBytes[0];
    this->cPuertoOrigen[1] = cadenaBytes[1];
    this->cPuertoDestino[0] = cadenaBytes[2];
    this->cPuertoDestino[1] = cadenaBytes[3];
    this->cLTotal[0] = cadenaBytes[4];
    this->cLTotal[1] = cadenaBytes[5];
    this->cSumVerificacion[0] = cadenaBytes[6];
    this->cSumVerificacion[1] = cadenaBytes[7];
    for(int i=8; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];


}

void UDP::defPuertos()
{
    string aux = "" + char_bin(this->cPuertoOrigen[0]) + char_bin(this->cPuertoOrigen[1]);
    this->puertoOrigen = bin_dec(aux);
    aux = "" + char_bin(this->cPuertoDestino[0]) + char_bin(this->cPuertoDestino[1]);
    this->puertoDestino = bin_dec(aux);
    if(this->puertoDestino>0 && this->puertoDestino<1023)
        this->tipoPuertoDestino = "Puerto bien conocido";
    if(this->puertoDestino>1024 && this->puertoDestino<49151)
        this->tipoPuertoDestino = "Puerto Registrado";
    if(this->puertoDestino>49152 && this->puertoDestino<65535)
        this->tipoPuertoDestino = "Puerto Dinamico o Privado";

    if(this->puertoOrigen>0 && this->puertoOrigen<1023)
        this->tipoPuertoOrigen = "Puerto bien conocido";
    if(this->puertoOrigen>1024 && this->puertoOrigen<49151)
        this->tipoPuertoOrigen = "Puerto Registrado";
    if(this->puertoOrigen>49152 && this->puertoOrigen<65535)
        this->tipoPuertoOrigen = "Puerto Dinamico o Privado";

    switch(this->puertoDestino){
    case 20:
        this->servicioDestino="FTP";
        break;
    case 21:
        this->servicioDestino="FTP";
        break;
    case 22:
        this->servicioDestino="SSH";
        break;
    case 23:
        this->servicioDestino="TELNET";
        break;
    case 25:
        this->servicioDestino="SMTP";
        break;
    case 53:
        this->servicioDestino="DNS";
        break;
    case 67:
        this->servicioDestino="DHCP";
        break;
    case 68:
        this->servicioDestino="DHCP";
        break;
    case 69:
        this->servicioDestino="TFTP";
        break;
    case 80:
        this->servicioDestino="HTTP";
        break;
    case 110:
        this->servicioDestino="POP3";
        break;
    case 143:
        this->servicioDestino="IMAP";
        break;
    case 443:
        this->servicioDestino="HTTPS";
        break;
    case 993:
        this->servicioDestino="IMAP SSL";
        break;
    case 995:
        this->servicioDestino="POP SSL";
        break;
    default:
        this->servicioDestino="Otro";
        break;
}
switch(this->puertoOrigen){
    case 20:
        this->servicioOrigen="FTP";
        break;
    case 21:
        this->servicioOrigen="FTP";
        break;
    case 22:
        this->servicioOrigen="SSH";
        break;
    case 23:
        this->servicioOrigen="TELNET";
        break;
    case 25:
        this->servicioOrigen="SMTP";
        break;
    case 53:
        this->servicioOrigen="DNS";
        break;
    case 67:
        this->servicioOrigen="DHCP";
        break;
    case 68:
        this->servicioOrigen="DHCP";
        break;
    case 69:
        this->servicioOrigen="TFTP";
        break;
    case 80:
        this->servicioOrigen="HTTP";
        break;
    case 110:
        this->servicioOrigen="POP3";
        break;
    case 143:
        this->servicioOrigen="IMAP";
        break;
    case 443:
        this->servicioOrigen="HTTPS";
        break;
    case 993:
        this->servicioOrigen="IMAP SSL";
        break;
    case 995:
        this->servicioOrigen="POP SSL";
        break;
    default:
        this->servicioOrigen="Otro";
        break;
}
}

void UDP::defLTotal()
{
    string aux = "" + char_bin(this->cLTotal[0]) + char_bin(this->cLTotal[1]);
    this->lTotal = bin_dec(aux);
}

void UDP::defChecksum()
{
    this->checksum[0] = dec_hex(this->cSumVerificacion[0]);
    this->checksum[1] = dec_hex(this->cSumVerificacion[1]);
}

void UDP::printInfo()
{
     cout<<"\n-------------UDP--------------"<<endl;
     cout<<" Puerto Origen: "<<this->puertoOrigen<<" "<<this->tipoPuertoOrigen<<endl;
     cout<<"\t Tipo de servicio: "<<this->servicioOrigen<<endl;
     cout<<" Puerto Destino: "<<this->puertoDestino<<" "<<this->tipoPuertoDestino<<endl;
     cout<<"\t Tipo de servicio: "<<this->servicioDestino<<endl;
      cout<<" Longitud Total: "<<this->lTotal<<" bytes"<<endl;
      cout<<" Suma de verificacion: "<<this->checksum[0]<<":"<<this->checksum[1]<<endl;

    DNS _dns(this->infoRest);

    _dns.printInfo();

}

DNS::DNS(string cadenaBytes)
{
    asignarBytes(cadenaBytes);
    defID();
    defBanderas();

}

void DNS::asignarBytes(string cadenaBytes)
{
    this->cID[0] = cadenaBytes[0];
    this->cID[1] = cadenaBytes[1];
    this->cBanderas[0] = cadenaBytes[2];
    this->cBanderas[1] = cadenaBytes[3];
    this->cQDcount[0] = cadenaBytes[4];
    this->cQDcount[1] = cadenaBytes[5];
    this->cANcount[0] = cadenaBytes[6];
    this->cANcount[1] = cadenaBytes[7];
    this->cNScount[0] = cadenaBytes[8];
    this->cNScount[1] = cadenaBytes[9];
    this->cARcount[0] = cadenaBytes[10];
    this->cARcount[1] = cadenaBytes[11];
    int startByte = 12;
    defContadores();
    for(int i = 0; i<this->qdcount; i++)
        startByte = question(cadenaBytes, startByte, i);
    for(int i = 0; i<this->ancount; i++)
        startByte = answer(cadenaBytes, startByte, i);
    for(int i=startByte; i<cadenaBytes.size(); i++)
        this->infoRest += cadenaBytes[i];



}

void DNS::defID(){
    string aux= "" + char_bin(this->cID[0]) + char_bin(this->cID[1]);
    this->id=dec_hex(bin_dec(aux));
}

void DNS::defBanderas(){
    string aux= "" + char_bin(this->cID[0]) + char_bin(this->cID[1]);
    string opCode="";
    string rcode="";
    if(aux[0]=='0'){
        this->banderaQR= "0 (Consulta)";
    }else{
        this->banderaQR= "1 (Respuesta)";
    }
    for(int i=1;i<5;i++){
        opCode+=aux[i];
    }
    switch(bin_dec(opCode)){
        case 0:
            this->banderaOPcode="0: QUERY";
            break;
        case 1:
            this->banderaOPcode="1: IQUERY";
            break;
        case 2:
            this->banderaOPcode="2: Status";
            break;
        default:
            this->banderaOPcode="Reservado";
            break;
    }
    if(aux[5]='0'){
        this->banderaAA="0";
    }else{
        this->banderaAA="1";
    }
    if(aux[6]='0'){
        this->banderaTC="0";
    }else{
        this->banderaTC="1";
    }
    if(aux[7]='0'){
        this->banderaRD="0";
    }else{
        this->banderaRD="1";
    }
    if(aux[8]='0'){
        this->banderaRA="0";
    }else{
        this->banderaRA="1";
    }
    if(aux[9]='0'){
        this->banderaZ="0";
    }else{
        this->banderaZ="1";
    }
    if(aux[10]='0'){
        this->banderaAD="0";
    }else{
        this->banderaAD="1";
    }
    if(aux[11]='0'){
        this->banderaCD="0";
    }else{
        this->banderaCD="1";
    }
    for(int i=12;i<16;i++){
        rcode+=aux[i];
    }
    switch(bin_dec(rcode)){
        case 0:
            this->banderaRcode="0: Ningun error.";
            break;
        case 1:
            this->banderaRcode="1: Error de formato.";
            break;
        case 2:
            this->banderaRcode="2: Falla en el servidor.";
            break;
        case 3:
            this->banderaRcode="3: Error en nombre.";
            break;
        case 4:
            this->banderaRcode="4: No implementado.";
            break;
        case 5:
            this->banderaRcode="5: Rechazado";
            break;
        default:
            this->banderaRcode="Otro errror.";
            break;
    }

}

void DNS::defContadores()
{

    this->qdcount = bin_dec(char_bin(cQDcount[0]) + char_bin(cQDcount[1]));
    this->ancount = bin_dec(char_bin(cANcount[0]) + char_bin(cANcount[1]));
    this->nscount = bin_dec(char_bin(cNScount[0]) + char_bin(cNScount[1]));
    this->arcount = bin_dec(char_bin(cARcount[0]) + char_bin(cARcount[1]));
}

int DNS::question(string cadenaBytes, int startByte, int no_question)
{
    DNSQuestion newQuestion;
    newQuestion.Qname = getDom(cadenaBytes, startByte);
    startByte += newQuestion.Qname.length()+1;
    cout<<"StartByte: "<<startByte<<endl;
    newQuestion.Qtype = getDomType(cadenaBytes, startByte);
    startByte += 2;
    newQuestion.Qclass = getDomClass(cadenaBytes, startByte);
    startByte += 2;
    this->questions[no_question] = newQuestion;
    return startByte;

}
int DNS::answer(string cadenaBytes, int startByte, int no_ans)
{
    DNSAnswer newAnswer;
    newAnswer.APTR = ""+char_hex(cadenaBytes[startByte])+char_hex(cadenaBytes[startByte]);
    startByte +=2;
    newAnswer.Atype = getDomType(cadenaBytes, startByte);
    startByte += 2;
    newAnswer.Aclass = getDomClass(cadenaBytes, startByte);
    startByte += 2;
    newAnswer.ATTL = bin_dec(char_bin(cQDcount[startByte + 0]) + char_bin(cQDcount[startByte + 1]) + char_bin(cQDcount[startByte +2]) + char_bin(cQDcount[startByte + 3]));
    startByte += 4;
    newAnswer.ARLen = bin_dec(char_bin(cQDcount[startByte + 0]) + char_bin(cQDcount[startByte + 1]));
    startByte += 2;
    newAnswer.ARData = getRData(cadenaBytes, startByte, newAnswer.Atype);
    startByte += 2;

    this->answers[no_ans] = newAnswer;

}

string DNS::getRData(string bytes, int byteStart, string type)
{
    string data = "";
    switch(int(type[0]))
    {
        case int('A'):
            data+= bin_dec(char_bin(bytes[byteStart])) + "." + bin_dec(char_bin(bytes[byteStart+1])); + ".";//
             data +=  bin_dec(char_bin(bytes[byteStart+2])) + "." + bin_dec(char_bin(bytes[byteStart+3]));
            break;
            /*
        case "CNAME":
            break;
        case "MX":
            break;
        case "NS":
            break;
        case "PTR":
            break;
        case "SOA":
            break;*/
    }
    return data;

}
string DNS::getDomClass(string bytes, int byteStart)
{
    int intClass = bin_dec(char_bin(bytes[byteStart])+char_bin(bytes[byteStart+1]));
    cout<<"Dominio-"<<intClass<<endl;
    string classOut;
    switch(intClass)
    {

    case 1:
        classOut = "IN";
        break;
    case 3:
        classOut = "CH";
        break;
    default:
        classOut = "Desconocido";

        return classOut;
    }
}
string DNS::getDomType(string bytes, int byteStart)
{
    int intType = bin_dec(char_bin(bytes[byteStart])+char_bin(bytes[byteStart+1]));
    cout<<"Dominio-"<<intType<<endl;
    string typeOut;
    switch(intType)
    {
        case 1:
            typeOut = "A";
        break;
        case 5:
            typeOut = "CNAME";
        break;
        case 13:
            typeOut = "HINFO";
        break;
        case 15:
            typeOut = "MX";
        break;
        case 22:
            typeOut = "NS";
        break;
        case 23:
            typeOut = "NS";
        break;
        default:
            typeOut = "Desconocido";
    }
    return typeOut;
}
string DNS::getDom(string bytes, int bytesStart)
{
    string dom = "";
    int cont = bytesStart;
    while(cont < bytes.size())
    {
        int num = bytes[cont];
        if(num == 0)
            return dom;
        for(int i = 1; i<=num; i++)
        {
            dom += bytes[cont+i];
        }
        dom+=".";
        cont += num+1;
    }
    return dom;
}



void DNS::printInfo(){
    cout<<"\n-------------DNS--------------"<<endl;
    cout<<" Id: "<<this->id<<endl;
    cout<<" BANDERAS: "<<endl;
    cout<<" \tQR: "<<this->banderaQR<<endl;
    cout<<" \tOp Code: "<<this->banderaOPcode<<endl;
    cout<<" \tAA: "<<this->banderaAA<<endl;
    cout<<" \tTC: "<<this->banderaTC<<endl;
    cout<<" \tRD: "<<this->banderaRD<<endl;
    cout<<" \tRA: "<<this->banderaRA<<endl;
    cout<<" \tZ: "<<this->banderaZ<<endl;
    cout<<" \tAD: "<<this->banderaAD<<endl;
    cout<<" \tCD: "<<this->banderaCD<<endl;
    cout<<" \tR code: "<<this->banderaRcode<<endl;
    cout<<" Contadores:"<<endl;
    cout<<" \tQuestion: "<<this->qdcount<<endl;
    cout<<" \tAnswer: "<<this->ancount<<endl;
    cout<<" \tAuthority: "<<this->nscount<<endl;
    cout<<" \tAdditional: "<<this->arcount<<endl;
     cout<<" Questions:"<<endl;
     for(int i=0; i<this->qdcount; i++)
     {
         cout<<"\t----Question "<<i<<"----"<<endl;
         cout<<"\tDominio: "<<this->questions[i].Qname<<endl;
         cout<<"\tTipo: "<<this->questions[i].Qtype<<endl;
         cout<<"\tClase: "<<this->questions[i].Qclass<<endl;
     }
     cout<<" Answers:"<<endl;
     for(int i=0; i<this->ancount; i++)
     {
         cout<<"\t----Answer "<<i<<"----"<<endl;
         cout<<"\tDominio: "<<this->answers[i].APTR<<endl;
         cout<<"\tTipo: "<<this->answers[i].Atype<<endl;
         cout<<"\tClase: "<<this->answers[i].Aclass<<endl;
         cout<<"\tTTL: "<<this->answers[i].ATTL<<" segundos"<<endl;
         cout<<"\tLongitud: "<<this->answers[i].ARLen<<endl;
         cout<<"\tData: "<<this->answers[i].ARData<<endl;
     }

}

