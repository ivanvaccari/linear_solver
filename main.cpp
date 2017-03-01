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
        std::cerr << "This version support these solving algorithms: cramer rule\n" << std::endl;

        return 1;
    }

    std::string fileName;
    for(int i=1;i<argc;i++){
        if (strcmp(argv[i],"-f")==0){
            i++;
            fileName=std::string(argv[i]);
        }
        if (strcmp(argv[i],"-f")==0){
            i++;
            fileName=std::string(argv[i]);
        }
    }

    //matrix and vector cache
    std::map<std::string,Matrix> matrixes;
    std::map<std::string,ColumnVector> columnVectors;

    try{
        CommandParser p;
        p.loadFromFile(fileName);

        if (p.operations.size()==0){
            throw std::string("No operations defined. Stopping here");
        }else{
            //just add target vector into cache to avoid being searched into the definition file.
            //These vector aren't defined i the file, and without this trick the program will halt
            std::list<Operation> operations=p.operations;
            while (!operations.empty()){
                columnVectors[operations.front().target]=ColumnVector();
                operations.pop_front();
            }
        }

        //loading matrixes
        std::list<std::string> matrixNames=p.getMatrixNames();
        while (!matrixNames.empty()){
            Matrix m;
            std::string matrixName=matrixNames.front();
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
                std::cout<<"Solving "<<op.target<<"=cramer("<<op.operator1<<","<<op.operator2<<")..."<<std::endl;
                ColumnVector Xi;
                float d=matrixes[op.operator1].determinant();
                std::vector<float> result=Algorithms::cramer_solve(matrixes[op.operator1],columnVectors[op.operator2].toStdVector(),d);
                columnVectors[op.target]=ColumnVector(result);
                std::cout<<"Result "<<op.target<<":"<<std::endl;
                columnVectors[op.target].print();
            }
        }

    }catch(std::string e){
        //just show the error message before exit
        std::cout <<e;
        return 2;
    }
    return 0;
}
