/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Search.cpp
 * Author: rafael.veiga
 * 
 * Created on 4 de Dezembro de 2018, 11:51
 */

#include <algorithm>
#include <math.h>
#include <iomanip>
#include "Search.h"
//#include "Population.h"
#include "Subject.h"
#include "Database.h"
#include "Gramatica.h"
#include "Configures.h"
#include "Parser.h"
#include <omp.h>

using namespace std;

bool mySort(Subject* a, Subject* b) {
    //    return (a->fitness < b->fitness);
    return (a->fitnessLS < b->fitnessLS);
};

bool sortTest(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->fitnessTestLS < b->fitnessTestLS);
};

bool sortRank(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->ranking < b->ranking);
};

bool Search::sortHigh(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->tree->high < b->tree->high);
};

bool Search::sortComplexity(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->complexity() < b->complexity());
};

bool Search::sortSize(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->tree->terminals < b->tree->terminals);
};

bool Search::sortFit(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->fitnessLS < b->fitnessLS);
};

bool Search::sortFitTest(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->fitnessTestLS < b->fitnessTestLS);
};

bool Search::sortFitValid(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->fitnessValidLS < b->fitnessValidLS);
};

bool sortCrow(Subject* a, Subject* b) {
    //    return (a->fitnessTest < b->fitnessTest);
    return (a->crowdingDistance > b->crowdingDistance);
};

Search::Search() {
    testError = INFINITY;
    testTr = INFINITY;
    errors = 0;

    aux = new int[conf->popSize];
    for (int i = 0; i < conf->popSize; i++)
        aux[i] = 0;

    conf->mono == 0 ? doMonoSearch() : doMultiSearch();
};

void Search::doMonoSearch() {
    pop = new Subject*[conf->popSize * 2];
    convergence = new double[conf->iterations];

    for (int i = 0; i < conf->popSize; i++) { //Cria população
        pop[i] = new Subject(gram->criaArvExp());
    }

    for (int i = 0; i < conf->popSize; i++) //Calcula primeira vez
    {
        calcFitnessLS(pop[i]);
    }

    int size = (conf->popSize * conf->elitism);

    for (int it = 0; it < conf->iterations; it++) {
        Operate();
        sort(pop, pop + conf->popSize, sortFit);
        sort(pop + conf->popSize, pop + conf->popSize * 2, sortFit);

        sort(pop, pop + conf->popSize + size, sortFit);
        for (int i = conf->popSize; i < conf->popSize * 2; i++)
            delete pop[i];
        convergence[it] = pop[0]->fitnessLS;

        //        cout << it << endl;
        //        if(it > (int)(conf->iterations * 0.00005))
        //            cout << convergence[it]/convergence[(int)(it - conf->iterations * 0.00005)] << endl;
        //        if(it > (int)(conf->iterations * 0.00005) && convergence[it] > (convergence[(int)(it - conf->iterations * 0.00005)] - convergence[(int)(it - conf->iterations * 0.00005)] * 0.00000000001)){
        //            cout << "Stopped Converging on " << it << "!" << endl;
        //            break;
        //        }
    }

    for (int i = 0; i < conf->popSize; i++) {
        calcFitnessTestLS(pop[i]);
    }

    sort(pop, pop + conf->popSize, sortFitTest);

    for (int i = 0; i < conf->popSize; i++) {
        calcFitnessValidLS(pop[i]);
    }

    sort(pop, pop + conf->popSize, sortFitValid);

    for (int i = 0; i < conf->popSize; i++) {
        cout << pop[i]->ranking << ", "
                << pop[i]->tree->high << ", "
                << pop[i]->fitnessLS << ", "
                << pop[i]->fitnessTestLS << ", "
                << pop[i]->fitnessValidLS << ", "
                << pop[i]->tree->infixPrint() << ", ";
        pop[i]->tree->printAlphas();
        cout << endl;
    }

    //    double diff = abs(convergence[conf->iterations - 1]) + 1;
    //    double max = convergence[conf->iterations - 1] < 0 ? convergence[0] + convergence[conf->iterations - 1] : convergence[0];
    //    cout << diff << " " << max << endl;
    //    cin.get();
    //
    //    for(int i = 0; i < conf->iterations; i += conf->iterations * .1){
    //        cout << convergence[i] << endl;
    ////        for(int j = 0; j < convergence[i] + diff; j += max * .1){
    ////            cout << "-";
    ////        }
    ////        cout << "." << endl;
    //    }
};

