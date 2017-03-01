#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string>

class Tokenizer
{
    public:
        Tokenizer();
        virtual ~Tokenizer();
        std::vector<std::string> tokenize(const std::string &line);
    private:
        std::string removeSpaces(std::string tmp_token);
};

#endif // TOKENIZER_H
