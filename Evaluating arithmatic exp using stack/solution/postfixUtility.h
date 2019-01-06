#ifndef   POSTFIXUTILITY_H
#define   POSTFIXUTILITY_H
 
#include <vector>


bool is_operator(char c);

void Tokenize(std::string expression, std::vector<std::string>& tokens);

std::string getPostfix(std::string nexp);

float evaluatePostfix(std::string pexp);

#endif 
