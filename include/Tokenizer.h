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
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string>

/*! \brief The tokenizer class is a multi-token tokenizer.
           The class create a list of tokens by splitting an input string when one of the specified delimiter is found.
           */

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
