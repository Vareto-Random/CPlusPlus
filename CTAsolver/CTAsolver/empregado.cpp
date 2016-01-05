/* 
 * File:   empregado.cpp
 * Author: Rafael Vareto
 *
 * Created on 2 de Novembro de 2015, 21:42
 */

#include "empregado.h"

Empregado::Empregado()
{}

Empregado::Empregado(int _id, int _dia, char _turno, int _turnoNum)
{
    this->inicializa(_id, _dia, _turno, _turnoNum);
}

Empregado Empregado::operator =(Empregado &_e)
{
    this->id = _e.id;
    this->dia = _e.dia;
    this->turno = _e.turno;
    this->turnoNum = _e.turnoNum;
    
    return (*this);
}

void Empregado::inicializa(int _id, int _dia, char _turno, int _turnoNum)
{
    this->id = _id;
    this->dia = _dia;
    this->turno = _turno;
    this->turnoNum = _turnoNum;
}