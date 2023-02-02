#include "ip.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <iostream>
#include <math.h>

using namespace std;






string tipoServicio(char palabra)
{
    string servicio;
    for(int i=7;i>=0;i--)
        servicio+=((palabra & (1 << i)) ? '1' : '0');
    return servicio;
}




int main()
{
    string ipv4;
    unsigned char palabra;
    unsigned char tipo;
    int i;


    FILE *archivo;

    if ((archivo = fopen(".\\paquetes\\ethernet_ipv4_icmp.bin","rb+")) == NULL)
        {
         cout<<"Error en la apertura. Es posible que el fichero no exista \n";
        }

    else{
            cout<<"\t\t\t\n ETHERNET\n\n";
            cout<<"Direccion MAC destino:\n";
            for(i=0;i<=5;i++){
                palabra = fgetc(archivo);
                printf("%02x:",palabra);
            }

            cout<<"\n";

            cout<<"Direccion MAC origen:\n";
            for(i=0;i<=5;i++){
                palabra=fgetc(archivo);
                printf ("%02x:",palabra);
            }
            cout<<"\n";

            cout<<"Tipo de codigo:\n";
            for(i=0;i<=1;i++){
                palabra=fgetc(archivo);
                tipo+=palabra;
                printf ("%02x:",palabra);
            }cout<<"\n";

            cout<<"Tipo: ";


            switch(tipo){
            case 8:
                cout<<"IPv4 \n";
                break;
            case 14:
                cout<<"ARP \n";
                break;
            case 181:
                cout<<"RARP \n";
                break;
            case 355:
                cout<<"IPv6 \n";
                break;
            }

            palabra=fgetc(archivo);

            IPv4 x;
            x.setVersion(palabra);
            x.setTamCabecera(palabra);


            cout<<"Version: "<<"\n";
            cout<<x.version<<endl;

            cout<<"Tamano de cabecera: "<<"\n";
            cout<<x.tamCabecera<<endl;


            cout<<"Tipo servicio: ";
            palabra=fgetc(archivo);
            x.setTipoServicio(palabra);
            cout<<x.tipoServicio<<endl;
            cout<<x.desgloseBits<<endl;
            cout<<"Retardo: "<<x.retardo<<endl;
            cout<<"Rendimiento: "<<x.rendimiento<<endl;
            cout<<"Fiabilidad: "<<x.fiabilidad<<endl;
            cout<<"\n";



            cout<<"Datos: ";
            while (!feof(archivo)){

                palabra=fgetc(archivo);
                printf ("%02x:",palabra);
            }
            cout<<"\n";
    }
        fclose(archivo);
        return (0);
}
