/*
 * File:   construtivo.cpp
 * Author: Rafael Vareto
 *
 * Created on 29 de Outubro de 2015, 13:21
 */

#include "construtivo.h"

//PUBLIC
Construtivo::Construtivo(void)
{
}

Construtivo::Construtivo(int _nDias, int _numCTAs)
{
    this->inicializa(_nDias, _numCTAs);
}

Construtivo::Construtivo(Instancia _problema, CTAs _controladores)
{
    this->inicializa(_problema, _controladores);
}

Construtivo::Construtivo(Construtivo &_c)
{
    this->problema = _c.problema;
    this->controladores = _c.controladores;
    this->cobertura = _c.cobertura;

    this->escala = _c.escala;
    this->escalaNum = _c.escalaNum;

    this->resultado = _c.resultado;
}

Construtivo Construtivo::operator =(Construtivo &_c)
{
    this->problema = _c.problema;
    this->controladores = _c.controladores;
    this->cobertura = _c.cobertura;

    this->escala = _c.escala;
    this->escalaNum = _c.escalaNum;
    
    this->resultado = _c.resultado;

    return (*this);
}

//------------------------------------------------------------------------------

bool Construtivo::inicializa(int _nDias, int _nCTAs)
{
    if( (_nDias > 0) && (_nCTAs > 0) )
    {
        this->aloca(_nDias, _nCTAs);

        for( unsigned int i = 0; i < this->escala.size(); i++ )
        {
            for( unsigned int j = 0; j < this->escala[i].size(); j++ )
            {
                this->escala[i][j] = VAZIO;
                this->escalaNum[i][j] = DISPONIVEL;
            }
        }
        return true;
    }
    return false;
}

bool Construtivo::inicializa(Instancia _problema, CTAs _controladores)
{
    this->problema = _problema;
    this->controladores = _controladores;

    if( (this->problema.getNumDias() > 0) && (this->problema.getNumCTAs() > 0) )
    {
        this->aloca(this->problema.getNumDias(), this->problema.getNumCTAs());
        this->cobertura.inicializa(this->problema.getNumDias(), this->problema.getNumCTAm(), this->problema.getNumCTAt(), this->problema.getNumCTAn());

        for( unsigned int i = 0; i < this->escala.size(); i++ )
        {
            for( unsigned int j = 0; j < this->escala[i].size(); j++ )
            {
                this->escala[i][j] = VAZIO;
                this->escalaNum[i][j] = DISPONIVEL;
            }
        }
        return true;
    }
    return false;
}

bool Construtivo::aloca(int _nDias, int _nCTAs)
{
    if( (_nDias > 0) && (_nCTAs > 0) )
    {
        this->escala.resize(_nCTAs);
        this->escalaNum.resize(_nCTAs);

        for( unsigned int i = 0; i < this->escala.size(); i++ )
        {
            this->escala[i].resize(_nDias);
            this->escalaNum[i].resize(_nDias);
        }
        return true;
    }
    return false;
}