void Search::doMultiSearch() {
    double tempo = omp_get_wtime();
    pop = new Subject*[conf->popSize * 2];
    convergence = new double[conf->iterations];

    for (int i = 0; i < conf->popSize; i++) { //Cria população
        pop[i] = new Subject(gram->criaArvExp());
    }

    for (int i = 0; i < conf->popSize; i++) {
        calcFitnessLS(pop[i]);
    }

    //    for(int i = 0; i < 100000000; i++)
    //        calcRank(conf->popSize);

    //    double old = 0;
    for (int it = 0; it < conf->iterations; it++) {
        data->permut();
        Operate();
        calcRank(conf->popSize * 2);

        //        double max = 0;
        //        double maxcrow = 0;
        //
        //        int space = 0;
        //        while(pop[space]->ranking == 0){
        //            if(pop[space]->fitnessLS > max) {max = pop[space]->fitnessLS ; maxcrow = pop[space]->crowdingDistance;}
        //            space++;
        //        }
        //
        //        if(old < max){
        //            old = max;
        ////            cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
        //        }
        //
        //        if(old > max){
        //            cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
        //            cin.get();
        //        }
        //
        //        for(int i = 0; i < max; i++)
        //            cout << " ";
        //        cout << max << " " << old << " " << maxcrow << endl;
        //        for(int i = 0; pop[i]->ranking == 0; i++)
        //            cout << pop[i]->ranking << " " << pop[i]->tree->high << " " << pop[i]->fitnessLS << " " << pop[i]->crowdingDistance << endl;
        //        cout << endl;
        //        cin.get();

        //        update population
        for (int i = conf->popSize; i < conf->popSize * 2; i++)
            delete pop[i];

        // teste
        if (it % 10 == 0) {
            cout << it << "\t";
            for (int i = 0; i < conf->popSize; i++) {
                if (pop[i]->ranking == 0) {
                    cout << pop[i]->tree->high << ","
                            << pop[i]->tree->terminals << ","
                            << pop[i]->fitnessLS;
                    cout << ";";
                }

            }
            cout << endl;
        }
    }
    // fim teste
    cout << "RESULTADO" << endl;
	data->permut_teste();
    for (int i = 0; i < conf->popSize; i++) {
        calcFitnessTestLS(pop[i]);
    }

    calcRankTest(conf->popSize);

    for (int i = 0; i < conf->popSize; i++) {
        calcFitnessValidLS(pop[i]);
    }

    calcRankValid(conf->popSize);

    for (int i = 0; i < conf->popSize; i++) {
        cout << pop[i]->ranking << ", "
                << pop[i]->tree->high << ", "
                << pop[i]->tree->terminals << ", "
                << pop[i]->fitnessLS << ", "
                << pop[i]->fitnessTestLS << ", "
                << pop[i]->fitnessValidLS << ", "
                << pop[i]->tree->infixPrint() << ", " << "pop[i]->tree->print()"
                << ",( "  << pop[i]->treino_vp << ";" << pop[i]->treino_vn << ";" << pop[i]->treino_fp << ";" << pop[i]->treino_fn << ")"
                << ",( "  << pop[i]->teste_vp << ";" << pop[i]->teste_vn << ";" << pop[i]->teste_fp << ";" << pop[i]->teste_fn << ")"
                << ",( "  << pop[i]->valida_vp << ";" << pop[i]->valida_vn << ";" << pop[i]->valida_fp << ";" << pop[i]->valida_fn << ")";
        //             pop[i]->tree->printAlphas();
        cout << endl;
    }
    // inserir modificação
    cout << "VETORES" << endl;
    cout << "TREINO" << endl;
    for(int i=0; i<conf->popSize; i++){
        Subject* s = pop[i];
        for(int l = 0;l<data->trainCount;l++){
            double* alpha;
        cout <<s->tree->treeResult(data->values[data->training[l]])<<";";   
        }
        
    cout << endl;    
    }
    cout <<"TESTE"<<endl;
    for(int i=0; i<conf->popSize; i++){
        Subject* s = pop[i];
        for(int l = 0;l<data->testCount;l++){
            double* alpha;
        cout <<s->tree->treeResult(data->values[data->test[l]])<<";";   
        }
        
    cout << endl;    
    }
     cout <<"VALIDATION"<<endl;
    for(int i=0; i<conf->popSize; i++){
        Subject* s = pop[i];
        for(int l = 0;l<data->validCount;l++){
            double* alpha;
        cout <<s->tree->treeResult(data->values[data->validation[l]])<<";";   
        }
    cout << endl;    
    }
     
   // Encontrado
    cout <<"ENCONTRADO"<<endl; 
    for(int i = 0;i<data->trainCount;i++){
     cout << data->results[data->training[i]]  <<";";
    }
    cout <<endl;
    for(int i = 0;i<data->testCount;i++){
     cout << data->results[data->test[i]]  <<";";
    }
    cout <<endl;
    for(int i = 0;i<data->validCount;i++){
     cout << data->results[data->validation[i]]  <<";";
    }
    cout << endl;
    tempo = omp_get_wtime() - tempo;
    cout << "Tempo = " << tempo;
};

