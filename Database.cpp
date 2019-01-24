#include <cstdio>
//#include <iostream>
#include <string>
#include <fstream>
#include "Database.h"

Database* data;

Database::Database(string base, string groups){
    loadBase(base);
    loadGroups(groups);
	this->permut();
};

void Database::permut(){
    double aux;
    int n;
    int tam = trainCount/2;
    for(int v=0;v<this->countVar;v++){
        for(int i=tam;i<this->trainCount;i++){
            n = (rand() % tam)+tam;
            aux = this->values[this->training[i]][v];
            this->values[this->training[i]][v] = this->values[this->training[n]][v];
            this->values[this->training[n]][v] = aux;
        }
    }
}

void Database::permut_teste(){
    double aux;
    int n;
    int tam = testCount/2;
    for(int v=0;v<this->countVar;v++){
        for(int i=tam;i<this->testCount;i++){
            n = (rand() % tam)+tam;
            aux = this->values[this->test[i]][v];
            this->values[this->test[i]][v] = this->values[this->test[n]][v];
            this->values[this->test[n]][v] = aux;
        }
    }
}

void Database::loadBase(string base){
    ifstream arq;
    string line;

    arq.open(base.c_str());

    arq >> countVar >> countResults;
    vars = new string[countVar];
    values = new double*[countResults];
    for(int i = 0; i < countResults; i++)
        values[i] = new double[countVar];
    results = new double[countResults];

    //inserido
    
    
    for(int i = 0; i < countVar; i++)
        arq >> vars[i];

    arq >> line;

    for(int i = 0; i < countResults; i++){
        for(int j = 0; j < countVar; j++){
            arq >> values[i][j];
        }
        arq >> results[i];
    }
    arq.close();
}

void Database::loadGroups(string groups){
//    ifstream arq;
//    string line;
//
//    for(int i = 0; i < countVar; i++){
//        int pos = gram->checkMapV(vars[i]);
//        if(pos != -1){
//            for(int j = 0; j < countResults; j++){
//                swap(values[j][pos], values[j][i]);
//            }
//            swap(vars[i], vars[pos]);
//        }
//    }
ifstream arq;
    string line;
    int temp[countVar];
    for(int i = 0; i < countVar; i++)
        temp[i] = gram->checkMapV(vars[i]);
    
    
    for(int i = 0; i < countVar; i++){
        int pos = temp[i];
        if(pos != -1){
            for(int j = 0; j < countResults; j++){
                swap(values[j][pos], values[j][i]);
            }
            swap(vars[i], vars[pos]);
            swap(temp[i], temp[pos]);
        }
    }
    arq.open(groups.c_str());
    arq >> trainCount >> testCount >> validCount;

    //conf->peso1 = 1.0 - conf->peso0;

    training = new int[trainCount];
    test = new int[testCount];
    validation = new int[validCount];

    arq >> line;
    for(int i = 0; i < trainCount; i++){
        arq >> training[i];
    }
    arq >> line;
    for(int i = 0; i < testCount; i++){
        arq >> test[i];
    }
    arq >> line;
    for(int i = 0; i < validCount; i++){
        arq >> validation[i];
    }
}

void Database::print(){
    cout << "vars: ";
    for(int i = 0; i < countVar; i++)
            cout << vars[i] << "  ";
    cout << endl;
//    for(int i = 0; i < trainCount; i++){
//        cout << i << "   ";
//        for(int j = 0; j < countVar; j++)
//            cout << values[training[i]][j] << "  ";
//        cout << "   " << results[training[i]] << endl;
//    }
//    cout << endl;
//    for(int i = 0; i < testCount; i++){
//        cout << i << "   ";
//        for(int j = 0; j < countVar; j++)
//            cout << values[test[i]][j] << "  ";
//        cout << "   " << results[test[i]] << endl;
//    }
//    cout << endl;
//    for(int i = 0; i < validCount; i++){
//        cout << i << "   " << validation[i] << "  ";
//        for(int j = 0; j < countVar; j++)
//            cout << values[validation[i]][j] << "  ";
//        cout << "   " << results[validation[i]] << endl;
//    }
//    cout << endl;
}

double* Database::getVars(int position){
    return values[position];
}

