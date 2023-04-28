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

    //TCP
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

class IPv6
{
private:
    unsigned char cfirs4bytes[4];
    unsigned char cTamanoDatos[2];
    unsigned char cEncabezadoSiguiente;
    unsigned char cLimiteSalto;
    unsigned char cDireccionOrigen[15];
    unsigned char cDireccionDestino[15];

    string infoRest="";

    void asignarBytes(string cadenaBytes);
    void desglosarBits();
    void defTamDatos();
    void defEncabezadoSiguiente();
    void defLimiteSalto();
    void defDirecciones();
    void ICMPv6();
    void ICMPv6_tipo();


    void defVersion();
public:
    int version;
    string claseTrafico;
    string tipoServicio;
    string retardo;
    string fiabilidad;
    string rendimiento;
    string encabezadoSiguiente;
    string direccionOrigen;
    string direccionDestino;
    int limiteSalto;
    int tamDatos;
    int etiquetaFlujo;
    //ICMPv6
    int ICMPv6Tipo;
    string ICMPV6_descripcionCodigo;
    string ICMPV6_mensaje;
    int ICMPv6Codigo;
    string ICMPv6Checksum[2];

    IPv6(string cadenaBytes);
    void printInfo();


};

class TCP
{
private:
    unsigned char cPuertoOrigen[2];
    unsigned char cPuertoDestino[2];
    unsigned char cNSecuencia[4];
    unsigned char cNAcuseRecibo[4];
    unsigned char cLCabecera[2];
    unsigned char cTVentana[2];
    unsigned char cSumVerificacion[2];
    unsigned char cPunteroUrgente[2];

    void asignarBytes(string cadenaBytes);
    void defPuertos();
    void defNSecuencia();
    void defNAcuse();
    void defLCabecera();
    void defBanderas();
    void defTamVentana();
    void defChecksum();
public:
    TCP(string cadenaBytes);
    int puertoOrigen;
    int puertoDestino;
    string tipoPuertoOrigen;
    string tipoPuertoDestino;
    string servicioOrigen;
    string servicioDestino;
    double nSecuencia;
    double nAcuseRecibo;
    int lCabecera;
    string banderas;
    int Tamventana;
    int PunteroUrgente;
    string checksum[2];

    void printInfo();


};

class UDP
{
   private:
    unsigned char cPuertoOrigen[2];
    unsigned char cPuertoDestino[2];
    unsigned char cLTotal[2];
    unsigned char cSumVerificacion[2];

    void asignarBytes(string cadenaBytes);
    void defPuertos();
    void defLTotal();
    void defChecksum();

    public:
     UDP(string cadenaBytes);
     int puertoOrigen;
    int puertoDestino;
    string tipoPuertoOrigen;
    string tipoPuertoDestino;
    string servicioOrigen;
    string servicioDestino;
    int lTotal;
    string checksum[2];
    string infoRest = "";

    void printInfo();
};
class DNSQuestion
{
    public:
        string Qname;
        string Qtype;
        string Qclass;

};
class DNSAnswer
{
    public:
        string APTR;
        string Atype;
        string Aclass;
        int ATTL;
        int ARLen;
        string ARData;

};
class DNS
{
    private:

        unsigned char cID[2];
        unsigned char cBanderas[2];
        unsigned char cQDcount[2];
        unsigned char cANcount[2];
        unsigned char cNScount[2];
        unsigned char cARcount[2];
        string getDom(string bytes, int bytesStart);
        string getDomType(string bytes, int byteStart);
        string getDomClass(string bytes, int byteStart);
        string getRData(string bytes, int byteStart, string type);


        DNSQuestion questions[5];
        DNSAnswer answers[5];

        void asignarBytes(string cadenaBytes);
        void defID();
        void defBanderas();
        void defContadores();
        int question(string cadenaBytes, int startByte, int no_question);
        int answer(string cadenaBytes, int startByte, int no_question);
    public:
        DNS(string cadenaBytes);
        string id;
        string banderaQR;
        string banderaOPcode;
        string banderaAA;
        string banderaTC;
        string banderaRD;
        string banderaRA;
        string banderaZ;
        string banderaAD;
        string banderaCD;
        string banderaRcode;
        int qdcount;
        int ancount;
        int nscount;
        int arcount;
        string infoRest="";

        void printInfo();



};


#endif // IP_H
