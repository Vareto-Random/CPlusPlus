/* 
 * File:   demanda.cpp
 * Author: Rafael Vareto
 *
 * Created on 27 de Outubro de 2015, 14:57
 */

#include "demanda.h"

Demanda::Demanda()
{
}

Demanda::Demanda(int _nDias, int _numCTAm, int _numCTAt, int _numCTAn)
{
    this->inicializa(_nDias, _numCTAm, _numCTAt, _numCTAn);
}

Demanda::Demanda(const Demanda &_d)
{
    this->manha = _d.manha;
    this->tarde = _d.tarde;
    this->noite = _d.noite;
}

Demanda Demanda::operator =(const Demanda &_d)
{
    this->manha = _d.manha;
    this->tarde = _d.tarde;
    this->noite = _d.noite;
    
    return (*this);
}

bool Demanda::aloca(int _nDias)
{
    if( _nDias > 0 )
    {
        this->manha.resize(_nDias);
        this->tarde.resize(_nDias);
        this->noite.resize(_nDias);
        return true;
    }
    return false;
}

bool Demanda::atualiza(int _numCTAm, int _numCTAt, int _numCTAn)
{
    if( (_numCTAm > 0) && (_numCTAt > 0) && (_numCTAn > 0) )
    {
        for( unsigned int i = 0; i < this->manha.size(); i++ )
        {
            this->manha[i] = _numCTAm;
            this->tarde[i] = _numCTAt;
            this->noite[i] = _numCTAn;
        }
        return true;
    }
    return false;
}

bool Demanda::inicializa(int _nDias, int _numCTAm, int _numCTAt, int _numCTAn)
{
    if( (_nDias > 0) && (_numCTAm > 0) && (_numCTAt > 0) && (_numCTAn > 0) )
    {
        this->aloca(_nDias);
        this->atualiza(_numCTAm, _numCTAt, _numCTAn);
        return true;
    }
    return false;
}

bool Demanda::decrementa(int _dia, char _turno)
{
    switch( _turno )
    {
    case MANHA:
        this->manha[_dia]--;
        return true;
        break;
    case TARDE:
        this->tarde[_dia]--;
        return true;
        break;
    case NOITE:
        this->noite[_dia]--;
        return true;
        break;
    case FOLGA:
        return true;
        break;
    default:
        return false;
        break;
    }
}

int Demanda::diaIncompleto()
{
    for( unsigned int i = 0; i < this->manha.size(); i++ )
    {
        if( this->manha[i] > 0 )
            return i;
        else if( this->tarde[i] > 0 )
            return i;
        else if( this->noite[i] > 0 )
            return i;
    }
    return -1;
}

char Demanda::turnoIncompleto(int _dia)
{
    if( this->manha[_dia] > 0 )
        return MANHA;
    else if( this->tarde[_dia] > 0 )
        return TARDE;
    else if( this->noite[_dia] > 0 )
        return NOITE;
    return VAZIO;
}