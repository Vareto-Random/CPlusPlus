/* 
 * File:   funcoes.cpp
 * Author: Rafael Vareto
 * 
 * Created on 21 de Outubro de 2015, 14:31
 */

#include "funcoes.h"


int numAleatorio(int _inicio, int _fim, int _semente)
{
    int numero;
    
    if(_semente == -1)
        srand( (unsigned int) time(NULL) );
    else
        srand( _semente );
    
    numero = ( rand() % _fim );
    
    if(numero < _inicio)
        numero += _inicio;
    
    return numero;
}

bool remove(vector<int> &_lista, int _numero)
{
    for(unsigned int i = 0; i < _lista.size(); i++)
    {
        if(_lista[i] == _numero)
        {
            _lista.erase( _lista.begin() + i);
            return true;
        }
    }
    return false;
}