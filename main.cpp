#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include "include/Matrix.h"
#include "include/ColumnVector.h"
#include "include/CommandParser.h"
#include "include/Algorithms.h"

int main(int argc, char* argv[]){
    if (argc<2){
        std::cerr << "Linear system " << std::endl;
        std::cerr << "Usage: " << argv[0] << " -f datafile.txt" << std::endl;
        return 1;
    }

    std::string fileName;
    for(int i=1;i<argc;i++){
        if (strcmp(argv[i],"-f")==0){
            i++;
            fileName=std::string(argv[i]);
        }
    }

    std::map<std::string,Matrix> matrixes;
    std::map<std::string,ColumnVector> columnVectors;
    try{
        CommandParser p;
        p.loadFromFile(fileName);

        if (p.operations.size()==0){
            throw std::string("No operations defined. Stopping here");
        }else{
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
            ColumnVector v;
            std::string colVectorName=columnVectorNames.front();
            if (columnVectors.find(colVectorName)!=columnVectors.end()){
                columnVectorNames.pop_front();
                continue;
            }
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
        std::cout <<e;
    }
    return 0;
}
