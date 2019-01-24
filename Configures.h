/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Configures.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 11:40
 */
#ifndef CONFIGURES_INCLUDED
#define CONFIGURES_INCLUDED
#include <stdlib.h>


class Configures{
public:
    int treeHigh;
    int popSize;
    int iterations;
    int leastSquare = 0;
    int mono;
//    double peso0;
//    double peso1;
    double elitism;

    int complexity = 0; //0=high 1=terminals

    Configures();

};

extern Configures* conf;

#endif // CONFIGURES_INCLUDED
