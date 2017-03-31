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
#include "CommandParser.h"
#include "Tokenizer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>


Operation::Operation(){
    targets.reserve(10);
    parameters.reserve(10);
}
void Operation::execute(std::map<std::string,Matrix> &matrixes, std::map<std::string,ColumnVector> &columnVectors){
    switch(type){
        case Operation::Cramer:{
            if(matrixes.find(parameters[0])==matrixes.end())
                throw std::string("Cannot perform cramer. Undefined matrix ").append(parameters[0]);
            if(columnVectors.find(parameters[1])==columnVectors.end())
                throw std::string("Cannot perform cramer. Undefined columnVector ").append(parameters[0]);

            std::cout<<"Solving "<<targets[0]<<"=cramer("<<parameters[0]<<","<<parameters[1]<<")..."<<std::endl;
            ColumnVector Xi;
            float d=matrixes[parameters[0]].determinant();
            std::vector<float> result=Algorithms::cramer_solve(matrixes[parameters[0]],columnVectors[parameters[1]].toStdVector(),d);
            columnVectors[targets[0]]=ColumnVector(result);
            }
            break;
        case Operation::TriangularSolve:{
            if(matrixes.find(parameters[0])==matrixes.end())
                throw std::string("Cannot perform triangular back substitution. Undefined matrix ").append(parameters[0]);
            if(columnVectors.find(parameters[1])==columnVectors.end())
                throw std::string("Cannot perform triangular back substitution. Undefined columnVector ").append(parameters[0]);

            std::cout<<"Solving "<<targets[0]<<"=triangularSolve("<<parameters[0]<<","<<parameters[1]<<")..."<<std::endl;
            ColumnVector Xi;
            std::vector<float> result=Algorithms::triangular_matrix_solve(matrixes[parameters[0]],columnVectors[parameters[1]].toStdVector());
            columnVectors[targets[0]]=ColumnVector(result);
            }
            break;
         case Operation::GaussReduction:{
            if(matrixes.find(parameters[0])==matrixes.end())
                throw std::string("Cannot perform gauss reduction. Undefined matrix ").append(parameters[0]);
            if(columnVectors.find(parameters[1])==columnVectors.end())
                throw std::string("Cannot perform gauss reduction. Undefined columnVector ").append(parameters[0]);


            std::cout<<"Building reduct system "<<targets[0]<<","<<targets[1]<<","<<targets[2]<<"=gauss("<<parameters[0]<<","<<parameters[1]<<")..."<<std::endl;
            ColumnVector Xi;
            std::tuple<Matrix,std::vector<float>, Matrix> result=Algorithms::gauss_reduction(matrixes[parameters[0]],columnVectors[parameters[1]].toStdVector());
            matrixes[targets[0]]=std::get<0>(result);
            matrixes[targets[2]]=std::get<2>(result);
            columnVectors[targets[1]]=ColumnVector(std::get<1>(result));
            }
            break;
        case Operation::Print:{
            if(columnVectors.find(parameters[0])!=columnVectors.end()){
                std::cout<<"Printing vector "<<parameters[0]<<":"<<std::endl;
                columnVectors[parameters[0]].print();
            }else if(matrixes.find(parameters[0])!=matrixes.end()){
                std::cout<<"Printing matrix "<<parameters[0]<<":"<<std::endl;
                matrixes[parameters[0]].print();
            }else{
                throw std::string("Cannot print undefined variable ").append(parameters[0]);
            }
            }
            break;

    }
}
CommandParser::CommandParser()
{
    //ctor
}

CommandParser::~CommandParser()
{

}
std::list<std::string> CommandParser::getMatrixesToBeLoaded(){
    return matrixParameters;
}
std::list<std::string> CommandParser::getColumnVectorToBeLoaded(){
    return columnVectorParameters;
}
bool CommandParser::checkPrint(const std::vector<std::string> & tokens){
    if (tokens.size()<4)
        return false;
    if (tokens[0]!="print")
        return false ;
    if (tokens[1]!="(")
        return false;
    if (tokens[3]!=")")
        return false;

    Operation op;
    op.parameters.push_back(tokens[2]);
    op.type=Operation::Print;
    operations.push_back(op);

    return true;
}

