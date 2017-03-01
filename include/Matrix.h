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
