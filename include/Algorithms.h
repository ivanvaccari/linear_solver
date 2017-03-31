/*
 DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 Version 2, December 2004

 Copyright (C) 2017 Ivan Vaccari <vaccari87@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

 DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.


*/
#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Matrix.h"
#include <tuple>
namespace Algorithms
{
    //solve Ax=b where x is the returned value, b a vector of known terms and m a square matrix
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b);

    //solve Ax=b where x is the returned value, b a vector of known terms and m a square matrix
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b,float precalculatedDeterminant);

    //solve Ax=b where x is the returned value, b a vector of known terms and m a square matrix
    std::vector<float> triangular_matrix_solve(Matrix A, std::vector<float> b);

    /*! \brief Perform the gauss reduction alorithm (https://en.wikipedia.org/wiki/Gaussian_elimination)
        \param A a matrix to reduct
        \param b a vector of known terms to reduct
        \return a tuple of values, containing in this order the reduct matrix, his transformed known terms vector and the permutation matrix
    */
    std::tuple<Matrix,std::vector<float>,Matrix > gauss_reduction(Matrix A,std::vector<float> b);
}

#endif // ALGORITHMS_H
