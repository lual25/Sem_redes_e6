#ifndef IP_H
#define IP_H


#include <string>
using namespace std;
class IPv4
{
    public:
    IPv4();
    int version;
    int tamCabecera;
    string desgloseBits;
    string tipoServicio = "00000000";
    string retardo;
    string rendimiento;
    string fiabilidad;
    int logTotal;

    void setVersion(char palabra);
    void setTamCabecera(char palabra);
    void setTipoServicio(char palabra);
    void setDesgloseBits();
    void setLogTotal(char palabra1, char palabra2);



};

#endif // IP_H
