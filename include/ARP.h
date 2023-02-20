#ifndef ARP_H
#define ARP_H
#include <string>
using namespace std;

class ARP
{
    public:
        ARP(string cadenaBytes);
        int longHardware;
        int longProtocolo;

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
};

#endif // ARP_H
