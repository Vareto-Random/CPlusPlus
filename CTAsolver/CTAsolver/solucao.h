/* 
 * File:   solucao.h
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 15:39
 */

#ifndef SOLUCAO_H
#define	SOLUCAO_H

#include "biblioteca.h"

class Solucao
{
public:
    Solucao operator=(Solucao &);
    
    int penalidade;
    vector< vector<char> > escala;
    vector< vector<int> > escalaNum;
};

#endif	/* SOLUCAO_H */

