#include "ip.h"
#include "funcionesAux.h"
#include <iostream>
#include <string>
using namespace std;

IPv4::IPv4()
{

}
void IPv4::setVersion(char palabra)
{
    string version;
   for(int i=7;i>=4;i--)
        version+=((palabra & (1 << i)) ? '1' : '0');
    this->version= bin_dec(version);
}

void IPv4::setTamCabecera(char palabra)
{
    string longitud;
   for(int i=3;i>=0;i--)
        longitud+=((palabra & (1 << i)) ? '1' : '0');
    this->tamCabecera = bin_dec(longitud);
}