int Search::tournamentMono(int a, int b) {
    if (pop[a]->fitnessLS < pop[b]->fitnessLS)
        return a;
    else
        return b;
}

int Search::tournamentMulti(int a, int b) {
    if (pop[a]->ranking < pop[b]->ranking)
        return a;
    else if (pop[a]->ranking > pop[b]->ranking)
        return b;
    else {
        if (pop[a]->crowdingDistance > pop[b]->crowdingDistance)
            return a;
        else
            return b;
    }
}

void Search::Operate() {
    for (int i = conf->popSize; i < conf->popSize * 2; i += 2) {
        pop[i] = (new Subject());
        pop[i + 1] = (new Subject());

        int a, b;
        int s1 = rand() % conf->popSize;
        int s2 = rand() % conf->popSize;
        a = conf->mono == 0 ? tournamentMono(s1, s2) : tournamentMulti(s1, s2);

        s1 = rand() % conf->popSize;
        s2 = rand() % conf->popSize;
        b = conf->mono == 0 ? tournamentMono(s1, s2) : tournamentMulti(s1, s2);

        aux[a]++;
        aux[b]++;

        op->Cross(pop[a]->tree, pop[b]->tree, pop[i]->tree, pop[i + 1]->tree);

        op->Mutate(pop[i]->tree);
        op->Mutate(pop[i + 1]->tree);

    }
    
    for(int i=0;i<conf->popSize * 2; i++){
        calcFitnessLS(pop[i]);
    }
};

bool Search::dominate(Subject* a, Subject* b) {
    if (a->fitnessLS <= b->fitnessLS && a->complexity() <= b->complexity()) {
        if (a->complexity() < b->complexity()) {
            return true;
        } else if (a->fitnessLS < b->fitnessLS) {
            return true;
        }
    }
    return false;
};

bool Search::dominateTest(Subject* a, Subject* b) {
    if (a->fitnessTestLS <= b->fitnessTestLS && a->complexity() <= b->complexity()) {
        if (a->complexity() < b->complexity()) {
            return true;
        } else if (a->fitnessTestLS < b->fitnessTestLS) {
            return true;
        }
    }
    return false;
};

