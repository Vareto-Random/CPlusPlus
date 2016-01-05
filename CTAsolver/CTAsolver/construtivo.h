/* 
 * File:   construtivo.h
 * Author: Rafael Vareto
 *
 * Created on 29 de Outubro de 2015, 13:21
 */

#ifndef CONSTRUTIVO_H
#define	CONSTRUTIVO_H

#include "biblioteca.h"
#include "instancia.h"
#include "ctas.h"
#include "funcoes.h"
#include "demanda.h"
#include "empregado.h"
#include "solucao.h"

class Construtivo 
{
public:
    Construtivo(void);
    Construtivo(int, int); //construtor avancado
    Construtivo(Instancia, CTAs); //construtor avancado
    Construtivo(Construtivo &); //construtor de copia
    Construtivo operator =(Construtivo &);
    
    bool inicializa(int, int);
    bool inicializa(Instancia, CTAs);
    bool aloca(int, int);    
    bool nilTodos(void); //seta todos os dados da Construtivo com valores nulos
    
    Instancia getProblema(void); //retorna a instancia utilizada
    CTAs getConstroladores(void); //retorna o estado atual dos controladores
    Demanda getCobertura(void); //retorna a demanda atual da solucao
    vector< vector<char> > getEscala(void);  //retorna toda a grade/solucao corrente
    vector< vector<int> > getEscalaNum(void); //retorna toda a grade/solucao numerica corrente
    vector< vector<int> > getPenalidade(void); //retorna toda a grade de penalidade corrente
    Solucao getResultado(void); //retorna toda a solucao do problema
    
    void setProblema(Instancia &); //atribui a instancia utilizada
    void setConstroladores(CTAs &); //atribui o estado atual dos controladores
    void setCobertura(Demanda &); //atribui a demanda atual da solucao
    void setEscala(vector< vector<char> > &);  //atribui toda a grade/solucao corrente
    void setEscalaNum(vector< vector<int> > &); //atribui toda a grade/solucao numerica corrente
    void setPenalidade(vector< vector<int> > &); //atribui toda a grade de penalidade corrente
    
    int getNumCTAsManhas(int); //Retorna o numero de CTAs que trabalham na manha no dia D
    int getNumCTAsTardes(int); //Retorna o numero de CTAs que trabalham na tarde no dia D
    int getNumCTAsNoites(int); //Retorna o numero de CTAs que trabalham na noite no dia D
    int getNumCTAsTurnos(int); //Retorna o numero de CTAs que trabalham no dia D
    int getNumCTAsFolgas(int); //Retorna o numero de CTAs que folgam no dia D
    
    vector<char> escalaCTA(int); //retorna grade de um unico CTA C
    vector<int> escalaNumCTA(int); //retorna grade numerica de um unico CTA C
    vector<char> escalaDia(int); //retorna grade de um unico dia D
    vector<int> escalaNumDia(int); ////retorna grade numerica de um unico dia D
    
    vector<int> getNaoDisponiveis(int); //retorna lista de CTAs que trabalharam no dia D
    vector<int> getDisponiveis(int); //retorna lista de CTAs que folgaram no dia D
    vector<int> getNaoDisponiveis(int, char); //retorna lista de CTAs que trabalharam no dia D e no turno T
    vector<int> getDisponiveis(int, char); //retorna lista de CTAs que no dia D nao trabalharam no turno T
    
    inline bool simula(int, int); //simula uma atribuicao ao CTA C no dia D do turno T
    inline bool atribui(int, int, char); //atribui ao CTA C no dia D do turno T
    inline bool entitulaSemPenalidade(vector<int> &, int, char); //seleciona CTA de uma lista a atribui a um dia e um turno SEM violar restricoes
    inline bool entitulaComPenalidade(vector<int> &, int, char); //seleciona CTA de uma lista a atribui a um dia e um turno violando restricoes

    void executa(void); //método que gera uma solucao inicial para o problema, atraves de um algoritmo guloso
    
