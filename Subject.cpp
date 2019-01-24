/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Subject.cpp
 * Author: rafael.veiga
 * 
 * Created on 4 de Dezembro de 2018, 11:53
 */

#include <iostream>
#include <cmath>

#include "Subject.h"
#include "Tree.h"

Subject::Subject(){
    tree = new Tree();
//    fitness = new double[objectives];
//    fitnessTest = new double[objectives];
    fitnessLS = INFINITY;
    fitnessTestLS = INFINITY;
    printing = true;
};

Subject::Subject(Tree* n){
    tree = n;
    fitnessLS = INFINITY;
    fitnessTestLS = INFINITY;
    printing = true;
};

Subject::~Subject(){
//    tree->print();
    delete tree;
};

double Subject::complexity(){
    if(conf->complexity == 0)
        return tree->high;
    else if(conf->complexity == 1)
        return tree->terminals;
}

void Subject::print(){
//    cout << ".";
    tree->print();
};
