/* 
 * File:   controlador.h
 * Author: Rafael Vareto
 *
 * Created on 21 de Outubro de 2015, 14:31
 */

#ifndef CTAS_H
#define	CTAS_H

#include "biblioteca.h"

class CTA 
{
public:
    CTA operator =(const CTA &);
    
    int numManhas;
    int numTardes;
    int numNoites;
    int numFolgas;
    int numNoitesCons;
    int numServicosCons;
    int numFolgasCons;
    int numTurnos;
};


class CTAs
{
public:
    CTAs(void); //construtor padrao
    CTAs(int); //construtor avancado
    CTAs(const CTAs &); //construtor de copia
    CTAs operator =(const CTAs &);
    
    bool inicializa(int); //aloca uma estrutura de dados para cada CTA e zera todos eles
    bool aloca(int); //aloca uma estrutura de dados para cada CTA
    bool nilTodos(void); //seta todos os dados dos CTAs com valores nulos
    bool nilTodos(int); //seta todos os dados de um CTA com valores nulos
    bool atualiza(vector< vector<char> > &); //atualiza dados dos CTAs com base na escala e escalaNum corrente
       
    vector<int> getDisponiveis(char); //retorna id dos CTAs que podem trabalhar no dia D e no turno T sem penalidades
    vector<int> getNaoDisponiveis(char); //retorna id dos CTAs que sao penalisados se trabalhar no dia D e no turno T
    //vector<int> rank(int, char); //retorna o Rank em ordem crescente das penalidades dos CTAs se trabalharem no dia D e no turno T

    bool incCTA(int, char); //Incrementa o numero de turnos T o CTA C trabalha
    bool decCTA(int, char); //Decrementa o numero de turnos T o CTA C trabalha    
    bool simula(int, char); //simula uma atribuicao de um turno T a um CTA C
    bool atribui(int, char); //atribui um turno T a um CTA C

    int getNumManhas(int); //Retorna o numero de numManhas do CTA C
    int getNumTardes(int); //Retorna o numero de numTardes do CTA C
    int getNumNoites(int); //Retorna o numero de numNoites do CTA C
    int getNumTurnos(int); //Retorna o numero de numTurnos do CTA C
    int getNumFolgas(int); //Retorna o numero de numFolgas do CTA C
    int getNumNoitesCons(int); //Retorna o numero de numNoitesCons do CTA C
    int getNumServicosCons(int); //Retorna o numero de numServicosCons do CTA C
    int getNumFolgasCons(int); //Retorna o numero de numFolgasCons do CTA C    
    
    bool setNumManhas(int, int); //atribui um valor qualquer ao numManhas do CTA C
    bool setNumTardes(int, int); //atribui um valor qualquer ao numTardes do CTA C
    bool setNumNoites(int, int); //atribui um valor qualquer ao numNoites do CTA C
    bool setNumTurnos(int, int); //atribui um valor qualquer ao numTurnos do CTA C
    bool setNumFolgas(int, int); //atribui um valor qualquer ao numFolgas do CTA C
    bool setNumNoitesCons(int, int); //atribui um valor qualquer ao numNoitesCons do CTA C
    bool setNumServicosCons(int, int); //atribui um valor qualquer ao numServicosCons do CTA C
    bool setNumFolgasCons(int, int); //atribui um valor qualquer ao numFolgasCons do CTA C
        
    bool nilNumManhas(int); //atribui o valor zero ao numManhas do CTA C
    bool nilNumTardes(int); //atribui o valor zero ao numTardes do CTA C
    bool nilNumNoites(int); //atribui o valor zero ao numNoites do CTA C
    bool nilNumTurnos(int); //atribui o valor zero ao numTurnos do CTA C
    bool nilNumFolgas(int); //atribui o valor zero ao numFolgas do CTA C
    bool nilNumNoitesCons(int); //atribui o valor zero ao numNoitesCons do CTA C
    bool nilNumServicosCons(int); //atribui o valor zero ao numServicosCons do CTA C
    bool nilNumFolgasCons(int); //atribui o valor zero ao numFolgasCons do CTA C
    
    vector<int> getCTAsManhasMais(int); //Retorna lista de CTAs que trabalham de Manha x ou mais vezes
    vector<int> getCTAsTardesMais(int); //Retorna lista de CTAs que trabalham de Tarde x ou mais vezes
    vector<int> getCTAsNoitesMais(int); //Retorna lista de CTAs que trabalham de Noite x ou mais vezes
    vector<int> getCTAsTurnosMais(int); //Retorna lista de CTAs que trabalham em x ou mais turnos
    vector<int> getCTAsFolgasMais(int); //Retorna lista de CTAs que folgam x ou mais vezes
    vector<int> getCTAsNoitesConsMais(int); //Retorna lista de CTAs que estao trabalhando a noite em sequencia x ou mais vezes
    vector<int> getCTAsServicosConsMais(int); //Retorna lista de CTAs que estao trabalhando em sequencia x ou mais vezes
    vector<int> getCTAsFolgasConsMais(int); //Retorna lista de CTAs que estao folgando em sequencia x ou mais vezes

    vector<int> getCTAsManhasMenos(int); //Retorna lista de CTAs que trabalham de Manha x ou menos vezes
    vector<int> getCTAsTardesMenos(int); //Retorna lista de CTAs que trabalham de Tarde x ou menos vezes
    vector<int> getCTAsNoitesMenos(int); //Retorna lista de CTAs que trabalham de Noite x ou menos vezes
    vector<int> getCTAsTurnosMenos(int); //Retorna lista de CTAs que trabalham em x ou menos turnos
    vector<int> getCTAsFolgasMenos(int); //Retorna lista de CTAs que folgam x ou menos vezes
    vector<int> getCTAsNoitesConsMenos(int); //Retorna lista de CTAs que estao trabalhando a noite em sequencia x ou menos vezes
    vector<int> getCTAsServicosConsMenos(int); //Retorna lista de CTAs que estao trabalhando em sequencia x ou menos vezes
    vector<int> getCTAsFolgasConsMenos(int); //Retorna lista de CTAs que estao folgando em sequencia x ou menos vezes    
    
    bool incNumManhas(int); //Incrementa o numero de numManhas do CTA C
    bool incNumTardes(int); //Incrementa o numero de numTardes do CTA C
    bool incNumNoites(int); //Incrementa o numero de numNoites do CTA C
    bool incNumFolgas(int); //Incrementa o numero de numNoites do CTA C
    bool incNumNoitesCons(int); //Incrementa o numero de numNoitesCons do CTA C
    bool incNumServicosCons(int); //Incrementa o numero de numServicosCons do CTA C
    bool incNumFolgasCons(int); //Incrementa o numero de numFolgasCons do CTA C
    bool incNumTurnos(int); //Incrementa o numero de numTurnos do CTA C
    
    bool decNumManhas(int); //Decrementa o numero de numManhas do CTA C
    bool decNumTardes(int); //Decrementa o numero de numTardes do CTA C
    bool decNumNoites(int); //Decrementa o numero de numNoites do CTA C
    bool decNumFolgas(int); //Decrementa o numero de numNoites do CTA C
    bool decNumNoitesCons(int); //Decrementa o numero de numNoitesCons do CTA C
    bool decNumServicosCons(int); //Decrementa o numero de numServicosCons do CTA C
    bool decNumFolgasCons(int); //Decrementa o numero de numFolgasCons do CTA C
    bool decNumTurnos(int); //Decrementa o numero de numTurnos do CTA C
    
    bool printCTA(int); //imprime os dados de um CTA C
    
private:    
    vector<CTA> controladores;
};

#endif	/* CTAS_H */