/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pilha.cpp
 * Author: rafael.veiga
 * 
 * Created on 4 de Dezembro de 2018, 13:00
 */

#include <cstdio>

#include "Pilha.h"

Pilha::Pilha() {
    this->pos = -1;
    
}

void Pilha::push(double a) {
    if(pos < TAMANHO_ARVORE){
      vet[++pos]=a;  
    }else{
        printf("ERROR");
    }
    
}

double Pilha::top() {
    if(pos>=0){
    return vet[pos--];
    }else{
     printf("ERROR");
     return 0.0;
    }
}

