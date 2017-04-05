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
#include <cmath>
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

    std::tuple<Matrix,Matrix> doolittle(const Matrix & A){
        Matrix L(A.sizeh(),A.sizeh());
        L.makeIdentity();
        Matrix U(A.sizeh(),A.sizeh());
        U.makeZero();

        for(unsigned int k=0;k<A.sizeh();k++){
            for(unsigned int i=k;i<A.sizeh();i++){
                float sum=0;
                if (k>0)
                    for(unsigned int h=0;h<k;h++){
                        sum+=(L.getRawCell(k,h)*U.getRawCell(h,i));
                    }
                U.setRawCell(k,i,A.getRawCell(k,i)-sum);
            }
            for(unsigned int i=k+1;i<A.sizeh();i++){
                float sum=0;
                if (k>0)
                    for(unsigned int h=0;h<k;h++)
                        sum+=(L.getRawCell(i,h)*U.getRawCell(h,k));
                L.setRawCell(i,k,(A.getRawCell(i,k)-sum)/U.getRawCell(k,k));
            }
        }
        return std::make_tuple(L,U);
    }

    std::tuple<Matrix,std::vector<float>,Matrix> gauss_reduction(Matrix A,std::vector<float> b){

        //NOTE: in this piece of code there are a lot of column/row variable usages with a lot of different combinations.
        //Can be tricky to read.

        Matrix permutation(A.sizeh(),A.sizeh());
        permutation.makeIdentity();
        std::pair<unsigned int, unsigned int> pivot(0,0);
        for(unsigned int column=0;column<A.sizeh()-1;column++){
           for(unsigned int row=column+1;row<A.sizeh();row++){
                bool performGauss=false;
                if (A.getRawCell(column,column)==0){
                    for(unsigned int newRow=row;newRow<A.sizeh();newRow++){
                        if (A.getRawCell(newRow,column)!=0){
                            permutation.swapRows(newRow,row-1);
                            A.swapRows(newRow,row-1);
                            float temp=b[newRow];
                            b[newRow]=b[row-1];
                            b[row-1]=temp;
                            performGauss=true;
                        }
                    }
                }else{
                    performGauss=true;
                }
                if (!performGauss)
                    continue;

                float multiplier=(-1)*A.getRawCell(row,column)/A.getRawCell(column,column);
                for(unsigned int subColumn=column; subColumn<A.sizeh();++subColumn){
                    float coefficient=A.getRawCell(column,subColumn)*multiplier+A.getRawCell(row,subColumn);

                    //DON'T EVEN WATCH THIS PIECE OF CODE. Skip it for your brain health. Just an approximation of very small numbers to 0
                    {
                        double result;
                        int n;
                        result = frexp (coefficient , &n);
                        if (n<-4)
                            coefficient=0;
                    }
                    A.setRawCell(row,subColumn,coefficient);
                }

                b[row]=b[column]*multiplier+b[row];
            }
        }
        return std::make_tuple(A,b,permutation);
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
