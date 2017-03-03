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
        for(unsigned int i=0;i<result.size();++i){
            Matrix Ai=A;
            Ai.replaceColumn(i,b);
            result[i]=Ai.determinant()/precalculatedDeterminant;
        }
        return result;
    }

    std::vector<float> triangular_matrix_solve(Matrix A, std::vector<float> b){
        std::vector<float> x(b.size());
        if (A.diagonalDeterminant()==0)
            throw std::string("Can't solve with triangular matrix rule. Provided matrix have zero determinant");
        if (A.isInferiorTriangular()){
            x[0]=b[0]/A.getRawCell(0,0);
            for(unsigned int i=1;i<A.sizeh();++i){
                float lineMul=0;
                for(unsigned int k=0;k<i;k++){
                    lineMul+=x[k]*A.getRawCell(i,k);
                }
                x[i]=(b[i]-lineMul)/A.getRawCell(i,i);
            }
        }else if (A.isSuperiorTriangular()){
            x[A.sizeh()-1]=b[A.sizeh()-1]/A.getRawCell(A.sizeh()-1,A.sizeh()-1);
            for(int i=A.sizeh()-2;i>=0;--i){
                float lineMul=0;
                for(unsigned int k=i;k<A.sizeh();k++){
                    lineMul+=x[k]*A.getRawCell(i,k);
                }
                x[i]=(b[i]-lineMul)/A.getRawCell(i,i);
            }
        }else{
            throw std::string("Provided matrix is not triangular.");
        }
        return x;
    }

}
