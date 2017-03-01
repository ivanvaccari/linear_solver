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
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <string>
class Matrix
{
private:
    std::vector<std::vector<float> > matrixData;
    int maxColumnNumber;

public:
    Matrix();
    Matrix(int rows,int columns);
    int sizeh();
    void print();
    void setRawCell(int row,int column,float data);
    float determinant();
    void replaceColumn(int columnNumber, std::vector<float> newColumn);
    Matrix minor(int row,int column);
    bool loadFromFile(const std::string &fileName, const std::string &matrixName);
};

#endif // MATRIX_H
