/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pilha.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 13:00
 */

#ifndef PILHA_H
#define PILHA_H
#define TAMANHO_ARVORE 25
class Pilha {
public:
    Pilha();
    void push(double a);
    double top();
private:
    char pos;
    double vet[TAMANHO_ARVORE];
};

#endif /* PILHA_H */

