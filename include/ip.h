#ifndef IP_H
#define IP_H


#include <string>
using namespace std;
class IPv4
{
protected: //Division de palabras correspondiantes
    string cadenaBytes;
    void asignarBytes(string cadenaBytes);
    unsigned char versionTCabecera;
    unsigned char tServicio;
    unsigned char longTotal[2];
    unsigned char id[2];
    unsigned char flagsPFrag[2];
    unsigned char tVida;
    unsigned char protocolo;
    unsigned char checkSum[2];
    unsigned char ipOrigen[4];
    unsigned char ipDestino[4];
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

    void setVersion();
    void setTamCabecera();
    void setTipoServicio();
    void desglosarBits();
    void setLogTotal();
    void printDivBytes();
    void printInfo();



};

#endif // IP_H
