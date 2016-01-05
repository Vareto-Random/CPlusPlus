/* 
 * File:   restricao.h
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 14:54
 */

#ifndef RESTRICAO_H
#define	RESTRICAO_H

#include "biblioteca.h"

class Restricao 
{
public:
    Restricao operator =(const Restricao &);
    
    int penalidade;
    map< int, set<char> > preferencias;
};


#endif	/* RESTRICAO_H */

