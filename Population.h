/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Population.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 11:52
 */

#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED

#include "Gramatica.h"
#include "Subject.h"
#include "Configures.h"

class Population{
    public:
//        Subject* pop[conf->popSize];
        vector<Subject*> pop;

        Population();
        Population(Population* p);
        ~Population();
        void print();
};

#endif // POPULATION_H_INCLUDED

