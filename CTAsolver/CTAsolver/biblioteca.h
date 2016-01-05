// -*- C++ -*-
/*
 * File:   biblioteca.h
 * Author: Rafael Vareto
 *
 * Created on 29 de Outubro de 2015, 12:28
 */

#ifndef BIBLIOTECA_H
#define	BIBLIOTECA_H

#define MAX_TURNO 20
#define MAX_MANHA 10
#define MAX_TARDE 10
#define MAX_NOITE 10
#define MAX_NOITE_CONS 3
#define MAX_SERVICOS_CONS 6
#define MAX_FOLGAS_CONS 6

#define MIN_MANHA 12
#define MIN_TARDE 13
#define MIN_NOITE 9

#define MANHA 'M'
#define TARDE 'T'
#define NOITE 'N'
#define FOLGA 'F'
#define VAZIO '-'

#define DISPONIVEL 0
#define ALOCADO 1

#define RESPEITANDO 1
#define VIOLANDO 2

#define MAIOR_VALOR 0
#define MENOR_VALOR 1

#define NUM_TENTATIVA 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <limits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#endif	/* BIBLIOTECA_H */
