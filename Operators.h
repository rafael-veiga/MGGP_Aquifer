/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operators.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 11:42
 */

#ifndef OPERATORS_H_INCLUDED
#define OPERATORS_H_INCLUDED
#include <stdlib.h>
#include "Gramatica.h"
#include "Tree.h"
#include "No.h"
#include "Configures.h"

class Operators{

public:

    void swap(No* p, No* n, Tree* a, Tree* b);
    int randomI(int x);
    void Mutate(Tree* t);
    void Cross(Tree* a, Tree* b, Tree* c, Tree* d);
};

extern Operators* op;

#endif // OPERATORS_H_INCLUDED