bool Construtivo::nilTodos(void)
{
    if( this->escala.size() > 0 )
    {
        for( unsigned int i = 0; i < this->escala.size(); i++ )
        {
            for( unsigned int j = 0; j < this->escala[i].size(); j++ )
            {
                this->escala[i][j] = VAZIO;
                this->escalaNum[i][j] = DISPONIVEL;
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

Instancia Construtivo::getProblema(void)
{
    return this->problema;
}

CTAs Construtivo::getConstroladores(void)
{
    return this->controladores;
}

Demanda Construtivo::getCobertura(void)
{
    return this->cobertura;
}

vector< vector<char> > Construtivo::getEscala(void)
{
    return this->escala;
}

vector< vector<int> > Construtivo::getEscalaNum(void)
{
    return this->escalaNum;
}

Solucao Construtivo::getResultado()
{
    return this->resultado;
}

//------------------------------------------------------------------------------

void Construtivo::setProblema(Instancia &_i)
{
    this->problema = _i;
}

void Construtivo::setConstroladores(CTAs &_c)
{
    this->controladores = _c;
}

void Construtivo::setCobertura(Demanda &_d)
{
    this->cobertura = _d;
}

void Construtivo::setEscala(vector< vector<char> > &_e)
{
    this->escala = _e;
}

void Construtivo::setEscalaNum(vector< vector<int> > &_e)
{
    this->escalaNum = _e;
}

//------------------------------------------------------------------------------

int Construtivo::getNumCTAsManhas(int _dia)
{
    int cont = 0;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
        for(unsigned int i = 0; i < this->escala.size(); i++)
            if(this->escala[i][_dia] == MANHA)
                cont++;
    return cont;
}

int Construtivo::getNumCTAsTardes(int _dia)
{
    int cont = 0;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
        for(unsigned int i = 0; i < this->escala.size(); i++)
            if(this->escala[i][_dia] == TARDE)
                cont++;
    return cont;
}

int Construtivo::getNumCTAsNoites(int _dia)
{
    int cont = 0;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
        for(unsigned int i = 0; i < this->escala.size(); i++)
            if(this->escala[i][_dia] == NOITE)
                cont++;
    return cont;
}

int Construtivo::getNumCTAsTurnos(int _dia)
{
    int cont = 0;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
        for(unsigned int i = 0; i < this->escalaNum.size(); i++)
            if(this->escalaNum[i][_dia] == ALOCADO)
                cont++;
    return cont;
}

int Construtivo::getNumCTAsFolgas(int _dia)
{
    int cont = 0;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
        for(unsigned int i = 0; i < this->escalaNum.size(); i++)
            if(this->escalaNum[i][_dia] == DISPONIVEL)
                cont++;
    return cont;
}

//------------------------------------------------------------------------------

vector<char> Construtivo::escalaCTA(int _id)
{
    vector<char> escala;

    if( (_id > 0) && (_id < (int)this->escala.size()) )
        escala = this->escala[_id];
    return escala;
}

vector<int> Construtivo::escalaNumCTA(int _id)
{
    vector<int> escala;

    if( (_id > 0) && (_id < (int)this->escalaNum.size()) )
        escala = this->escalaNum[_id];
    return escala;
}

vector<char> Construtivo::escalaDia(int _dia)
{
    vector<char> escala( this->problema.getNumCTAs() );

    if( (_dia >= 0) && (_dia < this->problema.getNumDias()) )
        for(unsigned int i = 0; i < this->escala.size(); i++)
            escala[i] = this->escala[i][_dia];

    return escala;
}

vector<int> Construtivo::escalaNumDia(int _dia)
{
    vector<int> escala( this->problema.getNumCTAs() );

    if( (_dia >= 0) && (_dia < this->problema.getNumDias()) )
        for(unsigned int i = 0; i < this->escalaNum.size(); i++)
            escala[i] = this->escalaNum[i][_dia];

    return escala;
}

//------------------------------------------------------------------------------

vector<int> Construtivo::getNaoDisponiveis(int _dia)
{
    vector<int> lista;

    for( unsigned int i = 0; i < this->escalaNum.size(); i++ )
        if( this->escalaNum[i][_dia] == ALOCADO )
            lista.push_back(i);
    return lista;
}

vector<int> Construtivo::getDisponiveis(int _dia)
{
    vector<int> lista;

    for( unsigned int i = 0; i < this->escalaNum.size(); i++ )
        if( this->escalaNum[i][_dia] == DISPONIVEL )
            lista.push_back(i);
    return lista;
}

vector<int> Construtivo::getNaoDisponiveis(int _dia, char _turno)
{
    vector<int> lista;

    for( unsigned int i = 0; i < this->escalaNum.size(); i++ )
        if( ( this->escalaNum[i][_dia] == ALOCADO ) && ( this->escala[i][_dia] == _turno ) )
            lista.push_back(i);
    return lista;
}

vector<int> Construtivo::getDisponiveis(int _dia, char _turno)
{
    vector<int> lista;

    for( unsigned int i = 0; i < this->escala.size(); i++ )
        if( this->escala[i][_dia] != _turno )
            lista.push_back(i);
    return lista;
}

//------------------------------------------------------------------------------

bool Construtivo::simula(int _id, int _dia)
{
    if( (_id >= 0) && (_id < (int)this->escala.size()) )
        if( (_dia >= 0) && (_dia < (int)this->escala[_id].size()) )
            if( this->escalaNum[_id][_dia] == DISPONIVEL )
                return true;
    return false;
}

bool Construtivo::atribui(int _id, int _dia, char _turno)
{
    if( (_id >= 0) && (_id < (int)this->escala.size()) )
    {
        if( (_dia >= 0) && (_dia < (int)this->escala[_id].size()) )
        {
            if( this->escalaNum[_id][_dia] == DISPONIVEL )
            {
                this->escala[_id][_dia] = _turno;
                this->escalaNum[_id][_dia] = ALOCADO;
                return true;
            }
        }
    }
    return false;
}

bool Construtivo::entitulaSemPenalidade(vector<int> &_lista, int _dia, char _turno)
{
    bool cond1, cond2;
    int id;

    id = this->problema.buscaPenalidade(_lista, MAIOR_VALOR);

    cond1 = this->simula(id, _dia);
    cond2 = this->controladores.simula(id, _turno);

    if( (cond1 == true) && (cond2 == true) )
    {
        //cout << ", Atribuido ao CTA " << id;
        this->atribui(id, _dia, _turno);
        this->controladores.atribui(id, _turno);
        this->cobertura.decrementa(_dia, _turno);
        return true;
    }
    return false;
}

bool Construtivo::entitulaComPenalidade(vector<int> &_lista, int _dia, char _turno)
{
    int id;

    id = this->problema.buscaPenalidade(_lista, MENOR_VALOR);

    //cout << ", Atribuido ao CTA " << id;
    this->atribui(id, _dia, _turno);
    this->controladores.atribui(id, _turno);
    this->cobertura.decrementa(_dia, _turno);
    return true;
}

//------------------------------------------------------------------------------

void Construtivo::executa(void)
{
    bool cond;
    int dia, diaAnterior;
    char turno;
    vector<int> listaPreferencia, listaDisponiveis, listaPenalizados;

    dia = 0;
    diaAnterior = 0;

    while( this->cobertura.diaIncompleto() != -1 )
    {
        dia = this->cobertura.diaIncompleto();
        turno = this->cobertura.turnoIncompleto(dia);
        listaDisponiveis = valoresComuns( this->problema.getDisponiveis(dia, turno), this->controladores.getDisponiveis(turno), this->getDisponiveis(dia) );

        if( dia > 0 )
        {
            listaPreferencia = valoresComuns( listaDisponiveis, this->getDisponiveis(dia - 1) );

            if( dia != diaAnterior ) //se for um novo dia, atualiza as folgas do dia anterior
                this->atualizaFolgas(diaAnterior);
        }

        if( listaPreferencia.size() > 0 ) //se for possivel alocar SEM VIOLAR e dar PREFERENCIA a certos CTAs
            this->entitulaSemPenalidade(listaPreferencia, dia, turno);
        else if( listaDisponiveis.size() > 0 ) //se for possivel alocar SEM VIOLAR restricoes
            this->entitulaSemPenalidade(listaDisponiveis, dia, turno);
        else //se for possivel alocar somente VIOLANDO restricoes
        {
            cond = this->entitulaSemPenalidade(listaPenalizados, dia, turno);
            if(cond == false)
            {
                listaPenalizados = valoresComuns(this->problema.getTodos(), this->getDisponiveis(dia));
                this->entitulaComPenalidade(listaPenalizados, dia, turno);
            }
        }
        diaAnterior = dia;
    }
    this->atualizaFolgas(dia);

    this->resultado.penalidade = this->getPenalidadeTotal();
    this->resultado.escala = this->escala;
    this->resultado.escalaNum = this->escalaNum;
}

//------------------------------------------------------------------------------

vector<int> Construtivo::getPenalisados(int _dia)
{
    bool cond;
    set<int> conjunto;
    vector<int> lista;

    if( (_dia >= 0) && (_dia < this->problema.getNumDias() ) )
    {
        if( this->minDemanda() )
        {
            for(unsigned int i = 0; i < this->escala.size(); i++)
            {
                cond = this->problema.getDisponiveis(i, _dia, this->escala[i][_dia]);
                if(cond == false)
                    conjunto.insert(i);

                cond = this->ultrapassaTurnos(i, _dia);
                if( (cond == false) && (this->escalaNum[i][_dia] == ALOCADO) )
                    conjunto.insert(i);

                cond = this->ultrapassaManhas(i, _dia);
                if( (cond == false) && (this->escala[i][_dia] == MANHA) )
                    conjunto.insert(i);

                cond = this->ultrapassaTardes(i, _dia);
                if( (cond == false) && (this->escala[i][_dia] == TARDE) )
                    conjunto.insert(i);

                cond = this->ultrapassaNoites(i, _dia);
                if( (cond == false) && (this->escala[i][_dia] == NOITE) )
                    conjunto.insert(i);

                cond = this->ultrapassaServicosCons(i, _dia);
                if(cond == false)
                    conjunto.insert(i);

                cond = this->ultrapassaNoitesCons(i, _dia);
                if(cond == false)
                    conjunto.insert(i);

                cond = this->ultrapassaFolgasCons(i, _dia);
                if(cond == false)
                    conjunto.insert(i);
                
                if (_dia > 0) {
                    cond = this->minimoDescanso(i, _dia);
                    if(cond == false)
                        conjunto.insert(i);
                }
            }

            for(set<int>::iterator it = conjunto.begin(); it != conjunto.end(); it++)
                lista.push_back(*it);
        }
        else
        {
            cout << endl << "ERRO: Construtivo Invalida::Demanda nao satisfeita";
            exit(1);
        }
    }
    return lista;
}

vector<string> Construtivo::getPenalidades(void)
{
    bool cond;
    string violacao;
    vector<string> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        for(unsigned int j = 0; j < this->escala[i].size(); j++)
        {
            if(this->escalaNum[i][j] == ALOCADO)
            {
                cond = this->problema.getDisponiveis(i, j, this->escala[i][j]);
                if(cond == false)
                {
                    stringstream tempI, tempJ;
                    tempI << i;
                    tempJ << (j + 1);

                    violacao.clear();
                    violacao = "CTA ";
                    violacao += tempI.str();
                    violacao += " NAO pode trabalhar no dia ";
                    violacao += tempJ.str();
                    violacao += " no turno ";
                    violacao += this->escala[i][j];
                    lista.push_back(violacao);
                }
            }

            cond = this->ultrapassaTurnos(i, j);
            if( (cond == false) && (this->escalaNum[i][j] == ALOCADO) )
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite TOTAL de turnos";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaManhas(i, j);
            if( (cond == false) && (this->escala[i][j] == MANHA) )
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de turnos na MANHA";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaTardes(i, j);
            if( (cond == false) && (this->escala[i][j] == TARDE) )
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de turnos na TARDE";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaNoites(i, j);
            if( (cond == false) && (this->escala[i][j] == NOITE) )
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de turnos na NOITE";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaServicosCons(i, j);
            if(cond == false)
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de TURNOS CONSECUTIVOS";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaNoitesCons(i, j);
            if(cond == false)
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de TURNOS CONSECUTIVOS a NOITE";
                lista.push_back(violacao);
            }

            cond = this->ultrapassaFolgasCons(i, j);
            if(cond == false)
            {
                stringstream temp;
                temp.clear();
                temp << i;

                violacao.clear();
                violacao = "CTA ";
                violacao += temp.str();
                violacao += " ultrapassou o limite de FOLGAS CONSECUTIVAS";
                lista.push_back(violacao);
            }
            
            if (j > 0) {
                cond = this->minimoDescanso(i, j);
                if(cond == false)
                {
                    stringstream tempI, tempJ;
                    tempI.clear();
                    tempJ.clear();
                    tempI << i;
                    tempJ << (j + 1);
                    
                    violacao.clear();
                    violacao = "CTA ";
                    violacao += tempI.str();
                    violacao += " nao descansou o suficiente no dia ";
                    violacao += tempJ.str();
                    lista.push_back(violacao);
                }
            }
        }
    }
    return lista;
}

int Construtivo::getPenalidadeTotal(void)
{
    bool cond;
    int total = 0;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        for(unsigned int j = 0; j < this->escala[i].size(); j++)
        {
            if(this->escalaNum[i][j] == ALOCADO)
            {
                cond = this->problema.getDisponiveis(i, j, this->escala[i][j]);
                if(cond == false)
                    total += this->problema.getPenCTA(i);
            }

            cond = this->ultrapassaTurnos(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaManhas(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaTardes(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaNoites(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaServicosCons(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaNoitesCons(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);

            cond = this->ultrapassaFolgasCons(i, j);
            if(cond == false)
                total += this->problema.getPenCTA(i);
            
            if (j > 0) {
                cond = this->minimoDescanso(i, j);
                if(cond == false)
                    total += this->problema.getPenCTA(i);
            }
        }
    }

    return total;
}

//------------------------------------------------------------------------------

void Construtivo::imprimeEscala(void)
{
    //imprime tabela
    printf("     ");
    for( int i = 0; i < this->problema.getNumDias(); i++ )
        printf("%3d", i + 1);
    cout << endl;
    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        printf("%3d  ", i);
        for( unsigned int j = 0; j < this->escala[i].size(); j++ )
        printf("%3c", this->escala[i][j]);
        printf("  %3d  |  ", i);
        printf("T:%2d m:%2d t:%2d n:%2d", this->controladores.getNumTurnos(i), this->controladores.getNumManhas(i), this->controladores.getNumTardes(i), this->controladores.getNumNoites(i));
        cout << endl;
    }
    cout << "Penalidade: " << this->getPenalidadeTotal() << endl;
}

void Construtivo::imprimeEscalaNum(void)
{
    //imprime tabela
    printf("     ");
    for( int i = 0; i < this->problema.getNumDias(); i++ )
        printf("%3d", i + 1);
    cout << endl;
    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        printf("%3d  ", i);
        for( unsigned int j = 0; j < this->escala[i].size(); j++ )
        printf("%3d", this->escalaNum[i][j]);
        printf("  %3d  |  ", i);
        printf("T:%2d m:%2d t:%2d n:%2d", this->controladores.getNumTurnos(i), this->controladores.getNumManhas(i), this->controladores.getNumTardes(i), this->controladores.getNumNoites(i));
        cout << endl;
    }
    cout << "Penalidade: " << this->getPenalidadeTotal() << endl;
}

void Construtivo::imprimePenalidades(void)
{
    vector<string> listaPenalidades;
    listaPenalidades = this->getPenalidades();

    cout << endl << "Numero de Violacoes: " << listaPenalidades.size();
    for(unsigned int i = 0; i < listaPenalidades.size(); i++)
        cout << endl << listaPenalidades[i];

    cout << endl << this->getPenalidadeTotal() << endl;
}

//------------------------------------------------------------------------------

//PROTECTED
void Construtivo::recuperaMelhorResultado()
{
    this->escala.clear();
    this->escalaNum.clear();

    this->escala = this->resultado.escala;
    this->escalaNum = this->resultado.escalaNum;
    this->controladores.atualiza(this->escala);
}

void Construtivo::atualizaFolgas(int _dia)
{
    for( unsigned int i = 0; i < this->escalaNum.size(); i++ )
        if( this->escalaNum[i][_dia] == DISPONIVEL )
            this->controladores.atribui(i, FOLGA);
}

bool Construtivo::minDemanda(void)
{
    bool cond;

    for( int i = 0; i < this->problema.getNumDias(); i++ )
    {
        cond = this->minDemanda(i);
        if( cond == false )
            return false;
    }
    return true;
}

inline bool Construtivo::minDemanda(int _dia)
{
    int contM, contT, contN;

    contM = 0;
    contT = 0;
    contN = 0;

    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        if( this->escala[i][_dia] == MANHA )
            contM++;
        else if( this->escala[i][_dia] == TARDE )
            contT++;
        else if( this->escala[i][_dia] == NOITE )
            contN++;
    }

    if( (contM >= MIN_MANHA) && (contT >= MIN_TARDE) && (contN >= MIN_NOITE) )
        return true;
    return false;
}


vector<int> Construtivo::violaPreferencia(int _dia, char _turno)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->problema.getDisponiveis(i, _dia, _turno);
        if(cond == false)
            lista.push_back(i);
    }

    return lista;
}

bool Construtivo::ultrapassaTurnos(void)
{
    bool cond;
    int dia;

    if( this->escalaNum.size() > 0 )
    {
        if( this->escalaNum[0].size() > 0 )
        {
            dia = (int) this->escalaNum[0].size() - 1;

            for( unsigned int i = 0; i < this->escalaNum.size(); i++ )
            {
                cond = this->ultrapassaTurnos(i, dia);
                if( cond == false )
                    return false;
            }
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaTurnos(int _id, int _dia)
{
    int cont = 0;

    for( int i = _dia; i >= 0; i-- )
        if( this->escalaNum[_id][i] == ALOCADO )
            cont++;

    if( cont <= MAX_TURNO )
        return true;
    return false;
}

vector<int> Construtivo::ultrapassaTurnos(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaTurnos(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaManhas(void)
{
    bool cond;
    int dia;

    if( this->escala.size() > 0 )
    {
        if( this->escala[0].size() > 0 )
        {
            dia = (int) this->escala[0].size() - 1;

            for( unsigned int i = 0; i < this->escala.size(); i++ )
            {
                cond = this->ultrapassaManhas(i, dia);
                if( cond == false )
                    return false;
            }
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaManhas(int _id, int _dia)
{
    int cont = 0;

    for( int i = _dia; i >= 0; i-- )
        if( this->escala[_id][i] == MANHA )
            cont++;

    if( cont <= MAX_MANHA )
        return true;
    return false;
}

vector<int> Construtivo::ultrapassaManhas(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaManhas(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaTardes(void)
{
    bool cond;
    int dia;

    if( this->escala.size() > 0 )
    {
        if( this->escala[0].size() > 0 )
        {
            dia = (int) this->escala[0].size() - 1;

            for( unsigned int i = 0; i < this->escala.size(); i++ )
            {
                cond = this->ultrapassaTardes(i, dia);
                if( cond == false )
                    return false;
            }
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaTardes(int _id, int _dia)
{
    int cont = 0;

    for( int i = _dia; i >= 0; i-- )
        if( this->escala[_id][i] == TARDE )
            cont++;

    if( cont <= MAX_TARDE )
        return true;
    return false;
}

vector<int> Construtivo::ultrapassaTardes(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaTardes(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaNoites(void)
{
    bool cond;
    int dia;

    if( this->escala.size() > 0 )
    {
        if( this->escala[0].size() > 0 )
        {
            dia = (int) this->escala[0].size() - 1;

            for( unsigned int i = 0; i < this->escala.size(); i++ )
            {
                cond = this->ultrapassaNoites(i, dia);
                if( cond == false )
                    return false;
            }
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaNoites(int _id, int _dia)
{
    int cont = 0;

    for( int i = _dia; i >= 0; i-- )
        if( this->escala[_id][i] == NOITE )
            cont++;

    if( cont <= MAX_NOITE )
        return true;
    return false;
}

vector<int> Construtivo::ultrapassaNoites(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaNoites(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaNoitesCons(void)
{
    bool cond;

    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        for( unsigned int j = 0; j < this->escala[i].size(); j++ )
        {
            cond = this->ultrapassaNoitesCons(i, j);
            if( cond == false )
                return false;
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaNoitesCons(int _id, int _dia)
{
    if(this->escala[_id][_dia] == NOITE)
    {
        int cont = 0;

        for( int i = _dia, seq = MAX_NOITE_CONS + 1; i >= 0, seq > 0; i--, seq-- )
            if( this->escala[_id][i] == NOITE )
                cont++;

        if( cont <= MAX_NOITE_CONS )
            return true;
        return false;
    }

    return true;
}

vector<int> Construtivo::ultrapassaNoitesCons(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaNoitesCons(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaServicosCons(void)
{
    bool cond;

    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        for( unsigned int j = 0; j < this->escala[i].size(); j++ )
        {
            cond = this->ultrapassaServicosCons(i, j);
            if( cond == false )
                return false;
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaServicosCons(int _id, int _dia)
{
    if(this->escalaNum[_id][_dia] == ALOCADO)
    {
        int cont = 0;

        for( int i = _dia, seq = MAX_SERVICOS_CONS + 1; i >= 0, seq > 0; i--, seq-- )
            if( this->escalaNum[_id][i] == ALOCADO )
                cont++;

        if( cont <= MAX_SERVICOS_CONS )
            return true;
        return false;
    }
    return true;
}

vector<int> Construtivo::ultrapassaServicosCons(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaServicosCons(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}


bool Construtivo::ultrapassaFolgasCons(void)
{
    bool cond;

    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        for( unsigned int j = 0; j < this->escala[i].size(); j++ )
        {
            cond = this->ultrapassaFolgasCons(i, j);
            if( cond == false )
                return false;
        }
    }
    return true;
}

inline bool Construtivo::ultrapassaFolgasCons(int _id, int _dia)
{
    if(this->escalaNum[_id][_dia] == DISPONIVEL)
    {
        int cont = 0;

        for( int i = _dia, seq = MAX_FOLGAS_CONS + 1; i >= 0, seq > 0; i--, seq-- )
            if( this->escalaNum[_id][i] == DISPONIVEL )
                cont++;

        if( cont <= MAX_FOLGAS_CONS )
            return true;
        return false;
    }
    return true;
}

vector<int> Construtivo::ultrapassaFolgasCons(int _dia)
{
    bool cond;
    vector<int> lista;

    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->ultrapassaFolgasCons(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}

bool Construtivo::minimoDescanso(void) {
    bool cond;
    
    for( unsigned int i = 0; i < this->escala.size(); i++ )
    {
        for( unsigned int j = 1; j < this->escala[i].size(); j++ )
        {
            cond = this->minimoDescanso(i, j);
            if( cond == false )
                return false;
        }
    }
    return true;
}

inline bool Construtivo::minimoDescanso(int _id, int _dia) {
    if(this->escala[_id][_dia] == MANHA)
    {
        if( this->escala[_id][_dia - 1] == NOITE )
            return false;
    }
    return true;
}

vector<int> Construtivo::minimoDescanso(int _dia) {
    bool cond;
    vector<int> lista;
    
    for(unsigned int i = 0; i < this->escala.size(); i++)
    {
        cond = this->minimoDescanso(i, _dia);
        if(cond == false)
            lista.push_back(i);
    }
    return lista;
}
