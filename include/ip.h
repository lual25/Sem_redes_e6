#ifndef IP_H
#define IP_H


#include <string>
using namespace std;
class IPv4
{
private:
    //Division de palabras correspondiantes
    string cadenaBytes;
    void asignarBytes(string cadenaBytes);
    unsigned char cVersionTCabecera;
    unsigned char cTServicio;
    unsigned char cLongTotal[2];
    unsigned char cId[2];
    unsigned char cFlagsPFrag[2];
    unsigned char cTVida;
    unsigned char cProtocolo;
    unsigned char cCheckSum[2];
    unsigned char cIpOrigen[4];
    unsigned char cIpDestino[4];

    string infoRest = "";

    void setVersion();
    void setTamCabecera();
    void setTipoServicio();
    void desglosarBits();
    void setLogTotal();
    void setIdentificador();
    void setProtocolo();
    void setTtl();
    void setIPs();
    void setFlags();
    void setPosFragmento(string binario);
    void setCheckSum();
    void ICMPv4();


    public:
    IPv4(string cadenaBytes);

    //Informacion de Ipv4
    int version;
    int tamCabecera;
    string desgloseBits;
    string tipoServicio;
    string retardo;
    string rendimiento;
    string fiabilidad;
    int logTotal;
    int identificador;
    string protocolo;
    int ttl;
    string ipOrtigen = "";
    string ipDestino = "";
    string flagBit1;
    string flagBit2;
    string flagBit3;
    int posFragmento;
    string checkSum[2];

    //ICMPv4
    string ICMPv4Type;
    string ICMPv4Code;
    string ICMPv4Checksum[2];

    void printDivBytes();
    void printInfo();




};

class ARP
{
    public:
        ARP(string cadenaBytes);
        int longHardware;
        int longProtocolo;
        string tipoHardware;
        string tipoProtocolo;
        string codigoOperacion;
        string macEmisor="";
        string ipEmisor="";
        string macReceptor="";
        string ipReceptor="";
        void printInfoARP();

    protected:

    private:
        string cadenaBytes;
        void asignarBytes(string cadenaBytes);
        unsigned char cTipoHardware[2];
        unsigned char cTipoProtocolo[2];
        unsigned char cLongitudHardware;
        unsigned char cLongitudProtocolo;
        unsigned char cCodigoOperacion[2];
        string cDireccionHEmisor="";
        string cDireccionIPEmisor="";
        string cDireccionHReceptor="";
        string cDireccionIPReceptor="";

        string infoRest = "";

        void defTipoHardware();
        void defTipoProtocolo();
        void defCodigoOperacion();
        void setIPsARP();
        void setMACsARP();

};

#endif // IP_H
