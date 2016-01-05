/* 
 * File:   restricao.cpp
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 14:54
 */

#include "restricao.h"

Restricao Restricao::operator =(const Restricao &_r)
{
    this->penalidade = _r.penalidade;
    this->preferencias = _r.preferencias;
    
    return (*this);
}
