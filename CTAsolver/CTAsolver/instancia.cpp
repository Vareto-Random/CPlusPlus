/*
 * File:   instancia.cpp
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 12:25
 */

#include "instancia.h"

//PUBLIC
Instancia::Instancia(void)
{
    this->numDias = 0;

    this->numCTAs = 0;
    this->numCTAm = 0;
    this->numCTAt = 0;
    this->numCTAn = 0;
}

Instancia::Instancia(int _numDias, int _numCTAs, int _numCTAm, int _numCTAt, int _numCTAn)
{
    atualiza(_numDias, _numCTAs, _numCTAm, _numCTAt, _numCTAn);
}

Instancia::Instancia(const Instancia &_i)
{
    this->numDias = _i.numDias;
    this->numCTAs = _i.numCTAs;
    this->numCTAm = _i.numCTAm;
    this->numCTAt = _i.numCTAt;
    this->numCTAn = _i.numCTAn;
    this->vCTAs = _i.vCTAs;
}

Instancia Instancia::operator =(const Instancia &_i)
{
    this->numDias = _i.numDias;
    this->numCTAs = _i.numCTAs;
    this->numCTAm = _i.numCTAm;
    this->numCTAt = _i.numCTAt;
    this->numCTAn = _i.numCTAn;
    this->vCTAs = _i.vCTAs;

    return (*this);
}

bool Instancia::atualiza(int _numDias, int _numCTAs, int _numCTAm, int _numCTAt, int _numCTAn)
{
    if( (_numDias > 0) && (_numCTAs > 0) && (_numCTAm > 0) && (_numCTAt > 0) && (_numCTAn > 0) )
    {
        this->numDias = _numDias;

        this->numCTAs = _numCTAs;
        this->numCTAm = _numCTAm;
        this->numCTAt = _numCTAt;
        this->numCTAn = _numCTAn;

        this->vCTAs.resize(this->numCTAs);

        return true;
    }
    return false;
}

void Instancia::setNumDias(int _numDias)
{
    this->numDias = _numDias;
}

void Instancia::setNumCTAs(int _numCTAs)
{
    this->numCTAs = _numCTAs;
}

void Instancia::setNumCTAm(int _numCTAm)
{
    this->numCTAm = _numCTAm;
}

void Instancia::setNumCTAt(int _numCTAt)
{
    this->numCTAt = _numCTAt;
}

void Instancia::setNumCTAn(int _numCTAn)
{
    this->numCTAn = _numCTAn;
}

void Instancia::setPenCTA(int _id, int _penalidade)
{
    this->vCTAs[_id].penalidade = _penalidade;
}

bool Instancia::setCTA(int _id, int _dia, char _turno)
{
    if( (_id >= 0) && (_id < this->numCTAs) && (_dia >= 0) && (_dia < this->numDias) )
    {
        set<char> tempS;

        //caso conjunto ainda nao tenha sido usado
        if( this->vCTAs[_id].preferencias.find(_dia) == this->vCTAs[_id].preferencias.end() )
            this->vCTAs[_id].preferencias.insert(pair< int, set<char> > (_dia, tempS));

        tempS = this->vCTAs[_id].preferencias[_dia];
        tempS.insert(_turno);
        this->vCTAs[_id].preferencias[_dia] = tempS;

        return true;
    }
    return false;
}

int Instancia::getNumDias(void)
{
    return this->numDias;
}

int Instancia::getNumCTAs(void)
{
    return this->numCTAs;
}

int Instancia::getNumCTAm(void)
{
    return this->numCTAm;
}

int Instancia::getNumCTAt(void)
{
    return this->numCTAt;
}

int Instancia::getNumCTAn(void)
{
    return this->numCTAn;
}

int Instancia::getPenCTA(int _id)
{
    if( (_id >= 0) && ( this->numCTAs > _id ) )
        return this->vCTAs[_id].penalidade;
    else
    {
        cout << endl << "ERRO Instancia::getPenCTA(int _id)" << endl;
        exit(1);
    }
}

Restricao Instancia::getCTA(int _id)
{
    if( (_id >= 0) && ( this->numCTAs > _id ) )
        return this->vCTAs[_id];
    else
    {
        cout << endl << "ERRO Instancia::getCTA(int _id)" << endl;
        exit(1);
    }
}

void Instancia::printCTA(int _id)
{
    Restricao empregado;
    set<char> periodo;
    map< int, set<char> >::iterator itM;
    set<char>::iterator itS;

    empregado = this->getCTA(_id);
    cout << endl << "Id: " << _id << endl << "Num Dias: " << empregado.preferencias.size() << endl << "Penalidade: " << empregado.penalidade << endl << "Dias: " << endl;
    for( itM = empregado.preferencias.begin(); itM != empregado.preferencias.end(); itM++ )
    {
        cout << itM->first << ":";
        periodo = itM->second;
        for( itS = periodo.begin(); itS != periodo.end(); itS++ )
            cout << " " << (*itS);
        cout << endl;
    }
}

vector<int> Instancia::getTodos(void)
{
    vector<int> lista;

    for(unsigned int i = 0; i < this->vCTAs.size(); i++)
        lista.push_back(i);

    return lista;
}

