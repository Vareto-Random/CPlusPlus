/* 
 * File:   buscalocalrepetida.h
 * Author: Rafael Vareto
 *
 * Created on 29 de Novembro de 2015, 10:05
 */

#ifndef BuscaLocalRepetida_H
#define	BuscaLocalRepetida_H

#include "construtivo.h"

class BuscaLocalRepetida : public Construtivo
{
public:
    BuscaLocalRepetida(void);
    BuscaLocalRepetida(int, int); //construtor avancado
    BuscaLocalRepetida(Instancia, CTAs); //construtor avancado
    BuscaLocalRepetida(Construtivo &); //construtor de copia de classe base
    BuscaLocalRepetida(BuscaLocalRepetida &); //construtor de copia
    BuscaLocalRepetida operator =(Construtivo &);
    BuscaLocalRepetida operator =(BuscaLocalRepetida &);
    
    void executa(void); //método que aprimora a solucao, atraves de um algoritmo guloso  
       
protected:
    void buscaLocal(void); //tenta realizar trocas para melhorar a solucao corrente
    void diversificacao(void); //faz muitas alteracos, com tendencia a piorar significamente a solucao
    void intensificacao(void); //faz poucas alteracoes, aproximando ao máximo o MINIMO com o MAXIMO de turnos trabalhados entre os CTAs
    
    void troca(Empregado &, Empregado &); //faz a troca entre dois CTAs (estrutura e escala)
    bool remove(vector<int> &, int); //remove valor X de uma lista
    
    bool trocaPreferencia(char); //tenta fazer trocas que respeitem as preferencias dos CTAs
    
    bool trocaTurnos(void); //tenta fazer trocas entre CTAs alocados e CTAs nao alocados
    bool trocaManhas(void); //tenta fazer trocas entre CTAs alocados na manha com CTAs de outros turnos
    bool trocaTardes(void); //tenta fazer trocas entre CTAs alocados na tarde com CTAs de outros turnos
    bool trocaNoites(void); //tenta fazer trocas entre CTAs alocados na noite com CTAs de outros turnos
    
    vector<int> ultrapassaServicosCons(int); //retorna lista de CTAs que ultrapassa limite de servicos consecutivos
    bool trocaServicosCons(void); //tenta fazer trocas entre CTAs que ultrapassam limite de servisos consecutivos
    
    vector<int> ultrapassaFolgasCons(int); //retorna lista de CTAs que ultrapassa limite de folgas consecutivas
    bool trocaFolgasCons(void); //tenta fazer trocas entre CTAs que ultrapassam limite de folgas consecutivas
    
    vector<int> ultrapassaNoitesCons(int); //retorna lista de CTAs que ultrapassa limite de noites consecutivas
    bool trocaNoitesCons(void); //tenta fazer trocas entre CTAs que ultrapassam limite de noites consecutivas
};

#endif	/* BuscaLocalRepetida_H */