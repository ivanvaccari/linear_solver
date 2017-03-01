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
