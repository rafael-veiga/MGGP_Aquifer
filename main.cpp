/* 
 * File:   main.cpp
 * Author: João Marcos de Freitas ; Rafael Valente Veiga
 *
 * Created on 14 de Janeiro de 2016
 */
#include <cstdio>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

//#include "Datamaker.h"
#include "No.h"
#include "Tree.h"
#include "Database.h"
#include "Gramatica.h"
#include "Configures.h"
#include "Operators.h"
#include "Search.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** args) {
    
    // imprimindo argumentos
//    for(int i=0; i<argc;i++){
//    cout << " " << args[i];    
//    }
//    cout << endl;
//string nome_saida = args[9];    
freopen(args[8], "w", stdout);

    int seed = atoi(args[1]);
    string gramatica = args[2];
    string dados = args[3];
    string grupo = args[4];
    int geracoes = atoi(args[5]);
    int populacao = atoi(args[6]);
    int altura = atoi(args[7]);
    //int complexidade = atoi(args[8]); //0=high 1=terminals
    
    srand(seed);
    cout.precision(7);

    //configuracoes
    conf = new Configures();
    conf->treeHigh = altura;
    conf->popSize = populacao;
    conf->iterations = geracoes;
    conf->leastSquare = 1;
    conf->elitism = 0.1;
    conf->mono = 1; // 0 = monobjetivo;  1 = multiobjetivo
    //conf->complexity = complexidade; // 0 = high 1 = terminals
    conf->complexity = 1;
    //gramatica
    gram = new Gramatica(gramatica);
   // cout<< "fim da gramatica" << endl;
    //operadores
   // cout << "inicio do operadores" << endl;
    //gram->imprimeGramatica();
    op = new Operators();
   // cout << "fim do operadores" << endl << "inicio dos database" << endl;
    //dados
//    data = new Database("read/base5.txt", "read/grupo5.txt");
    data = new Database(dados, grupo);
    //cout << "fim do database" << endl << "inicio do search" << endl;
    //busca
    Search* s = new Search();
    delete s;

    fclose(stdout);
    
    return 0;
}