    vector<int> getPenalisados(int); //retorna id dos CTAs que sao penalizados no dia D
    vector<string> getPenalidades(void); //armazena as penalidade de todos os CTAs    
    int getPenalidadeTotal(void); //calcula a penalidade total
 
    void imprimeEscala(void);
    void imprimeEscalaNum(void);
    void imprimePenalidades(void);
    
protected:
    void recuperaMelhorResultado(); //recupera a melhor solucao encontrada
    
    void atualizaFolgas(int); //atualiza as folgas do dia D
    
    bool minDemanda(void); //verifica se a demanda de todos os dias está sendo respeitada
    bool minDemanda(int); //verifica se a demana de um dia D está sendo respeitadai
    
    vector<int> violaPreferencia(int, char); //retorna a lista de CTAs que violam restricoes se trabalharem mo turno T a partir do dia D
    
    bool ultrapassaTurnos(void); //verifica se todos os CTAs trabalham no máximo 20 turnos no mes
    bool ultrapassaTurnos(int, int); //verifica se um CTA C trabalha no máximo 20 turnos no mes a partir de um dia D
    vector<int> ultrapassaTurnos(int); //retorna lista de CTAs que estoura o limite de turnos permitidos a partir de um dia D
    
    bool ultrapassaManhas(void); //verifica se todos os CTAs trabalham no máximo 10 manhas no mes
    bool ultrapassaManhas(int, int); //verifica se um CTA C trabalha no máximo 10 manhas no mes a partir de um dia D
    vector<int> ultrapassaManhas(int); //retorna lista de CTAs que estoura o limite de Manhas permitidas a partir de um dia D
    
    bool ultrapassaTardes(void); //verifica se todos os CTAs trabalham no máximo 10 tardes no mes
    bool ultrapassaTardes(int, int); //verifica se um CTA C trabalha no máximo 10 tardes no mes a partir de um dia D
    vector<int> ultrapassaTardes(int); //retorna lista de CTAs que estoura o limite de Tardes permitidas a partir de um dia D
    
    bool ultrapassaNoites(void); //verifica se todos os CTAs trabalham no máximo 10 noites no mes
    bool ultrapassaNoites(int, int); //verifica se um CTA C trabalha no máximo 10 noites no mes a partir de um dia D
    vector<int> ultrapassaNoites(int); //retorna lista de CTAs que estoura o limite de Noites permitidas a partir de um dia D
    
    bool ultrapassaServicosCons(void); //verifica se todos os CTAs trabalham no máximo 6 dias consecutivos no mes
    bool ultrapassaServicosCons(int, int); //verifica se um CTA C trabalha no máximo 6 dias consecutivos a partir de um dia D
    vector<int> ultrapassaServicosCons(int); //retorna a lista de CTAs que trabalham mais 6 dias consecutivos a partir de um dia D
    
    bool ultrapassaNoitesCons(void); //verifica se todos os CTAs trabalham no máximo 3 noites consecutivas no mes
    bool ultrapassaNoitesCons(int, int); //verifica se um CTA C trabalha no máximo 3 noites consecutivas a partir de um dia D
    vector<int> ultrapassaNoitesCons(int); //retorna a lista de CTAs que trabalham mais 3 dias consecutivos a noite a partir de um dia D
    
    bool ultrapassaFolgasCons(void); //verifica se todos os CTAs folgam no máximo 6 dias consecutivos no mes
    bool ultrapassaFolgasCons(int, int); //verifica se um CTA C folga no máximo 6 dias consecutivos a partir de um dia D
    vector<int> ultrapassaFolgasCons(int); //retorna a lista de CTAs que folgam mais 6 dias consecutivos a partir de um dia D
    
    bool minimoDescanso(void);
    bool minimoDescanso(int,int);
    vector<int> minimoDescanso(int);

    
    Instancia problema;
    CTAs controladores;
    Demanda cobertura;
    
    vector< vector<char> > escala;
    vector< vector<int> > escalaNum;
    //vector< vector<int> > penalidade;
    
    Solucao resultado;
};

#endif	/* CONSTRUTIVO_H */