bool Search::dominateValid(Subject* a, Subject* b) {
    if (a->fitnessValidLS <= b->fitnessValidLS && a->complexity() <= b->complexity()) {
        if (a->complexity() < b->complexity()) {
            return true;
        } else if (a->fitnessValidLS < b->fitnessValidLS) {
            return true;
        }
    }
    return false;
};

void Search::calcRank(int size) {
    /**
        Juntar tudo
        selecionar 1s não dominados rank = 0
        aumentar rank dos outros

     **/

    int ranking = 0;

    for (int i = 0; i < size; i++)
        pop[i]->ranking = 0;

    bool stop = false;
    while (!stop) {
        stop = true;
        for (int i = 0; i < size; i++) // ele
        {
            if (pop[i]->ranking == ranking) // se tiver na hora dele
            {
                for (int j = 0; j < size; j++) // pra cada um candidato
                {
                    if (i != j && (pop[j]->ranking == ranking)) // se não for ele e se tiver no mesmo ranking
                    {
                       // if (pop[i]->tree->infixPrint().compare(pop[j]->tree->infixPrint()) == 0) {
                            if (rand() % 100 < 50 && pop[i]->fitnessLS == pop[j]->fitnessLS && pop[i]->complexity() == pop[j]->complexity()) {
                            pop[j]->ranking = INFINITY;
                        } else if (dominate(pop[i], pop[j])) // se for dominado por j então ele aumenta o ranking
                        {
                            pop[j]->ranking = ranking + 1;
                            stop = false;
                        }



                    }
                }
            }
        }
        ranking++;
    }
    sort(pop, pop + size, sortRank);

    int i, f, r;
    i = f = r = 0;
    while (f <= conf->popSize) {
        while (pop[f]->ranking == r)
            f++;

        sort(pop + i, pop + f, sortFit);
        crowdingDistanceFitness(i, f - 1);
        sort(pop + i, pop + f, sortComplexity);
        crowdingDistanceComplexity(i, f - 1);

        if (f > conf->popSize)
            sort(pop + i, pop + f, sortCrow);

        i = f;
        f++;
        r++;
    }
};

void Search::calcRankTest(int size) {
    /**
        Juntar tudo
        selecionar 1s não dominados rank = 0
        aumentar rank dos outros

     **/

    int ranking = 0;

    for (int i = 0; i < size; i++)
        pop[i]->ranking = 0;

    bool stop = false;
    while (!stop) {
        stop = true;
        for (int i = 0; i < size; i++) // ele
        {
            if (pop[i]->ranking == ranking) // se tiver na hora dele
            {
                for (int j = 0; j < size; j++) // pra cada um candidato
                {
                    if (i != j && (pop[j]->ranking == ranking)) // se não for ele e se tiver no mesmo ranking
                    {
                        if (pop[i]->tree->infixPrint() == pop[j]->tree->infixPrint()) {
                            pop[j]->ranking = INFINITY;
                        } else if (dominateTest(pop[i], pop[j])) // se for dominado por j então ele aumenta o ranking
                        {
                            pop[j]->ranking = ranking + 1;
                            stop = false;
                        }
                    }
                }
            }
        }
        ranking++;
    }
    sort(pop, pop + size, sortRank);

    int i, f, r;
    i = f = r = 0;
    while (f <= conf->popSize) {
        while (f < conf->popSize && pop[f]->ranking == r)
            f++;

        sort(pop + i, pop + f, sortFitTest);
        crowdingDistanceFitnessTest(i, f - 1);
        sort(pop + i, pop + f, sortComplexity);
        crowdingDistanceComplexity(i, f - 1);

        //desordena o rank se o tamanho dele for >= conf->popSize
        if (f > conf->popSize)
            sort(pop + i, pop + f - 1, sortCrow);

        i = f;
        f++;
        r++;
    }
};

