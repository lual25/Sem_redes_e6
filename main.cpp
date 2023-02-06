#include "ip.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <iostream>
#include <math.h>

using namespace std;



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

            string info;
            while (!feof(archivo)){
                palabra=fgetc(archivo);
                info += palabra;
                //printf ("%02x:",palabra);
            }

            cout<<"Tipo: ";


            switch(int(tipo)){
            case 8:
                {
                    cout<<"IPv4 \n";
                   IPv4 _ipv4(info);
                   _ipv4.printInfo();
                   _ipv4.printDivBytes();
                }
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
            default:
                cout<<"Tipo no identificado \n";
                break;
            }

        fclose(archivo);

        return (0);
    }
}
