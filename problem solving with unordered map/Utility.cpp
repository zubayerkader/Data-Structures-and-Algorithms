#include <iostream>
#include <vector>
#include <algorithm>
#include "Utility.h"


using namespace std;

vector<string> n_gram::getArray() const
{
    return words_;
}

ostream& operator<<(ostream& out, const n_gram& ng){
                out << "(";
                for (int i=0; i<ng.n_-1; i++)
                        out << ng.words_[i] << ",";
                out << ng.words_[ng.n_-1]<< ")";
                return out;
        }

bool n_gram::operator== (const n_gram& ng) const
{
	/*bool check_words_ = true;
	for (int i=0; i<words_.size(); i++)
	{
		if (words_[i]!=ng.words_[i])
		{
			check_words_ = false;
			break;
		}
	}
	return ((n_==ng.n_) && check_words_);*/

	return ((n_==ng.n_) && (words_==ng.words_));
}

n_gram& n_gram::operator= (const n_gram& ng)
{
    n_=ng.n_;
    words_=ng.words_;
    return *this;
}

void Tokenize(string line, vector<string> & tokens, string delimiters){
	string token = "";
        string OneCharString = " ";
        for (int i=0; i<line.size(); i++)
                if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
                {
                        if (token != "")
                                tokens.push_back(token);
                        token = "";
                }
                else
                {
                        OneCharString[0] = line[i];
                        token +=OneCharString;
                }

        if (token != "")
                tokens.push_back(token);
}

size_t n_gram_hash::operator () (const n_gram& ng) const{

	int s=0;

	for (int i=0; i< ng.words_.size(); i++)
	{
		string a = ng.words_[i];
		for (int j=0; j<a.size(); j++)
			s+=(int)a[j];
	}
	return s;
}
