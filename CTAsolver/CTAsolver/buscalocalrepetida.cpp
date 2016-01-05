/*
 * File:   buscalocalrepetida.cpp
 * Author: Rafael Vareto
 *
 * Created on 29 de Novembro de 2015, 10:05
 */

#include "buscalocalrepetida.h"

BuscaLocalRepetida::BuscaLocalRepetida(void)
{}

BuscaLocalRepetida::BuscaLocalRepetida(int _nDias, int _numCTAs) : Construtivo(_nDias, _numCTAs)
{}

BuscaLocalRepetida::BuscaLocalRepetida(Instancia _problema, CTAs _controladores) : Construtivo(_problema, _controladores)
{}

BuscaLocalRepetida::BuscaLocalRepetida(Construtivo &_c) : Construtivo(_c)
{}

BuscaLocalRepetida::BuscaLocalRepetida(BuscaLocalRepetida &_m)
{
    this->problema = _m.problema;
    this->controladores = _m.controladores;
    this->cobertura = _m.cobertura;

    this->escala = _m.escala;
    this->escalaNum = _m.escalaNum;

    this->resultado = _m.resultado;
}

BuscaLocalRepetida BuscaLocalRepetida::operator =(Construtivo &_c)
{
    this->problema = _c.getProblema();
    this->controladores = _c.getConstroladores();
    this->cobertura = _c.getCobertura();
    
    this->escala = _c.getEscala();
    this->escalaNum = _c.getEscalaNum();
    
    this->resultado.penalidade = _c.getResultado().penalidade;
    this->resultado.escala = _c.getResultado().escala;
    this->resultado.escalaNum = _c.getResultado().escalaNum;

    return (*this);
}

BuscaLocalRepetida BuscaLocalRepetida::operator =(BuscaLocalRepetida &_m)
{
    this->problema = _m.getProblema();
    this->controladores = _m.getConstroladores();
    this->cobertura = _m.getCobertura();
    this->escala = _m.getEscala();
    this->escalaNum = _m.getEscalaNum();

    return (*this);
}

//------------------------------------------------------------------------------

void BuscaLocalRepetida::executa(void)
{
    int solucaoInicial, solucaoFinal;
    
    for(unsigned int i = 0; i < NUM_TENTATIVA; i++)
    {
        cout << endl << "Iteracao " << i << " -  Penalidade: ";
        for(unsigned int j = 0; j < NUM_TENTATIVA/3; j++)
        {
            this->intensificacao(); //pertubação fraca
            do
            {
                if( this->minDemanda() )
                {
                    solucaoInicial = this->getPenalidadeTotal();

                    this->buscaLocal();
                    solucaoFinal = this->getPenalidadeTotal();

                    if( solucaoFinal < this->resultado.penalidade )
                    {
                        this->resultado.penalidade = solucaoFinal;
                        this->resultado.escala = this->escala;
                        this->resultado.escalaNum = this->escalaNum;
                        j = 0;
                    }
                    cout << solucaoFinal << ", "; fflush(stdout);
                }
                else
                {
                    cout << endl << "ERRO: Busca Local Inválida::Demanda nao satisfeita";
                    exit(1);
                }
            }
            while( solucaoFinal < solucaoInicial );
        }
        if ((i + 1) < NUM_TENTATIVA)
        {
            this->diversificacao(); //pertubação forte
        }
    }
    this->recuperaMelhorResultado();

    cout << endl << endl;
}


//------------------------------------------------------------------------------

//PROTECTED


inline void BuscaLocalRepetida::buscaLocal(void)
{
    this->trocaPreferencia(MANHA);
    this->trocaPreferencia(TARDE);
    this->trocaPreferencia(NOITE);

    this->trocaNoitesCons();
    this->trocaFolgasCons();
    this->trocaServicosCons();
    this->trocaTurnos();
    this->trocaManhas();
    this->trocaTardes();
    this->trocaNoites();

    this->controladores.atualiza( this->escala );
}

