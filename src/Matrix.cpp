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
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix():maxColumnNumber(0){
}
Matrix::Matrix(unsigned int rows,unsigned int columns):maxColumnNumber(columns){

    matrixData.resize(rows);
    for(unsigned int i=0;i<rows;i++){
        matrixData[i].resize(columns);
    }
}
void Matrix::print(){
    for(unsigned int i=0;i<matrixData.size();++i){
        for(unsigned int k=0;k<matrixData[i].size();++k){
            std::cout<<matrixData[i][k]<<"\t";
        }
        std::cout<<std::endl;
    }
}
void Matrix::setRawCell(unsigned int row,unsigned int column,float data){
    matrixData[row][column]=data;
}
float Matrix::getRawCell(unsigned int row,unsigned int column){
    return matrixData[row][column];
}
unsigned int Matrix::sizeh(){
    return matrixData.size();
}

float Matrix::diagonalDeterminant(){
    float determinant=1;
    for(unsigned int row=0;row<matrixData.size();++row){
        determinant*=matrixData[row][row];
    }
    return determinant;
}
bool Matrix::isInferiorTriangular(){
    for(unsigned int row=0;row<matrixData.size()-1;++row){
        for(unsigned int column=row+1;column<matrixData.size();++column){
            if (matrixData[row][column]!=0)
                return false;
        }
    }
    return true;
}
bool Matrix::isSuperiorTriangular(){
    for(unsigned int row=0;row<matrixData.size();++row){
        for(unsigned int column=0;column<row;++column){
            if (matrixData[row][column]!=0)
                return false;
        }
    }
    return true;
}
float Matrix::determinant(){

    if(matrixData.size()!=maxColumnNumber){
        throw std::string("Cant calculate determinant. Matrix is not square");
    }else if (maxColumnNumber==2){
        return matrixData[0][0]*matrixData[1][1]-matrixData[0][1]*matrixData[1][0];
    }else{
        float det=0;
        int mul=-1;
        for(unsigned int i=0;i<matrixData.size();++i){
            mul=mul*(-1);
            Matrix min=minor(i,0);
            det+=mul*matrixData[i][0]*min.determinant();
        }
        return det;
    }
}
void Matrix::replaceColumn(unsigned int columnNumber, std::vector<float> newColumn){
    if (matrixData.size()!=newColumn.size())
        throw std::string("Can't replace a column with the one provided. different sizes.");
    if (maxColumnNumber<columnNumber)
        throw std::string("Can't replace a column with the one provided. The matrix don't have this column number.");

    for(unsigned int i=0;i<matrixData.size();++i)
        matrixData[i][columnNumber]=newColumn[i];
}
Matrix Matrix::minor(unsigned int row,unsigned int column){
    Matrix m(matrixData.size()-1,maxColumnNumber-1);
    int offset_column=0;
    int offset_row=0;
    for(unsigned int i=0;i<matrixData.size();++i){
        if (i==row){
            offset_row=-1;
            continue;
        }
        for(unsigned int k=0;k<matrixData[i].size();++k){
            if(k==column){
                offset_column=-1;
                continue;
            }
            m.setRawCell(i+offset_row,k+offset_column,matrixData[i][k]);
        }
    }
    return m;
}
bool Matrix::loadFromFile(const std::string &fileName, const std::string &matrixName){
    bool ret=false;
    std::ifstream file(fileName.c_str());
    std::string matrix_section("[matrix ");
    matrix_section.append(matrixName);
    matrix_section.append("]");
    bool process=false;
    int lineNumber=0;

    if (file.is_open()){
        std::string line;
        while (std::getline(file,line)){
            if (process && line.length()==0){
                process=false;
                ret=true;
                break;
            }else if (process){
                //removing double spaces
                line.append(" ");
                std::string::size_type pos=line.find("  ");
                while(pos!=std::string::npos){
                    line.replace(pos,2," ");
                    pos=line.find("  ");
                }

                pos=line.find(" ");
                std::string::size_type start_pos=0;
                matrixData.push_back(std::vector<float>());
                while(pos!=std::string::npos){
                    std::string num=line.substr(start_pos,pos-start_pos);
                    matrixData[lineNumber].push_back(std::atof(num.c_str()));
                    start_pos=pos+1;
                    pos=line.find(" ",start_pos);
                }
                if (maxColumnNumber<matrixData[lineNumber].size())
                    maxColumnNumber=matrixData[lineNumber].size();
                lineNumber++;
            }else if (line==matrix_section){
                process=true;
            }
        }
        file.close();
        for(unsigned int i=0;i<matrixData.size();++i){
            while (matrixData[i].size()<maxColumnNumber){
                matrixData[i].push_back(0);
            }
        }
    }else{
        throw std::string("Unable to open file.");
    }
    return ret;
}