void Search::calcRankValid(int size) {
    /**
        Juntar tudo
        selecionar 1s não dominados rank = 0
        aumentar rank dos outros

     **/

    int ranking = 0;

    for (int i = 0; i < size; i++)
        pop[i]->ranking = 0;

    bool stop = false;
    while (!stop) {
        stop = true;
        for (int i = 0; i < size; i++) // ele
        {
            if (pop[i]->ranking == ranking) // se tiver na hora dele
            {
                for (int j = 0; j < size; j++) // pra cada um candidato
                {
                    if (i != j && (pop[j]->ranking == ranking)) // se não for ele e se tiver no mesmo ranking
                    {
                        if (pop[i]->tree->infixPrint() == pop[j]->tree->infixPrint()) {
                            pop[j]->ranking = INFINITY;
                        } else if (dominateValid(pop[i], pop[j])) // se for dominado por j então ele aumenta o ranking
                        {
                            pop[j]->ranking = ranking + 1;
                            stop = false;
                        }
                    }
                }
            }
        }
        ranking++;
    }
    sort(pop, pop + size, sortRank);

    int i, f, r;
    i = f = r = 0;
    while (f <= conf->popSize) {
        while (f < conf->popSize && pop[f]->ranking == r)
            f++;

        sort(pop + i, pop + f, sortFitValid);
        crowdingDistanceFitnessValid(i, f - 1);
        sort(pop + i, pop + f, sortComplexity);
        crowdingDistanceComplexity(i, f - 1);

        if (f > conf->popSize)
            sort(pop + i, pop + f - 1, sortCrow);

        i = f;
        f++;
        r++;
    }
};

void Search::crowdingDistanceFitness(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = MAX;
        for (int j = i + 1; j < f; j++) {
            pop[j]->crowdingDistance = (pop[j + 1]->fitnessLS - pop[j - 1]->fitnessLS) / (pop[f]->fitnessLS - pop[i]->fitnessLS);
        }
    }
}

void Search::crowdingDistanceFitnessTest(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = MAX;
        for (int j = i + 1; j < f; j++) {
            pop[j]->crowdingDistance = (pop[j + 1]->fitnessTestLS - pop[j - 1]->fitnessTestLS) / (pop[f]->fitnessTestLS - pop[i]->fitnessTestLS);
        }
    }
}

void Search::crowdingDistanceFitnessValid(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = INFINITY;
        for (int j = i + 1; j < f; j++) {
            pop[j]->crowdingDistance = (pop[j + 1]->fitnessValidLS - pop[j - 1]->fitnessValidLS) / (pop[f]->fitnessValidLS - pop[i]->fitnessValidLS);
        }
    }
}

void Search::crowdingDistanceHigh(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = MAX;
        for (int j = i + 1; j < f; j++) {
            double num = (pop[j + 1]->tree->high - pop[j - 1]->tree->high);
            double den = (pop[f]->tree->high - pop[i]->tree->high);
            if (den == 0)
                pop[j]->crowdingDistance += 0;
            else
                pop[j]->crowdingDistance += num / den;
        }
    }
}

void Search::crowdingDistanceComplexity(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = MAX;
        for (int j = i + 1; j < f; j++) {
            double num = (pop[j + 1]->complexity() - pop[j - 1]->complexity());
            double den = (pop[f]->complexity() - pop[i]->complexity());
            if (den == 0)
                pop[j]->crowdingDistance += 0;
            else
                pop[j]->crowdingDistance += num / den;
        }
    }
}

void Search::crowdingDistanceSize(int i, int f) {
    if (i == f) {
        pop[i]->crowdingDistance = MAX;
    } else {
        pop[i]->crowdingDistance = pop[f]->crowdingDistance = MAX;
        for (int j = i + 1; j < f; j++) {
            double num = (pop[j + 1]->tree->terminals - pop[j - 1]->tree->terminals);
            double den = (pop[f]->tree->terminals - pop[i]->tree->terminals);
            if (den == 0)
                pop[j]->crowdingDistance += 0;
            else
                pop[j]->crowdingDistance += num / den;
        }
    }
}

