/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 11:45
 */

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

    double Avalia(double *expr, int tam);
    double Posfixa(double S[], int tam, double V[]);
    int quantidade(int vet[]);
    int verifica(double x);
    int prio_vet(double x, double y);
    double opera(double a, double b, int x);
    void imprimeEquacao(double* expr, int tam);
    void imprimeEquacaoInfixa(double* expr, int tam);
    char converte(double x, double y);

#endif // PARSER_H_INCLUDED

