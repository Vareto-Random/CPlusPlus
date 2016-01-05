/*
 * File:   main.cpp
 * Author: Rafael Vareto
 *
 * Created on 5 de Outubro de 2015, 12:25
 */

#include "biblioteca.h"

#include "instancia.h"
#include "ctas.h"

#include "construtivo.h"
#include "buscalocalrepetida.h"

#include "solucao.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << endl << "Numero invalido de argumentos" << endl;
        exit(1);
    }
    else if(argc == 2)
    {
        //cout << "Aperte uma tecla para iniciar...";cin.get();
        Instancia problema;
        CTAs controladores;

        problema.leitura(argv[1]);
        controladores.inicializa( problema.getNumCTAs() );

        Construtivo gradeInicial;
        BuscaLocalRepetida gradeFinal;

        cout << "ALGORITMO CONSTRUTIVO" << endl;
        gradeInicial.inicializa(problema, controladores);
        gradeInicial.executa();
        gradeInicial.imprimeEscala();
        gradeInicial.imprimePenalidades();

        gradeFinal = gradeInicial;

        cout << endl << "ALGORITMO BUSCA LOCAL REPETITIVO" << endl;
        gradeFinal.executa();
        gradeFinal.imprimeEscala();
        gradeFinal.imprimePenalidades();
     }
    return 0;
}