void Search::calcFitnessLS(Subject* s) {
    //double fitness = 0;
    int lines = data->trainCount;
    

    s->treino_vp = s->treino_fp = s->treino_vn = s->treino_fn = 0;
    int cont = 0;
    //classification

    //double total = 0;
    //omp_set_num_threads(7);
    {
#pragma omp parallel for reduction(+: cont)   
    for (int i = 0; i < lines; i++) {
        int b = omp_get_num_threads();
        double res = (s->tree->treeResult(data->values[data->training[i]]));
//        if (data->results[data->training[i]] == 0) {
//            total += conf->peso0;
//        } else {
//            total += conf->peso1;
//        }
        if (res != data->results[data->training[i]]) {
            cont++;
        } 
        
    }
    }
    
    
    s->fitnessLS = ((double)(cont) / lines) * 100;

    //    //regression
    //    if(conf->leastSquare == 1){
    //        dimension = columns;
    //        subMat = new double*[lines];
    //        for(int i = 0; i < lines; i++)
    //            subMat[i] = new double[columns];
    //
    //        //Avalia cada subExp
    //        for(int i = 0; i < columns; i++)
    //        {
    //            double* exp = &s->tree->sub.at(i).at(0);
    //            int sizeExp = s->tree->sub.at(i).size();
    //            for(int j = 0; j < lines; j++)
    //            {
    //                double* a = new double[sizeExp];
    //                double* var = data->values[data->training[j]];
    //                for(int k = 0; k < sizeExp; k += 2)
    //                {
    //                    a[k] = exp[k];
    //                    a[k + 1] = exp[k + 1];
    //                    if(a[k] == 3.0)
    //                    {
    //                        a[k] = 0.0;
    //                        a[k + 1] = var[(int)a[k + 1]];
    //                    }
    //                    if(a[k] == 5.0)
    //                    {
    //                        a[k] = 0.0;
    //                    }
    //                }
    //
    //                subMat[j][i] = Avalia(a, sizeExp);
    //                delete [] a;
    //            }
    //        }
    //
    //
    //        QRDecomposition* qrDec = new QRDecomposition(subMat, lines, columns);
    //        double* b = new double[lines];
    //        for(int i = 0; i < lines; i++)
    //        {
    //            b[i] = data->results[data->training[i]];
    //        }
    ////        se tem algo lá, apagar
    //        alpha = s->tree->alpha;
    //        if(alpha != NULL)
    //            delete [] alpha;
    ////        novos coeficientes
    //        alpha = s->tree->alpha = qrDec->solveLeastSquares(b, lines);
    //
    //        if(alpha == NULL){
    //            dimension = 0;
    //        }
    //
    //        for(int i = 0; i < lines; i++)
    //            delete [] subMat[i];
    //        delete [] subMat;
    //        delete [] b;
    //        delete qrDec;
    //    }
    //
    //    for(int i = 0; i < lines ; i++){
    //        double res = (s->tree->treeResult(data->values[data->training[i]], alpha, dimension));
    //
    ////        for(int j = 0; j < data->countVar; j++)
    ////            cout << data->values[data->training[i]][j] << " ";
    ////        if(s->tree->infixPrint() == "(a + ((c * b) + (d / e)))"){
    ////            cout << data->results[data->training[i]] << " " << res << " " << data->results[data->training[i]] - res << " " << pow(data->results[data->training[i]] - res, 2) << endl;
    ////            cin.get();
    ////        }
    //
    //        res = pow(data->results[data->training[i]] - res, 2);
    //
    //        if(res == INFINITY){
    //            fitness = INFINITY;
    //            break;
    //        }
    //        if(res == NAN){
    //            fitness = INFINITY;
    //            break;
    //        }
    //        fitness += res;
    //    }
    //    s->fitnessLS = fitness/lines;
};

