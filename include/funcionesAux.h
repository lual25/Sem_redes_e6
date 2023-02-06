#ifndef FUNCIONESAUX_H
#define FUNCIONESAUX_H
#include <string>
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

string char_bin(char hex)
{
    string bin="";
    for(int i=7;i>=0;i--)
        bin+=((hex & (1 << i)) ? '1' : '0');
    return bin;
}

string string_bin(string cadena)
{
    string bin="";
    for(int i=0; i<cadena.length()-1; i++)
    {
        bin += char_bin(cadena[i]);
    }
    return bin;
}

uint32_t ascii_hex(const char* src) {
    uint32_t ret = 0;
    char* dst = (char*)&ret;
    for(int i = 0; (i < 4) && (*src); ++i, ++src)
      dst[i] = *src;

    return ret;
  }
#endif
