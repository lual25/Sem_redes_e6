#ifndef FUNCIONESAUX_H
#define FUNCIONESAUX_H
#include <string>
#include <math.h>
#include <iostream>

using namespace std;
bool isNumber(string s)
{
    for( int i = 0; i < s.length(); i++ ) {
      if( !isdigit( s[i] )) {
         return false;
      }
   }
   return true;
 }

string hexToASCII(string hex)
{
    // initialize the ASCII code string as empty.
    string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        // extract two characters from hex string
        string part = hex.substr(i, 2);

        // change it into base 16 and
        // typecast as the character
        char ch = stoul(part, nullptr, 16);

        // add this char to final ASCII string
        ascii += ch;
    }
    return ascii;
}
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

double bin_double(string bin)
{
    double value = 0;
    int indexCounter = 0;
    for(int i=bin.size()-1;i>=0;i--){

        if(bin[i]=='1'){
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}

string char_bin(char chex)
{
    unsigned char hex = chex;
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
        unsigned char c = cadena[i];
        bin += char_bin(c);
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
    if(hex.length()<2 && first)
        for(int i = hex.length(); i<2; i++) //Rellena con 0 los espacios vacios
            hex = "0" + hex;
    return hex;
}
 string char_hex(char chex)
{
    return dec_hex(bin_dec(char_bin(chex)));
}

#endif
