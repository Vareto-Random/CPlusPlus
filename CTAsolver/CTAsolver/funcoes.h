/* 
 * File:   funcoes.h
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 22:26
 */

#ifndef FUNCOES_H
#define	FUNCOES_H

#include "biblioteca.h"

int numAleatorio(int, int, int = -1);

bool remove(vector<int> &, int); //remove de um vetor o valor X se existir

//PROGRAMACAO GENERICA
template<typename T> 
T valoresComuns(T a, T b)//Retorna valores semelhantes entre dois containers
{
    typename T::iterator itA;
    typename T::iterator itB;
    T lista;
    
    for(itA = a.begin(); itA != a.end(); itA++)
        for(itB = b.begin(); itB != b.end(); itB++)
            if( (*itA) == (*itB) )
                lista.insert(lista.end(), *itA);
    
    return lista;
};

template<typename T>
T valoresComuns(T a, T b, T c)//Retorna valores semelhantes entre tres containers
{
    T lista1, lista2;
    
    lista1 = valoresComuns(a, b);
    lista2 = valoresComuns(lista1, c);
    
    return lista2;
}

template<typename T> 
T valoresIncomuns(T a, T b)//Retorna valores NAO semelhantes entre dois containers
{
    int cont;
    typename T::iterator itA;
    typename T::iterator itB;
    T lista;
    
    for(itA = a.begin(); itA != a.end(); itA++)
    {
        cont = 0;
        for(itB = b.begin(); itB != b.end(); itB++)
            if( (*itA) != (*itB) )
                cont++;
        
        if( cont == b.size() )
            lista.insert(lista.end(), *itA);
    }
    
    return lista;
};

template<typename T>
T valoresIncomuns(T a, T b, T c)//Retorna valores NAO semelhantes entre tres containers
{
    T lista1, lista2;
    
    lista1 = valoresIncomuns(a, b);
    lista2 = valoresIncomuns(lista1, c);
    
    return lista2;
}

#endif	/* FUNCOES_H */