bool Instancia::getDisponiveis(int _id, int _dia, char _turno)
{
    if( (_id >= 0) && (_id < this->numCTAs) && (_dia >= 0) && (_dia < this->numDias) )
    {
        if( this->vCTAs[_id].preferencias.find(_dia) != this->vCTAs[_id].preferencias.end() )
            if( this->vCTAs[_id].preferencias[_dia].find(_turno) != this->vCTAs[_id].preferencias[_dia].end() )
                return false;

        return true;
    }

    return false;
}

inline bool Instancia::getNaoDisponiveis(int _id, int _dia, char _turno)
{
    if( (_id >= 0) && (_id < this->numCTAs) && (_dia >= 0) && (_dia < this->numDias) )
    {
        if( this->vCTAs[_id].preferencias.find(_dia) != this->vCTAs[_id].preferencias.end() )
            if( this->vCTAs[_id].preferencias[_dia].find(_turno) != this->vCTAs[_id].preferencias[_dia].end() )
                return true;
    }

    return false;
}

vector<int> Instancia::getDisponiveis(int _dia, char _turno) //retorna id e penalidade dos CTAs que podem trabalhar no dia D e no turno T
{
    vector<int> lista;

    if( (_dia >= 0) && (_dia < this->numDias) )
    {
        for( unsigned int i = 0; i < this->vCTAs.size(); i++ )
        {
            if( this->vCTAs[i].preferencias.find(_dia) != this->vCTAs[i].preferencias.end() )
            {
                if( this->vCTAs[i].preferencias[_dia].find(_turno) == this->vCTAs[i].preferencias[_dia].end() )
                    lista.push_back(i);
            }
            else if( this->vCTAs[i].preferencias.find(_dia) == this->vCTAs[i].preferencias.end() )
                lista.push_back(i);
        }
    }

    return lista;
}

vector<int> Instancia::getNaoDisponiveis(int _dia, char _turno) //retorna id e penalidade dos CTAs que nao querem trabalhar no dia D e no turno T
{
    vector<int> lista;

    if( ( _dia >= 0) && (_dia < this->numDias) )
        for(unsigned int i = 0; i < this->vCTAs.size(); i++)
            if( this->vCTAs[i].preferencias.find(_dia) != this->vCTAs[i].preferencias.end() )
                if( this->vCTAs[i].preferencias[_dia].find(_turno) != this->vCTAs[i].preferencias[_dia].end() )
                    lista.push_back(i);

    return lista;
}

int Instancia::buscaPenalidade(vector<int> &_ids, int _tipo)
{
    int id, penalidade;

    id = -1;

    if(_tipo == MAIOR_VALOR)
    {
        id = numeric_limits<int>::min();
        penalidade = numeric_limits<int>::min();

        if(_ids.size() > 0)
        {
            for(unsigned int i = 0; i < _ids.size(); i++)
            {
                if( this->vCTAs[ _ids[i] ].penalidade > penalidade )
                {
                    id = _ids[i];
                    penalidade = this->vCTAs[ _ids[i] ].penalidade;
                }
            }
        }
    }
    else if(_tipo == MENOR_VALOR)
    {
        id = numeric_limits<int>::max();
        penalidade = numeric_limits<int>::max();

        if(_ids.size() > 0)
        {
            for(unsigned int i = 0; i < _ids.size(); i++)
            {
                if( this->vCTAs[ _ids[i] ].penalidade < penalidade )
                {
                    id = _ids[i];
                    penalidade = this->vCTAs[ _ids[i] ].penalidade;
                }
            }
        }
    }

    return id;
}

vector<int> Instancia::buscaPenalidades(vector<int> &_ids)
{
    vector<int> listaPenalidades;

    if(_ids.size() > 0)
        for(unsigned int i = 0; i < _ids.size(); i++)
            listaPenalidades.push_back( this->vCTAs[ _ids[i] ].penalidade );

    return listaPenalidades;
}

bool Instancia::leitura(string nome)
{
    ifstream arquivo;

    arquivo.open(nome.c_str(), ifstream::in);

    if( arquivo.is_open() )
    {
        //lê numero de dias
        arquivo >> this->numDias;

        //lê numero de CTAs disponiveis
        arquivo >> this->numCTAs;

        //lê numero de CTAs necessários para a manhã
        arquivo >> this->numCTAm;

        //lê numero de CTAs necessários para a tarde
        arquivo >> this->numCTAt;

        //lê numero de CTAs necessários para a noite
        arquivo >> this->numCTAn;

        atualiza(this->numDias, this->numCTAs, this->numCTAm, this->numCTAt, this->numCTAn);

        while( arquivo.good() )
        {
            int id;
            int penalidade;
            int dia;
            char turno;

            arquivo >> id;
            arquivo >> penalidade;
            this->setPenCTA(id, penalidade);

            do
            {
                arquivo >> dia;
                if( dia != -1 )
                {
                    arquivo >> turno;
                    dia = dia - 1;
                    setCTA(id, dia, turno);
                }
            }
            while( dia != -1 );
        }

        arquivo.close();

        return true;
    }
    else
    {
        cout << endl << "ERRO Instancia::leitura(string nome)" << endl;
        exit(1);
    }

    return false;
}
