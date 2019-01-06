#ifndef   POSTFIXUTILITY_H
#define   POSTFIXUTILITY_H
 
#include <iostream>
#include <vector>
#include "genericLinkedListStack.h"
#include "postfixUtility.h"

using namespace std;


bool is_operator(char c){
        return ((c=='+')||(c=='-')||(c=='*')||(c=='/'));
}

void Tokenize(string expression, vector<string>& tokens){

        string last_int = "";
        // expression has only characters of space, digit, or operator(+-*/)
        for (int i=0; i<expression.size(); i++){
                if ((expression[i]==' ')||(expression[i]=='(')||(expression[i]==')')){ // we may have finished reading an integer  
			if (last_int != ""){
                                tokens.push_back(last_int);
                                last_int = "";
                        }
                }
			
		if (expression[i]==' '){}
		else if (expression[i]=='(')
                        tokens.push_back("(");
                else if (expression[i]==')')
                        tokens.push_back(")");
                else if (is_operator(expression[i])){
                        string one_char_string = " ";
                        one_char_string[0]=expression[i]; // one_char_string now contains the operator

                        // we may have finished reading an integer too
                        if (last_int != ""){
                                tokens.push_back(last_int);
                                last_int = "";
                        }
			tokens.push_back(one_char_string);
                }
                else  // expression[i] is a digit
                        last_int.push_back(expression[i]);
	}
}

string getPostfix(string nexp){
	nexp = "(" + nexp + ")";
	vector<string> items;
	Tokenize(nexp, items);

	genericLinkedListStack<string> stack1, stack2, stack3;

	string aux_str="";

	for (int i=0; i < items.size(); i++){
		if (items[i]!=")")
			stack1.push(items[i]);
		else{
			//cout << "saw ) \n";
			string ready = stack1.top();
			stack1.pop();
			string op = stack1.top(); 
			stack1.pop();

			while (op != "("){
				if ((op=="*")||(op=="/"))
                                	aux_str= ready + " " + op + aux_str;
                        	else if ((op=="+")||(op=="-")){
					aux_str= ready + " " + aux_str;
                                	stack2.push(aux_str);
                                	stack2.push(op);
                                	aux_str="";
                        	}
                        	else
                                	cout << "unexpected op: " << op << endl;
					
				ready = stack1.top();
                        	stack1.pop();
                        	op = stack1.top();
                        	stack1.pop();		
			}
			//cout << "just saw ( \n";

			aux_str= ready + " " + aux_str;
			stack2.push(aux_str);
			aux_str="";

			while (!stack2.isempty()){
				stack3.push(stack2.top());
				stack2.pop();
			}
			;
			ready = stack3.top(); stack3.pop();
			while (!stack3.isempty()){
				op = stack3.top(); stack3.pop();
				aux_str = ready + " " + op + " " + aux_str;
				ready = stack3.top(); stack3.pop();
			}
			aux_str = ready + " " + aux_str;

			stack1.push(aux_str);
			aux_str="";
			
		}
	}

	if (stack1.size()!=1)
		cout << "unexpected stack size : " << stack1.size() << endl;

	return stack1.top();
}

float evaluatePostfix(string pexp){
        genericLinkedListStack<float> s;
        vector<string> tokens;
        Tokenize(pexp, tokens);

        for (int i=0; i<tokens.size(); i++){
                if (is_operator(tokens[i][0])){
                        float first = s.top();
                        s.pop();
                        float second = s.top();
                        s.pop();
                        if (tokens[i]=="+")
                                s.push(second + first);
                        else if (tokens[i]=="-")
                                s.push(second - first);
                        else if (tokens[i]=="*")
                                s.push(second * first);
                        else if (tokens[i]=="/")
                                s.push(second / first);
                }
                else
                        s.push(atof(tokens[i].c_str()));
        }

        return s.top();
}

#endif 