void Search::calcFitnessTestLS(Subject* s) {
    //double fitness = 0;
    int lines = data->testCount;
    int columns = s->tree->subCounter;
    double* alpha = s->tree->alpha;
    int dimension = columns;
    if (conf->leastSquare == 0 || alpha == NULL) {
        dimension = 0;
    }

    s->teste_vp = s->teste_fp = s->teste_vn = s->teste_fn = 0;

    //classification
    //double total = 0;

    for (int i = 0; i < lines; i++) {
        double res = (s->tree->treeResult(data->values[data->test[i]]));
//        if (data->results[data->training[i]] == 0) {
//            total += conf->peso0;
//        } else {
//            total += conf->peso1;
//        }
        if (res != data->results[data->test[i]]) {
            if (data->results[data->test[i]] == 0) {
                //fitness += conf->peso0;
                s->teste_fp++;
            } else {
                //fitness += conf->peso1;
                s->teste_fn++;
            }
        } else {
            if (data->results[data->test[i]] == 0) {
                s->teste_vn++;
            } else {
                s->teste_vp++;
            }
        }
    }

    s->fitnessTestLS = ((double)(s->teste_fn + s->teste_fp) / lines) * 100;

    //    //regression
    //    for(int i = 0; i < lines ; i++)
    //    {
    //        double res = (s->tree->treeResult(data->values[data->test[i]], alpha, dimension));
    //        res = pow(data->results[data->test[i]] - res, 2);
    //        if(res == INFINITY)
    //        {
    //            fitness = INFINITY;
    //            break;
    //        }
    //        if(res == NAN)
    //        {
    //            fitness = INFINITY;
    //            break;
    //        }
    //        fitness += res;
    //    }
    //    s->fitnessTestLS = fitness/lines;
};

void Search::calcFitnessValidLS(Subject* s) {
    //double fitness = 0;
    int lines = data->validCount;
    int columns = s->tree->subCounter;
    double* alpha = s->tree->alpha;
    int dimension = columns;
    if (conf->leastSquare == 0 || alpha == NULL) {
        dimension = 0;
    }

    s->valida_vp = s->valida_fp = s->valida_vn = s->valida_fn = 0;

    //classification
    //double total = 0;

    for (int i = 0; i < lines; i++) {
        double res = (s->tree->treeResult(data->values[data->validation[i]]));
//        if (data->results[data->training[i]] == 0) {
//            total += conf->peso0;
//        } else {
//            total += conf->peso1;
//        }
        if (res != data->results[data->validation[i]]) {
            if (data->results[data->validation[i]] == 0) {
                //fitness += conf->peso0;
                s->valida_fp++;
            } else {
                //fitness += conf->peso1;
                s->valida_fn++;
            }
        } else {
            if (data->results[data->validation[i]] == 0) {
                s->valida_vn++;
            } else {
                s->valida_vp++;
            }
        }
    }

    s->fitnessValidLS = ((double)(s->valida_fn + s->valida_fp) / lines) * 100;
    //      //regression
    //    for(int i = 0; i < lines ; i++)
    //    {
    //        double res = (s->tree->treeResult(data->values[data->validation[i]], alpha, dimension));
    //        res = pow(data->results[data->validation[i]] - res, 2);
    //        if(res == INFINITY)
    //        {
    //            fitness = INFINITY;
    //            break;
    //        }
    //        if(res == NAN)
    //        {
    //            fitness = INFINITY;
    //            break;
    //        }
    //        fitness += res;
    //    }
    //    s->fitnessValidLS = fitness/lines;
};

void Search::Replace() {
    for (int i = conf->popSize * 2 - 1; i >= conf->popSize; i--)
        delete pop[i];
};

Search::~Search() {
    delete [] pop;
};
