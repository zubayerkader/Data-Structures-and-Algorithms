#include "postfixUtility.h"

int getPrecedence(char top)
{
    if (top== '+' || top=='-')
        return 1;
    if (top== '*' || top=='/')
        return 2;
    else
        return 3;
}

string getPostfix (string nexp)
{
    string pexp;
    genericLinkedListStack<char> X;
    for (int i=0; i<nexp.length(); i++)
    {
        if (nexp[i]=='(')
            X.push(nexp[i]);
        else if (nexp[i]>='0' && nexp[i]<='9')
        {
            pexp+=nexp[i];
            while (nexp[i+1]>='0' && nexp[i+1]<='9')
            {
                //cout << "1" << endl;
                i++;
                pexp+=nexp[i];
            }
            pexp+=' ';
        }
        else if(nexp[i]=='+' || nexp[i]=='-' || nexp[i]=='*' || nexp[i]=='/')
        {
            while (!X.empty() && getPrecedence(X.top()) >= getPrecedence(nexp[i]) && X.top()!='(')
            {
                //cout << "2" << endl;
                pexp+=X.top();
                X.pop();
            }
            X.push(nexp[i]);
            //X.print();
        }
        else if (nexp[i] == ')')
        {
            while (X.top()!='(' && !X.empty()) /////condition
            {
                //cout << "3" << endl;
                pexp+=X.top();
                X.pop();
            }
            X.pop();
            //X.print();
        }
    }
    //X.print();
    while (!X.empty())
    {
        pexp+=X.top();
        X.pop();
    }
    return pexp;
}

float evaluatePostfix (string pexp)
{
    genericLinkedListStack<float> X;
    for (int i=0; i<pexp.length(); i++)
    {
        float push_val;
        if (pexp[i]>='0' && pexp[i]<='9')
        {
            push_val = pexp[i] - '0';
            while (pexp[i+1]>='0' && pexp[i+1]<='9')
            {
                push_val = push_val*10 + (pexp[i+1] - '0');
                i++;
            }
            X.push(push_val);
        }
        else if (pexp[i] == '-')
        {
            float a = X.top();
            X.pop();
            float b = X.top();
            X.pop();
            X.push(b-a);
        }
        else if (pexp[i] == '*')
        {
            float a = X.top();
            X.pop();
            float b = X.top();
            X.pop();
            X.push(b*a);
        }
        else if (pexp[i] == '+')
        {
            float a = X.top();
            X.pop();
            float b = X.top();
            X.pop();
            X.push(b+a);
        }
        else if (pexp[i] == '/')
        {
            float a = X.top();
            X.pop();
            float b = X.top();
            X.pop();
            X.push(b/a);
        }
    }
    return X.top();
}
