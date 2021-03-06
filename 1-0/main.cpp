//--------------------------------------------------//
// File Name: main.cpp                              //
// Function: Arithmetic calculation                 //
// Copyright(C) 2016 shoarai                        //
// The MIT License (MIT)                            //
//--------------------------------------------------//
#include <iostream>
#include <cstring>
#include <math.h>

#include "Matrix.h"
#include "SquareMatrix.h"
#include "Vector.h"
#include "numpy.h"

using namespace arith;

void calcVetor();
void calcMatrix();
void calcSquareMatrix();

int main()
{
    calcVetor();
    calcMatrix();
    calcSquareMatrix();
  	return 0;
}

void calcVetor () {
    // Initialize x, y and z elements
    Vect vecA;
    Vect vecB(1, 10, 100);

    // Set elements
    vecA.set(1, 2, 3);

    // Get elements
    double x = vecA.getx();
    double y = vecA.gety();
    double z = vecA.getz();

    Vect vecC;

    // Addition and subtraction of vectors
    vecC  = vecA + vecB;
    vecC += vecA;
    vecC  = vecA - vecB;
    vecC -= vecA;

    int val = 10;

    // Multiplication and division of a vector and a scholar
    vecC  = vecA * val;
    vecC *= val;
    vecC  = vecA / val;
    vecC /= val;

    // Cross product
    vecC = vecA * vecB;

    // Inner product
    double inner = vecA % vecB;

    // Norm
    double norm = vecA.norm();

    // Normalization
    vecC = vecA.normalize();
}

void calcMatrix() {
    // Initialize the number of rows and columns
    Matrix matA(3, 2);
    Matrix matB(3, 2);

    // Set elements
    matA(0, 1) = 10;
    matB(2, 2) = 20;

    // Get elements
    double a01 = matA(0, 1);
    double b22 = matB(2, 2);

    // Addition and subtraction of matrixes
    Matrix matC = matA + matB;
    matC += matA;
    matC  = matA - matB;
    matC -= matB;

    Matrix matD(2, 3);

    // Multiplication and division of matrixes
    Matrix matE = matD * matA;

    int val = 10;

    // Multiplication and division of a matrix and a scholar
    matA  = matB * val;
    matA *= val;
    matA  = matB / val;
    matA /= val;

    // Transpose
    matA = matD.transpose();
}

void calcSquareMatrix() {
    // Initialize the number of rows and columns
    SquareMatrix smatA(3);

    Matrix matA(2, 2);

    // Convert a matrix with the same number of rows and columns
    // into square matrix type
    SquareMatrix smatB = matA;

    // Determinant
    double det = smatA.det();

    // Inverse matrix
    if(det != 0){
        SquareMatrix smatC = smatA.invrs(det);
    }
}

