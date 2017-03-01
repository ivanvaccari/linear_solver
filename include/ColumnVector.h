#ifndef COLUMNVECTOR_H
#define COLUMNVECTOR_H
#include <vector>
#include <string>

class ColumnVector
{
    private:
        std::vector<float> data;
    public:
        ColumnVector();
        ColumnVector(int rows);
        ColumnVector(const std::vector<float> &values);
        int sizeh();
        void print();
        void setRawCell(int row,float data);
        std::vector<float> toStdVector();
        bool loadFromFile(const std::string &fileName, const std::string &vectorName);

};

#endif // COLUMNVECTOR_H
