/*
 * File:   controlador.cpp
 * Author: Rafael Vareto
 *
 * Created on 21 de Outubro de 2015, 14:31
 */

#include "ctas.h"
CTA CTA::operator =(const CTA &_c)
{
    this->numFolgas = _c.numFolgas;
    this->numFolgasCons = _c.numFolgasCons;
    this->numManhas = _c.numManhas;
    this->numNoites = _c.numNoites;
    this->numNoitesCons = _c.numNoitesCons;
    this->numServicosCons = _c.numServicosCons;
    this->numTardes = _c.numTardes;
    this->numTurnos = _c.numTurnos;

    return (*this);
}




//PUBLIC
CTAs::CTAs(void)
{
}

CTAs::CTAs(int _numCTAs)
{
    this->inicializa(_numCTAs);
}

CTAs::CTAs(const CTAs &_c)
{
    this->controladores = _c.controladores;
}

CTAs CTAs::operator =(const CTAs &_c)
{
    this->controladores = _c.controladores;
    return (*this);
}

bool CTAs::inicializa(int _numCTAs)
{
    if(_numCTAs > 0)
    {
        this->aloca(_numCTAs);
        this->nilTodos();

        return true;
    }
    return false;
}

bool CTAs::aloca(int _numCTAs)
{
    if(_numCTAs > 0)
    {
        this->controladores.resize(_numCTAs);
        return true;
    }
    return false;
}


//------------------------------------------------------------------------------

bool CTAs::nilTodos(void)
{
    if(this->controladores.size() > 0)
    {
        for(unsigned int i = 0; i < this->controladores.size(); i++)
                this->nilTodos(i);
        return true;
    }
    return false;
}

bool CTAs::nilTodos(int _id)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->nilNumTurnos(_id);
        this->nilNumManhas(_id);
        this->nilNumTardes(_id);
        this->nilNumNoites(_id);
        this->nilNumNoitesCons(_id);
        this->nilNumServicosCons(_id);
        this->nilNumFolgasCons(_id);

        return true;
    }
    return false;
}

bool CTAs::atualiza(vector< vector<char> > &_escala)
{
    this->nilTodos();

    for(unsigned int i = 0; i < _escala.size(); i++)
    {
        for(unsigned int j = 0; j < _escala[i].size(); j++)
            this->atribui(i, _escala[i][j]);
    }
    return true;
}

//------------------------------------------------------------------------------

vector<int> CTAs::getDisponiveis(char _turno)
{
    bool cond;
    vector<int> aptos;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
    {
       cond = this->simula(i, _turno);
       if(cond)
           aptos.push_back(i);
    }

    return aptos;
}

vector<int> CTAs::getNaoDisponiveis(char _turno)
{
    bool cond;
    vector<int> ocupados;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
    {
        cond = this->simula(i, _turno);
        if(!cond)
            ocupados.push_back(i);
    }

    return ocupados;
}

//------------------------------------------------------------------------------

bool CTAs::incCTA(int _id, char _turno)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        switch(_turno)
        {
            case MANHA:
                this->incNumManhas(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case TARDE:
                this->incNumTardes(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case NOITE:
                this->incNumNoites(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case FOLGA:
                this->incNumFolgas(_id);
                return true;
            break;
            default:
                return false;
            break;
        }
    }
    return false;
}

bool CTAs::decCTA(int _id, char _turno)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        switch(_turno)
        {
            case MANHA:
                this->decNumManhas(_id);
                this->decNumTurnos(_id);
                return true;
            break;
            case TARDE:
                this->decNumTardes(_id);
                this->decNumTurnos(_id);
                return true;
            break;
            case NOITE:
                this->decNumNoites(_id);
                this->decNumTurnos(_id);
                return true;
            break;
            case FOLGA:
                this->decNumFolgas(_id);
                return true;
            break;
            default:
                return false;
            break;
        }
    }
    return false;
}

