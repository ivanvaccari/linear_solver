#include "Tokenizer.h"
#include <cstring>

Tokenizer::Tokenizer()
{
    //ctor
}

Tokenizer::~Tokenizer()
{
    //dtor
}

std::string Tokenizer::removeSpaces(std::string tmp_token){

    size_t remove_pos=tmp_token.find(" ");
    while (remove_pos!=std::string::npos){
        tmp_token.erase(remove_pos,1);
        remove_pos=tmp_token.find(" ");
    }
    return tmp_token;
}
std::vector<std::string> Tokenizer::tokenize(const std::string &line){

    std::vector<std::string> tokens;
    char * input = new char [line.length()+1];
    std::strcpy (input, line.c_str());

    int max_delim_count=4;
    char delimiters[max_delim_count][2];
    strcpy(delimiters[0],"=");
    strcpy(delimiters[1],",");
    strcpy(delimiters[2],"(");
    strcpy(delimiters[3],")");

    char *string_last_match_pos=input;
    char *string_curr_pos=input;

    while (string_curr_pos[0]!='\0'){
        char *minimum_match_pos=input+strlen(input);
        int minimum_match_length=0;
        for(int i=0;i<max_delim_count;i++){
            int delim_len=strlen(delimiters[i]);
            if (strncmp(string_curr_pos,delimiters[i],delim_len)==0){
                if (minimum_match_pos>string_curr_pos){
                    minimum_match_pos=string_curr_pos;
                    minimum_match_length=delim_len;
                }
            }
        }
        if (minimum_match_length>0){
            //will crash with strings longer than 200. don't care for now.
            char tmp[200];
            if (minimum_match_pos-string_last_match_pos>0){
                memset(tmp,0,200);
                strncpy(tmp,string_last_match_pos,minimum_match_pos-string_last_match_pos);
                tokens.push_back(removeSpaces(std::string(tmp)));

            }
            memset(tmp,0,200);
            strncpy(tmp,minimum_match_pos,minimum_match_length);

            tokens.push_back(removeSpaces(std::string(tmp)));

            string_last_match_pos=minimum_match_pos+1;
            string_curr_pos=minimum_match_pos+1;
        }else{
            string_curr_pos++;
        }
    }
    return tokens;
}
