/* 
 * File:   instancia.h
 * Author: Rafael Vareto
 *
 * Created on 6 de Outubro de 2015, 12:27
 */

#ifndef INSTANCIA_H
#define	INSTANCIA_H

#include "biblioteca.h"
#include "restricao.h"

class Instancia {
public:
    Instancia(void); //Construtor padrão
    Instancia(int, int, int, int, int); //Construtor avancado
    Instancia(const Instancia &); //Construtor de copia
    Instancia operator =(const Instancia &);

    bool atualiza(int, int, int, int, int); //define Instancia com valores pré-definidos
    void setNumDias(int); //define numero de dias
    void setNumCTAs(int); //define numero de controladores de tráfego aéreo
    void setNumCTAm(int); //define demanda durante a manhã
    void setNumCTAt(int); //define demanda durante a tarde
    void setNumCTAn(int); //define demanda durante a noite
    void setPenCTA(int, int); //define penalidade para um CTA
    bool setCTA(int, int, char); //define o turno de um dia de um CTA que deve ser evitado

    int getNumDias(void); //retorna numero de dias
    int getNumCTAs(void); //retorna numero de controladores de tráfego aéreo
    int getNumCTAm(void); //retorna demanda durante a manhã
    int getNumCTAt(void); //retorna demanda durante a tarde
    int getNumCTAn(void); //retorna demanda durante a noite
    int getPenCTA(int); //retorna penalidade de um CTA
    Restricao getCTA(int); //retorna os turnos dos dias de um CTA que devem ser evitados
    void printCTA(int);

    vector<int> getTodos(void); //retorna id de todos os CTAs
    bool getDisponiveis(int, int, char); //verifica se um CTA C pode trabalhar em um dia D no turno T
    bool getNaoDisponiveis(int, int, char); //verifica se um CTA C prefere NAO trabalhar em um dia D no turno T
    
    vector<int> getDisponiveis(int, char); //retorna id dos CTAs que preferem trabalhar no dia D e no turno T
    vector<int> getNaoDisponiveis(int, char); //retorna id dos CTAs que preferem NAO trabalhar no dia D e no turno T
    
    int buscaPenalidade(vector<int> &, int = MAIOR_VALOR); //retorna o id do CTA C que possui maior penalidade caso haja uma violacao
    vector<int> buscaPenalidades(vector<int> &); //retorna a lista de penalidades dos CTAs (em mesma ordem) 

    bool leitura(string);

private:
    int numDias; //numero total de dias
    int numCTAs; //numero total de controladores de vôo
    int numCTAm; //demanda de CTAs no período da manhã
    int numCTAt; //demanda de CTAs no período da tarde
    int numCTAn; //demanda de CTAs no período da noite

    vector<Restricao> vCTAs;
};

#endif	/* INSTANCIA_H */