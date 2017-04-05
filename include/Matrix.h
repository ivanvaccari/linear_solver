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

/*!
    \brief  This class manage a matrix

*/
class Matrix
{
private:
    std::vector<std::vector<float> > matrixData;
    unsigned int maxColumnNumber;

public:
    Matrix();
    Matrix(unsigned int rows,unsigned int columns);

    /*!
        \brief  Return the height of the matrix
        \return The height of the matrix
    */
    unsigned int sizeh() const;

    /*!
        \brief  print to stdout a well-formatted matrix
    */
    void print();

    /*!
        \brief Insert a value into the specified position
        \param row The row , starting from 0 where we want to place the value
        \param column The column , starting from 0 where we want to place the value
        \param value The value we want to place into the matrix
    */
    void setRawCell(unsigned int row,unsigned int column,float value);

    float getRawCell(unsigned int row,unsigned int column) const;
    bool isSuperiorTriangular();
    bool isInferiorTriangular();
    float diagonalDeterminant();
    float determinant();

    /*!
        \brief Make this matrix an identity matrix, by setting all zero's into the matrix except the diagonal ones.
    */
    void makeIdentity();
    /*!
        \brief Make this matrix a zero matrix by setting all the elements to 0
    */
    void makeZero();

    /*!
        \brief Swap two rows.
        \param row1 The first index of the row we want to swap
        \param row2 The second index of the row we want to swap
    */
    void swapRows(unsigned int row1,unsigned int row2);

    void replaceColumn(unsigned int columnNumber, std::vector<float> newColumn);
    Matrix minor(unsigned int row,unsigned int column);
    bool loadFromFile(const std::string &fileName, const std::string &matrixName);
};

#endif // MATRIX_H
