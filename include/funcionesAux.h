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
#endif