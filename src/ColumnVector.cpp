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
#include "ColumnVector.h"
#include <list>
ColumnVector::ColumnVector()
{

}
ColumnVector::ColumnVector(const std::vector<float> &values){
    data=values;
}
ColumnVector::ColumnVector(int rows){
    data.resize(rows,0);
}
int ColumnVector::sizeh(){
    return data.size();
}
void ColumnVector::setRawCell(unsigned int row,float number){
    if (data.size()<=row)
        throw std::string("Can't set raw cell at this row. Vector is smaller.");
    data[row]=number;
}
std::vector<float> ColumnVector::toStdVector(){
    return data;
}

void ColumnVector::print(){
    for(unsigned int i=0;i<data.size();++i){
        std::cout<<data[i]<<std::endl;
    }
}
bool ColumnVector::loadFromFile(const std::string &fileName, const std::string &vectorName){
    bool ret=false;
    std::ifstream file(fileName.c_str());
    std::string vector_section("[colvector ");
    vector_section.append(vectorName);
    vector_section.append("]");
    bool process=false;
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
                if(pos!=std::string::npos){
                    std::string num=line.substr(start_pos,pos-start_pos);
                    data.push_back(std::atof(num.c_str()));
                }
            }else if (line==vector_section){
                process=true;
            }
        }
        file.close();

    }else{
        throw std::string("Unable to open file.");
    }
    return ret;
}
