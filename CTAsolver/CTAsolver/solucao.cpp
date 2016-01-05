/* 
 * File:   solucao.h
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 15:39
 */

#include "solucao.h"

Solucao Solucao::operator =(Solucao &_s)
{
    this->penalidade = _s.penalidade;
    this->escala = _s.escala;
    this->escalaNum = _s.escalaNum;
    
    return (*this);
}