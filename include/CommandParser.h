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
class Operation{

public:
    Operation():targetIsMatrix(false){
    }
    std::string operation;
    std::string operator1;
    std::string operator2;
    std::string target;
    bool targetIsMatrix;

};

class CommandParser
{
    private:
        std::list<std::string> matrixesNames;
        std::list<std::string> columnVectorNames;

        bool checkCramer(const std::vector<std::string> & tokens);
        bool checkTriangularSolve(const std::vector<std::string> & tokens);
    public:
        CommandParser();
        virtual ~CommandParser();
        std::list<Operation> operations;
        void parseLine(const std::string &line);
        void loadFromFile(const std::string &fileName);
        std::list<std::string> getMatrixNames();
        std::list<std::string> getColumnVectorNames();

};

#endif // COMMANDPARSER_H
