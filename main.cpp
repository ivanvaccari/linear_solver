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
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <cstdio>
#include <ctime>
#include "include/Matrix.h"
#include "include/ColumnVector.h"
#include "include/CommandParser.h"
#include "include/Algorithms.h"

int main(int argc, char* argv[]){

    //checking command line parameters
    if (argc<2){
        std::cerr << "Linear system solver.\nA simple linear system solver for learning purposes.\n" << std::endl;
        std::cerr << "Usage: " << argv[0] << " -f datafile.txt\n" << std::endl;
        std::cerr << "Parameter list\n -h  Show a small man page\n -f  Specify the input definition file\n" << std::endl;
        std::cerr << "This version support these solving algorithms: cramer rule, triangular rule\n" << std::endl;
        return 1;
    }

    std::string fileName;
    for(int i=1;i<argc;i++){
        if (strcmp(argv[i],"-f")==0){
            i++;
            fileName=std::string(argv[i]);
        }
        if (strcmp(argv[i],"-h")==0){
            //print a help then exit
            std::cerr << "Linear system solver.\nA simple linear system solver for learning purposes.\n" << std::endl;
            std::cerr << "Definition file syntax" << std::endl;
            std::cerr << "-Define a matrix\n [matrix NAME]\n a11 a12 a13 ... a1n\n a21 a22 a23 ... a2n\n ... ... ... ... ...\n an1 an2 an3 ... ann\n\n\n-Define a column vector\n[colvector name]\n a1\n a2\n ...\n an\n\n\n-Define commands\n[commands]\ntargetname1=cramer(MATRIXNAME1,colvectorname1)\ntargetname2=cramer(MATRIXNAME2,colvectorname2)\n...\n\n\nEach definition section must be separated by an empty line\n" << std::endl;
            return 1;
        }
    }

    //matrix and vector cache. Key is the name of the matrix/vector, value is
    //the effective object. Just like a couple name and data
    std::map<std::string,Matrix> matrixes;
    std::map<std::string,ColumnVector> columnVectors;

    try{
        CommandParser p;
        p.loadFromFile(fileName);

        if (p.operations.size()==0){
            throw std::string("No operations defined. Stopping here");
        }else{
            //just add target vector into cache to avoid being searched into the definition file.
            //These vector aren't defined in the file, and without this trick the program will halt
            std::list<Operation> operations=p.operations;
            while (!operations.empty()){
                if (!operations.front().targetVector.empty())
                    columnVectors[operations.front().targetVector]=ColumnVector();

                if (!operations.front().targetMatrix.empty())
                    matrixes[operations.front().targetMatrix]=Matrix();

                operations.pop_front();
            }
        }

        //loading matrixes
        std::list<std::string> matrixNames=p.getMatrixNames();
        while (!matrixNames.empty()){
            std::string matrixName=matrixNames.front();
            if (matrixes.find(matrixName)!=matrixes.end()){
                matrixNames.pop_front();
                continue;
            }
            Matrix m;

            if (!m.loadFromFile(fileName,matrixName))
                throw std::string("Can't load matrix ").append(matrixName).append(". Matrix not defined");
            else
                std::cout<<"Matrix "<<matrixName<<" loaded"<<std::endl;
            matrixes[matrixName]=m;
            matrixNames.pop_front();
        }

        //loading vectors
        std::list<std::string> columnVectorNames=p.getColumnVectorNames();
        while (!columnVectorNames.empty()){
            std::string colVectorName=columnVectorNames.front();
            //in the case the vector is already  in cache, do not load it from file
            if (columnVectors.find(colVectorName)!=columnVectors.end()){
                columnVectorNames.pop_front();
                continue;
            }
            ColumnVector v;
            if (!v.loadFromFile(fileName,colVectorName))
                throw std::string("Can't load column vector ").append(colVectorName).append(". Column vector not defined");
            else
                std::cout<<"Column vector "<<colVectorName<<" loaded"<<std::endl;
            columnVectors[colVectorName]=v;
            columnVectorNames.pop_front();
        }

        //running commands
        while (!p.operations.empty()){
            Operation op=p.operations.front();
            p.operations.pop_front();
            if (op.operation=="cramer"){
                std::cout<<std::endl;
                std::cout<<"Solving "<<op.targetVector<<"=cramer("<<op.operatorMatrix<<","<<op.operatorVector<<")..."<<std::endl;
                ColumnVector Xi;
                float d=matrixes[op.operatorMatrix].determinant();
                std::vector<float> result=Algorithms::cramer_solve(matrixes[op.operatorMatrix],columnVectors[op.operatorVector].toStdVector(),d);
                columnVectors[op.targetVector]=ColumnVector(result);

            }else if (op.operation=="triangularSolve"){
                std::cout<<std::endl;
                std::cout<<"Solving "<<op.targetVector<<"=triangolarSolve("<<op.operatorMatrix<<","<<op.operatorVector<<")..."<<std::endl;
                ColumnVector Xi;
                std::vector<float> result=Algorithms::triangular_matrix_solve(matrixes[op.operatorMatrix],columnVectors[op.operatorVector].toStdVector());
                columnVectors[op.targetVector]=ColumnVector(result);

            }else if (op.operation=="gauss"){
                std::cout<<std::endl;
                std::cout<<"Building reduct system gauss("<<op.operatorMatrix<<","<<op.operatorVector<<")..."<<std::endl;
                ColumnVector Xi;
                std::pair<Matrix,std::vector<float> > result=Algorithms::gauss_reduction(matrixes[op.operatorMatrix],columnVectors[op.operatorVector].toStdVector());
                matrixes[op.targetMatrix]=result.first;
                columnVectors[op.targetVector]=ColumnVector(result.second);

            }else if (op.operation=="print"){
                if(columnVectors.find(op.operatorVector)!=columnVectors.end()){
                    std::cout<<"Printing vector "<<op.operatorVector<<":"<<std::endl;
                    columnVectors[op.operatorVector].print();
                }else if(matrixes.find(op.operatorMatrix)!=matrixes.end()){
                    std::cout<<"Printing matrix "<<op.operatorMatrix<<":"<<std::endl;
                    matrixes[op.operatorMatrix].print();
                }
            }
        }

    }catch(std::string e){
        //just show the error message before exit
        std::cout <<e;
        return 2;
    }
    return 0;
}
