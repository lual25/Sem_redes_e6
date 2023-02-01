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
    string tipoServicio;

    void setVersion(char palabra);
    void setTamCabecera(char palabra);


};

#endif // IP_H
