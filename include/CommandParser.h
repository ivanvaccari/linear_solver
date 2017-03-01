#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <string>
#include <vector>
#include <list>
class Operation{

public:
    std::string operation;
    std::string operator1;
    std::string operator2;
    std::string target;

};

class CommandParser
{
    private:
        std::list<std::string> matrixesNames;
        std::list<std::string> columnVectorNames;

        bool checkCramer(const std::vector<std::string> & tokens);
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
