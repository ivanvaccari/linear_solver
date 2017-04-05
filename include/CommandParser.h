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
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Matrix.h"
#include "ColumnVector.h"
#include "Algorithms.h"

class Operation{

public:
    Operation();
    enum OpType {
        Cramer,
        TriangularSolve,
        GaussReduction,
        Doolittle,
        Print
    };
    OpType type;
    std::vector<std::string> parameters;
    std::vector<std::string> targets;
    void execute(std::map<std::string,Matrix> &matrixes, std::map<std::string,ColumnVector> &columnVectors);
};
class CommandParser
{
    private:
        std::list<std::string> matrixParameters;
        std::list<std::string> columnVectorParameters;
        std::list<std::string> columnVectorTargets;
        std::list<std::string> matrixTargets;
        void checkLoadMatrixFromFile(std::string matrixName);
        void checkLoadColumnVectorFromFile(std::string matrixName);
        bool checkCramer(const std::vector<std::string> & tokens);
        bool checkTriangularSolve(const std::vector<std::string> & tokens);
        bool checkGaussReduction(const std::vector<std::string> & tokens);
        bool checkDoolittle(const std::vector<std::string> & tokens);
        bool checkPrint(const std::vector<std::string> & tokens);
    public:
        CommandParser();
        virtual ~CommandParser();
        std::list<Operation> operations;
        void parseLine(const std::string &line);
        void loadFromFile(const std::string &fileName);
        std::list<std::string> getMatrixesToBeLoaded();
        std::list<std::string> getColumnVectorToBeLoaded();

};

#endif // COMMANDPARSER_H