void BuscaLocalRepetida::diversificacao(void)
{
    int escolhido, candidato;
    vector<int> listaTodos;
    Empregado cta1, cta2;

    for( int dia = 0; dia < this->problema.getNumDias() - 1; dia++ )
    {
        listaTodos = this->problema.getTodos();
        for(unsigned int i = 0; i < 4; i++)
        {
            escolhido = this->problema.buscaPenalidade(listaTodos, MAIOR_VALOR);
            this->remove(listaTodos, escolhido);
            candidato = this->problema.buscaPenalidade(listaTodos, MAIOR_VALOR);
            this->remove(listaTodos, candidato);

            cta1.inicializa(escolhido, dia, this->escala[escolhido][dia], this->escalaNum[escolhido][dia]);
            cta2.inicializa(candidato, dia, this->escala[candidato][dia], this->escalaNum[candidato][dia]);
            this->troca(cta1, cta2);
        }
    }
}

void BuscaLocalRepetida::intensificacao(void)
{
    int sobrecarregado, candidato;
    vector<int> listaSobrecarregados, listaCandidatos;
    Empregado cta1, cta2;

    for( int dia = 0; dia < this->problema.getNumDias() - 1; dia++ )
    {
        listaSobrecarregados = this->controladores.getCTAsTurnosMais(MAX_TURNO);
        listaCandidatos = this->controladores.getCTAsTurnosMenos(MAX_TURNO - 2);

        while( ( listaSobrecarregados.size() > 0 ) && ( listaCandidatos.size() > 0 ) )
        {
            this->controladores.atualiza( this->escala );

            sobrecarregado = this->problema.buscaPenalidade(listaSobrecarregados, MAIOR_VALOR);
            candidato = this->problema.buscaPenalidade(listaCandidatos, MENOR_VALOR);

            if( (this->escalaNum[sobrecarregado][dia] == ALOCADO) && (this->escalaNum[candidato][dia] == DISPONIVEL) )
            {
                cta1.inicializa(sobrecarregado, dia, this->escala[sobrecarregado][dia], this->escalaNum[sobrecarregado][dia]);
                cta2.inicializa(candidato, dia, this->escala[candidato][dia], this->escalaNum[candidato][dia]);
                this->troca(cta1, cta2);
                break;
            }
            else if( this->escalaNum[sobrecarregado][dia] != ALOCADO )
                this->remove( listaSobrecarregados, sobrecarregado );
            else if( this->escalaNum[candidato][dia] != DISPONIVEL )
                this->remove( listaCandidatos, candidato );
        }
    }
}

void BuscaLocalRepetida::troca(Empregado &_cta1, Empregado &_cta2)
{
    char celula;
    int celulaNum;
    Empregado temp;

    //troca na escala
    celula = this->escala[_cta1.id][_cta1.dia];
    this->escala[_cta1.id][_cta1.dia] = this->escala[_cta2.id][_cta2.dia];
    this->escala[_cta2.id][_cta2.dia] = celula;

    celulaNum = this->escalaNum[_cta1.id][_cta1.dia];
    this->escalaNum[_cta1.id][_cta1.dia] = this->escalaNum[_cta2.id][_cta2.dia];
    this->escalaNum[_cta2.id][_cta2.dia] = celulaNum;

    //troca na estrutura
    temp = _cta1;
    _cta1 = _cta2;
    _cta2 = temp;
}

//------------------------------------------------------------------------------

bool BuscaLocalRepetida::remove(vector<int> &_lista, int _numero)
{
    for(unsigned int i = 0; i < _lista.size(); i++)
    {
        if(_lista[i] == _numero)
        {
            _lista.erase( _lista.begin() + i );
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

bool BuscaLocalRepetida::trocaPreferencia(char _turno)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->problema.getNaoDisponiveis(dia, _turno);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if( this->escala[ listaPenalisados[i] ][dia] == _turno )
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->problema.getDisponiveis(dia, _turno);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    if(this->escala[ listaCandidatos[j] ][dia] != _turno)
                    {
                        cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                        solucaoCorrente = this->getPenalidadeTotal();
                        this->troca(cta1, cta2);
                        solucaoFinal = this->getPenalidadeTotal();
                        //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                        if(solucaoFinal > solucaoCorrente)
                            this->troca(cta2, cta1);
                    }
                }
            }
        }
    }

    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}


bool BuscaLocalRepetida::trocaTurnos(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaTurnos(this->problema.getNumDias() - 1);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escalaNum[ listaPenalisados[i] ][dia] == ALOCADO)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }
    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}

