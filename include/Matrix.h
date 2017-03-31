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
#include <tuple>
class Matrix
{
private:
    std::vector<std::vector<float> > matrixData;
    unsigned int maxColumnNumber;

public:
    Matrix();
    Matrix(unsigned int rows,unsigned int columns);
    unsigned int sizeh();
    void print();
    void setRawCell(unsigned int row,unsigned int column,float data);
    float getRawCell(unsigned int row,unsigned int column);
    bool isSuperiorTriangular();
    bool isInferiorTriangular();
    float diagonalDeterminant();
    float determinant();
    void makeIdentity();
    void swapRows(unsigned int row1,unsigned int row2);
    void replaceColumn(unsigned int columnNumber, std::vector<float> newColumn);
    Matrix minor(unsigned int row,unsigned int column);
    bool loadFromFile(const std::string &fileName, const std::string &matrixName);
};

#endif // MATRIX_H
