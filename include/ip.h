#ifndef IP_H
#define IP_H


#include <string>
using namespace std;
class IPv4
{
protected: //Division de palabras correspondiantes
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

    void setVersion();
    void setTamCabecera();
    void setTipoServicio();
    void desglosarBits();
    void setLogTotal();
    void printDivBytes();
    void printInfo();
    void setIdentificador();
    void setProtocolo();
    void setTtl();
    void setIPs();
    void setFlags();
    void setPosFragmento(string binario);



};

#endif // IP_H