bool CommandParser::checkCramer(const std::vector<std::string> & tokens){
    if (tokens.size()<8)
        return false;
    if (tokens[1]!="=")
        return false ;
    if (tokens[2]!="cramer")
        return false;
    if (tokens[3]!="(")
        return false;
    if (tokens[5]!=",")
        return false;
    if (tokens[7]!=")")
        return false;

    checkLoadMatrixFromFile(tokens[4]);
    checkLoadColumnVectorFromFile(tokens[4]);

    Operation op;
    op.targets.push_back(tokens[0]);
    columnVectorTargets.push_back(tokens[0]);
    columnVectorParameters.remove(tokens[0]);
    op.parameters.push_back(tokens[4]);
    op.parameters.push_back(tokens[6]);
    op.type=Operation::Cramer;
    operations.push_back(op);

    return true;
}
bool CommandParser::checkTriangularSolve(const std::vector<std::string> & tokens){
    if (tokens.size()<8)
        return false;
    if (tokens[1]!="=")
        return false ;
    if (tokens[2]!="triangularSolve")
        return false;
    if (tokens[3]!="(")
        return false;
    if (tokens[5]!=",")
        return false;
    if (tokens[7]!=")")
        return false;

    checkLoadMatrixFromFile(tokens[4]);
    checkLoadColumnVectorFromFile(tokens[4]);

    Operation op;
    op.targets.push_back(tokens[0]);
    columnVectorTargets.push_back(tokens[0]);
    op.parameters.push_back(tokens[4]);
    op.parameters.push_back(tokens[6]);
    op.type=Operation::TriangularSolve;
    operations.push_back(op);

    return true;
}

void CommandParser::checkLoadMatrixFromFile(std::string matrixName){
    if((std::find(matrixTargets.begin(),matrixTargets.end(),matrixName)==matrixTargets.end()) &&
       (std::find(matrixParameters.begin(),matrixParameters.end(),matrixName)==matrixParameters.end())){
        matrixParameters.push_back(matrixName);
    }


}
void CommandParser::checkLoadColumnVectorFromFile(std::string columnName){
    if((std::find(columnVectorTargets.begin(),columnVectorTargets.end(),columnName)==columnVectorTargets.end())&&
       (std::find(columnVectorParameters.begin(),columnVectorParameters.end(),columnName)==columnVectorParameters.end())){
        columnVectorParameters.push_back(columnName);
    }
}
bool CommandParser::checkGaussReduction(const std::vector<std::string> & tokens){

    if (tokens.size()<9)
        return false;
    if (tokens[1]!=",")
        return false ;
    if (tokens[3]!=",")
        return false ;
    if (tokens[5]!="=")
        return false ;
    if (tokens[6]!="gauss")
        return false ;
    if (tokens[7]!="(")
        return false;
    if (tokens[9]!=",")
        return false;
    if (tokens[11]!=")")
        return false;

    checkLoadMatrixFromFile(tokens[8]);
    checkLoadColumnVectorFromFile(tokens[10]);

    Operation op;
    op.parameters.push_back(tokens[8]);
    op.parameters.push_back(tokens[10]);
    op.type=Operation::GaussReduction;
    op.targets.push_back(tokens[0]);
    op.targets.push_back(tokens[2]);
    op.targets.push_back(tokens[4]);

    matrixTargets.push_back(tokens[0]);
    matrixTargets.push_back(tokens[4]);
    columnVectorTargets.push_back(tokens[2]);

    operations.push_back(op);

    return true;
}
void CommandParser::parseLine(const std::string &line){
    Tokenizer t;
    std::vector<std::string> tokens=t.tokenize(line);
    bool ok=checkCramer(tokens);
    ok=ok||checkTriangularSolve(tokens);
    ok=ok||checkGaussReduction(tokens);
    ok=ok||checkPrint(tokens);
    if (!ok)
        throw std::string("unknow command ").append(line);
}
void CommandParser::loadFromFile(const std::string &fileName){
    std::ifstream file(fileName.c_str());
    std::string command_section("[commands]");
    bool process=false;
    if (file.is_open()){
        std::string line;
        while (std::getline(file,line)){
            if (process && line.length()==0){
                process=false;
                break;
            }else if (process){
                parseLine(line);
            }else if (line==command_section){
                process=true;
            }
        }
        file.close();
    }else{
        throw std::string("Unable to open file.");
    }
}
