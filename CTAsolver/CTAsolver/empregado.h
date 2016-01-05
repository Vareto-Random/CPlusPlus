/* 
 * File:   empregado.h
 * Author: Rafael Vareto
 *
 * Created on 2 de Novembro de 2015, 21:42
 */

#ifndef EMPREGADO_H
#define	EMPREGADO_H

#include "biblioteca.h"

class Empregado
{
public:
    Empregado();
    Empregado(int, int, char, int);
    Empregado operator =(Empregado &);
    
    void inicializa(int, int, char, int);
    
    int id;
    int dia;
    char turno;
    int turnoNum;
};


#endif	/* EMPREGADO_H */

