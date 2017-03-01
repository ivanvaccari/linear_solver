#include "Algorithms.h"
#include "Matrix.h"
#include <iostream>
namespace Algorithms
{
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b){
        return cramer_solve(A,b,A.determinant());
    }
    std::vector<float> cramer_solve(Matrix A, std::vector<float> b, float precalculatedDeterminant){

        if (precalculatedDeterminant==0)
            throw std::string("Can't solve with cramer rule. Provided matrix have zero determinant");

        std::vector<float> result(A.sizeh());
        for(int i=0;i<result.size();++i){
            Matrix Ai=A;
            Ai.replaceColumn(i,b);
            result[i]=Ai.determinant()/precalculatedDeterminant;
        }
        return result;
    }

}