bool BuscaLocalRepetida::trocaManhas(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaManhas(this->problema.getNumDias() - 1);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escala[ listaPenalisados[i] ][dia] == MANHA)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia, MANHA);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }
    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}

bool BuscaLocalRepetida::trocaTardes(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaTardes(this->problema.getNumDias() - 1);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escala[ listaPenalisados[i] ][dia] == TARDE)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia, TARDE);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }
    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}

bool BuscaLocalRepetida::trocaNoites()
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaNoites(this->problema.getNumDias() - 1);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escala[ listaPenalisados[i] ][dia] == NOITE)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia, NOITE);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }
    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}


vector<int> BuscaLocalRepetida::ultrapassaServicosCons(int _dia)
{
    int cont;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escalaNum.size(); i++)
    {
        cont = 0;
        for(int j = _dia, k = 0; j < (int)this->escalaNum[i].size(), k < (MAX_SERVICOS_CONS + 1); j++, k++)
            if( this->escalaNum[i][j] == ALOCADO )
                cont++;

        if( cont == (MAX_SERVICOS_CONS + 1) )
            lista.push_back(i);
    }

    return lista;
}

bool BuscaLocalRepetida::trocaServicosCons(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaServicosCons(dia);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escalaNum[ listaPenalisados[i] ][dia] == ALOCADO)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }

    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}

vector<int> BuscaLocalRepetida::ultrapassaFolgasCons(int _dia)
{
    int cont;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escalaNum.size(); i++)
    {
        cont = 0;
        for(int j = _dia, k = 0; j < (int)this->escalaNum[i].size(), k < (MAX_FOLGAS_CONS + 1); j++, k++)
            if( this->escalaNum[i][j] == DISPONIVEL )
                cont++;

        if( cont == (MAX_FOLGAS_CONS + 1) )
            lista.push_back(i);
    }

    return lista;
}

bool BuscaLocalRepetida::trocaFolgasCons(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaFolgasCons(dia);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escalaNum[ listaPenalisados[i] ][dia] == DISPONIVEL)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }

    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}

vector<int> BuscaLocalRepetida::ultrapassaNoitesCons(int _dia)
{
    int cont;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cont = 0;
        for(int j = _dia, k = 0; j < (int)this->escala[i].size(), k < (MAX_NOITE_CONS + 1); j++, k++)
            if( this->escala[i][j] == NOITE )
                cont++;

        if( cont == (MAX_NOITE_CONS + 1) )
            lista.push_back(i);
    }

    return lista;
}

bool BuscaLocalRepetida::trocaNoitesCons(void)
{
    int solucaoInicial, solucaoCorrente, solucaoFinal;
    Empregado cta1, cta2;
    vector<int> listaCandidatos, listaPenalisados;

    solucaoInicial = this->getPenalidadeTotal();
    solucaoCorrente = 0;
    solucaoFinal = 0;

    for(int dia = 0; dia < this->problema.getNumDias(); dia++)
    {
        //cout << dia + 1 << ", "; fflush(stdout);

        listaPenalisados = this->ultrapassaNoitesCons(dia);
        for(unsigned int i = 0; i < listaPenalisados.size(); i++)
        {
            if(this->escala[ listaPenalisados[i] ][dia] == NOITE)
            {
                cta1.inicializa( listaPenalisados[i], dia, this->escala[ listaPenalisados[i] ][dia], this->escalaNum[ listaPenalisados[i] ][dia] );

                listaCandidatos = this->getDisponiveis(dia);
                for(unsigned int j = 0; j < listaCandidatos.size(); j++)
                {
                    cta2.inicializa( listaCandidatos[j], dia, this->escala[ listaCandidatos[j] ][dia], this->escalaNum[ listaCandidatos[j] ][dia] );

                    solucaoCorrente = this->getPenalidadeTotal();
                    this->troca(cta1, cta2);
                    solucaoFinal = this->getPenalidadeTotal();
                    //cout << solucaoCorrente << " : " << solucaoFinal << endl;

                    if(solucaoFinal > solucaoCorrente)
                        this->troca(cta2, cta1);
                }
            }
        }
    }

    if(solucaoFinal < solucaoInicial)
        return true;
    return false;
}
