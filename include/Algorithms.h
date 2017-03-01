#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Matrix.h"

namespace Algorithms
{
    //solve Ax=b where x is the returned value, b a vector of known terms and m a square matrix
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b);
    //solve Ax=b where x is the returned value, b a vector of known terms and m a square matrix
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b,float precalculatedDeterminant);
}

#endif // ALGORITHMS_H