bool CTAs::simula(int _id, char _turno)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        CTA temp;
        temp = this->controladores[_id];

        switch(_turno)
        {
            case MANHA:
                temp.numManhas++;
                temp.numServicosCons++;
                temp.numNoitesCons = 0;
                temp.numFolgasCons = 0;
                temp.numTurnos++;
            break;
            case TARDE:
                temp.numTardes++;
                temp.numServicosCons++;
                temp.numNoitesCons = 0;
                temp.numFolgasCons = 0;
                temp.numTurnos++;
            break;
            case NOITE:
                temp.numNoites++;
                temp.numServicosCons++;
                temp.numNoitesCons++;
                temp.numFolgasCons = 0;
                temp.numTurnos++;
            break;
            case FOLGA:
                temp.numFolgas++;
                temp.numFolgasCons++;
                temp.numServicosCons = 0;
                temp.numNoitesCons = 0;
            break;
            default:
                return false;
            break;
        }

        if( (temp.numManhas <= MAX_MANHA) && (temp.numTardes <= MAX_TARDE) && (temp.numNoites <= MAX_NOITE) &&
            (temp.numServicosCons <= MAX_SERVICOS_CONS) && (temp.numNoitesCons <= MAX_NOITE_CONS) &&
            (temp.numFolgasCons <= MAX_FOLGAS_CONS) && (temp.numTurnos <= MAX_TURNO) )
            return true;
    }

    return false;
}

bool CTAs::atribui(int _id, char _turno)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        switch(_turno)
        {
            case MANHA:
                this->incNumManhas(_id);
                this->incNumServicosCons(_id);
                this->nilNumNoitesCons(_id);
                this->nilNumFolgasCons(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case TARDE:
                this->incNumTardes(_id);
                this->incNumServicosCons(_id);
                this->nilNumNoitesCons(_id);
                this->nilNumFolgasCons(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case NOITE:
                this->incNumNoites(_id);
                this->incNumServicosCons(_id);
                this->incNumNoitesCons(_id);
                this->nilNumFolgasCons(_id);
                this->incNumTurnos(_id);
                return true;
            break;
            case FOLGA:
                this->incNumFolgas(_id);
                this->incNumFolgasCons(_id);
                this->nilNumServicosCons(_id);
                this->nilNumNoitesCons(_id);
                return true;
            break;
            default:
                return false;
            break;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

int CTAs::getNumManhas(int _id)
{
    return this->controladores[_id].numManhas;
}

int CTAs::getNumTardes(int _id)
{
    return this->controladores[_id].numTardes;
}

int CTAs::getNumNoites(int _id)
{
    return this->controladores[_id].numNoites;
}

int CTAs::getNumTurnos(int _id)
{
    return this->controladores[_id].numTurnos;
}

int CTAs::getNumFolgas(int _id)
{
    return this->controladores[_id].numFolgas;
}

int CTAs::getNumNoitesCons(int _id)
{
    return this->controladores[_id].numNoitesCons;
}

int CTAs::getNumServicosCons(int _id)
{
    return this->controladores[_id].numServicosCons;
}

int CTAs::getNumFolgasCons(int _id)
{
    return this->controladores[_id].numFolgasCons;
}


//------------------------------------------------------------------------------

bool CTAs::setNumManhas(int _id, int _numManhas)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numManhas = _numManhas;
        return true;
    }
    return false;
}

bool CTAs::setNumTardes(int _id, int _numTardes)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numTardes = _numTardes;
        return true;
    }
    return false;
}

bool CTAs::setNumNoites(int _id, int _numNoites)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numNoites = _numNoites;
        return true;
    }
    return false;
}

bool CTAs::setNumTurnos(int _id, int _numTurnos)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numTurnos = _numTurnos;
        return true;
    }
    return false;
}

bool CTAs::setNumFolgas(int _id, int _numFolgas)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numFolgas = _numFolgas;
        return true;
    }
    return false;
}

bool CTAs::setNumNoitesCons(int _id, int _numNoitesCons)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numNoitesCons = _numNoitesCons;
        return true;
    }

    return false;
}

bool CTAs::setNumServicosCons(int _id, int _numServicosCons)
{
    if( (_id >= 0) && (_id < (int)this->controladores.size()) )
    {
        this->controladores[_id].numServicosCons = _numServicosCons;
        return true;
    }
    return false;
}

bool CTAs::setNumFolgasCons(int _id, int _numFolgasCons)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numFolgasCons = _numFolgasCons;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

