/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QRDecomposition.h
 * Author: rafael.veiga
 *
 * Created on 4 de Dezembro de 2018, 11:58
 */

#ifndef _QRDECOMPOSITION_H
#define	_QRDECOMPOSITION_H

class QRDecomposition {
    public:
        QRDecomposition(double const* const* matrix, const int numberLines, const int numberColumns);
        QRDecomposition(const QRDecomposition& orig);
        virtual ~QRDecomposition();
        double** createH(int* numberLines, int* numberColumns);
        double** createR(int* numberLines, int* numberColumns);
        double** createQ(int* numberLines, int* numberColumns);
        double* solveLeastSquares(double const* rightHandSide, const int dimension);
		bool isFullRank( ) const;
    private:
        double** qr;
        int numberLines;
        int numberColumns;
        double* diagonalR;
        bool fullRank;
};

#endif	/* _QRDECOMPOSITION_H */

