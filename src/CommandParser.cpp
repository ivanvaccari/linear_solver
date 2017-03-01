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

CommandParser::CommandParser()
{
    //ctor
}

CommandParser::~CommandParser()
{

}
std::list<std::string> CommandParser::getMatrixNames(){
    return matrixesNames;
}
std::list<std::string> CommandParser::getColumnVectorNames(){
    return columnVectorNames;
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

    if (std::find(matrixesNames.begin(),matrixesNames.end(),tokens[4])==matrixesNames.end())
        matrixesNames.push_back(tokens[4]);
    if (std::find(columnVectorNames.begin(),columnVectorNames.end(),tokens[6])==columnVectorNames.end())
        columnVectorNames.push_back(tokens[6]);

    Operation op;
    op.target=tokens[0];
    op.operator1=tokens[4];
    op.operator2=tokens[6];
    op.operation=tokens[2];

    operations.push_back(op);

    return true;
}
void CommandParser::parseLine(const std::string &line){
    Tokenizer t;
    std::vector<std::string> tokens=t.tokenize(line);
    bool ok=checkCramer(tokens);
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