bool CTAs::nilNumManhas(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numManhas = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumTardes(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numTardes = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumNoites(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numNoites = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumTurnos(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numTurnos = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumFolgas(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numFolgas = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumNoitesCons(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numNoitesCons = 0;
        return true;
    }

    return false;
}

bool CTAs::nilNumServicosCons(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numServicosCons = 0;
        return true;
    }
    return false;
}

bool CTAs::nilNumFolgasCons(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
        this->controladores[_id].numFolgasCons = 0;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

vector<int> CTAs::getCTAsManhasMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numManhas >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsTardesMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numTardes >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsNoitesMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numNoites >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsTurnosMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numTurnos >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsFolgasMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numFolgas >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsNoitesConsMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numNoitesCons >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsServicosConsMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numServicosCons >= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsFolgasConsMais(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numFolgasCons >= _qtd)
            lista.push_back(i);
    return lista;
}

//------------------------------------------------------------------------------

vector<int> CTAs::getCTAsManhasMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numManhas <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsTardesMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numTardes <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsNoitesMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numNoites <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsTurnosMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numTurnos <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsFolgasMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numFolgas <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsNoitesConsMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numNoitesCons <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsServicosConsMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numServicosCons <= _qtd)
            lista.push_back(i);
    return lista;
}

vector<int> CTAs::getCTAsFolgasConsMenos(int _qtd)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->controladores.size(); i++)
        if(this->controladores[i].numFolgasCons <= _qtd)
            lista.push_back(i);
    return lista;
}

//------------------------------------------------------------------------------


bool CTAs::incNumManhas(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numManhas++;
       return true;
   }
   return false;
}

bool CTAs::incNumTardes(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numTardes++;
       return true;
   }
   return false;
}

bool CTAs::incNumNoites(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numNoites++;
       return true;
   }
   return false;
}

bool CTAs::incNumFolgas(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numFolgas++;
       return true;
   }
   return false;
}

bool CTAs::incNumNoitesCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numNoitesCons++;
       return true;
   }
   return false;
}

bool CTAs::incNumServicosCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numServicosCons++;
       return true;
   }
   return false;
}

bool CTAs::incNumFolgasCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numFolgasCons++;
       return true;
   }
   return false;
}

bool CTAs::incNumTurnos(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
   {
       this->controladores[_id].numTurnos++;
       return true;
   }
   return false;
}

//------------------------------------------------------------------------------

bool CTAs::decNumManhas(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numManhas > 0) )
   {
       this->controladores[_id].numManhas--;
       return true;
   }
   return false;
}

bool CTAs::decNumTardes(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numTardes > 0) )
   {
       this->controladores[_id].numTardes--;
       return true;
   }
   return false;
}

bool CTAs::decNumNoites(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numNoites > 0) )
   {
       this->controladores[_id].numNoites--;
       return true;
   }
   return false;
}

bool CTAs::decNumFolgas(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numFolgas > 0) )
   {
       this->controladores[_id].numFolgas--;
       return true;
   }
   return false;
}

bool CTAs::decNumNoitesCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numNoitesCons > 0) )
   {
       this->controladores[_id].numNoitesCons--;
       return true;
   }
   return false;
}

bool CTAs::decNumServicosCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numServicosCons > 0) )
   {
       this->controladores[_id].numServicosCons--;
       return true;
   }
   return false;
}

bool CTAs::decNumFolgasCons(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numFolgasCons > 0) )
   {
       this->controladores[_id].numFolgasCons--;
       return true;
   }
   return false;
}

bool CTAs::decNumTurnos(int _id)
{
   if( (_id >= 0) && ( _id < (int)this->controladores.size() ) && (this->controladores[_id].numTurnos > 0) )
   {
       this->controladores[_id].numTurnos--;
       return true;
   }
   return false;
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

bool CTAs::printCTA(int _id)
{
    if( (_id >= 0) && ( _id < (int)this->controladores.size() ) )
    {
       cout << endl << "MANHA: " << this->getNumManhas(_id)
            << endl << "TARDE: " << this->getNumTardes(_id)
            << endl << "NOITE: " << this->getNumNoites(_id)
            << endl << "FOLGA: " << this->getNumFolgas(_id)
            << endl << "NOITEScONS: " << this->getNumNoitesCons(_id)
            << endl << "SERVICOScONS: " << this->getNumServicosCons(_id)
            << endl << "FOLGAScONS: " << this->getNumFolgasCons(_id)
            << endl << "TURNOS: " << this->getNumTurnos(_id);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
