/* 
 * File:   demanda.h
 * Author: Rafael Vareto
 *
 * Created on 27 de Outubro de 2015, 14:57
 */

#ifndef DEMANDA_H
#define	DEMANDA_H

#include "biblioteca.h"

class Demanda
{
public:
    Demanda(); //construtor padrao
    Demanda(int, int, int, int); //construtor avancado
    Demanda(const Demanda &); //construtor de copia
    Demanda operator =(const Demanda &);
    
    bool inicializa(int, int, int, int); //aloca e inicializa
    bool aloca(int); //aloca espaco(vetor) para a demanda de cada turno
    bool atualiza(int, int, int); //preenche a demanda de cada turno para todos os dias
    bool decrementa(int, char); //decrementa demanda para cada turno(periodo)
    
    int diaIncompleto(); //retorna o dia D que ainda nao possui toda a demanda satisfeita
    char turnoIncompleto(int); //retorna o turno T do dia D que ainda nao possui a demanda satisfeita

private:
    vector<int> manha;
    vector<int> tarde;
    vector<int> noite;
};

#endif	/* DEMANDA_H */

