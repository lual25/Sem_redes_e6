#ifndef FUNCIONESAUX_H
#define FUNCIONESAUX_H
#include <string>
#include <math.h>
#include <iostream>

using namespace std;

int bin_dec(string bin)
{
    int value = 0;
    int indexCounter = 0;
    for(int i=bin.size()-1;i>=0;i--){

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
    for(int i=0; i<cadena.size(); i++)
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

string dec_hex(int value, bool first = true)
{

    if (value == 0)
    {
        if(first)
            return "00";
        return "";
    }
    string hex="";
    int rem = value % 16;
    value /= 16;
    hex += dec_hex(value, false); //first execute recurency and print next value

    //after return print the less significant digit
    if (rem > 9)
        hex += (char)(rem - 10 + 'A');
    else
        hex += to_string(rem);
    return hex;
}
#endif
