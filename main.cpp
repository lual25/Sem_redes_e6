#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <iostream>
#include <math.h>

using namespace std;

int bin_dec(string bin)
{
    int value = 0;
    int indexCounter = 0;
    for(int i=bin.length()-1;i>=0;i--){

        if(bin[i]=='1'){
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}

int version(char palabra)
{
    string version;
   for(int i=7;i>=4;i--)
        version+=((palabra & (1 << i)) ? '1' : '0');
    return bin_dec(version);

}

int tamanoCab(char palabra)
{
    string longitud;
   for(int i=3;i>=0;i--)
        longitud+=((palabra & (1 << i)) ? '1' : '0');
    return bin_dec(longitud);
}

string tipoServicio(char palabra)
{
    string servicio;
    for(int i=7;i>=0;i--)
        servicio+=((palabra & (1 << i)) ? '1' : '0');
    return servicio;
}




int main()
{


    unsigned char palabra;
    unsigned char tipo;
    int i;


    FILE *archivo;

    if ((archivo = fopen(".\\paquetes\\ethernet_1.bin","rb+")) == NULL)
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


            cout<<"Version: "<<"\n";
            cout<<version(palabra)<<endl;
            cout<<"\n";

            cout<<"Tamano de cabecera: "<<"\n";
            cout<<tamanoCab(palabra)<<endl;
            cout<<"\n";


            cout<<"Tipo servicio: "<<"\n";
            palabra=fgetc(archivo);
            cout<<tipoServicio(palabra)<<endl;
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
