#include <iostream>
#include <vector>
#include <algorithm>
#include "Utility.h"

using namespace std;

std::size_t sum_of_components_hash::operator () (const string & str) const{

	int s=0;

	for (int i=0; i< str.size(); i++)
		s+=(int)str[i];

	return s;
}


polynomial_hash::polynomial_hash(){
        srand((unsigned)time(0));
        a_ = rand();
        while (a_==0)
                a_ = rand();
        //cout << "chosen a: " <<  a_ << endl;
   }


std::size_t polynomial_hash::operator () (const string & str) const{
	int s=0;

        for (int i=0; i< str.size(); i++)
                s= a_*s + (int)str[i];

        return s;
}

cyclic_hash::cyclic_hash(){
        srand((unsigned)time(0));
        sh_ = rand() % 32;
        while (sh_ ==0)
                sh_ = rand() % 32;
        //cout << "chosen sh: " <<  sh_ << endl;
   }

std::size_t cyclic_hash::operator() (const string & str) const{
	unsigned int s=0;

        for (int i=0; i< str.size(); i++){
		s = (s << sh_) | (s >> (32 - sh_));
                s += (unsigned int)str[i];
	}

        return s;
}


std::size_t n_gram_hash::operator () (const n_gram &ng) const{
        int s = 0;

        for (int i=0; i< ng.n_; i++)
                for (int j=0; j< ng.words_[i].size(); j++)
                s = s + ((int)ng.words_[i][j]);

        return s; 
    }   

ostream& operator<<(ostream& out, const n_gram& ng){
                out << "(";
                for (int i=0; i<ng.n_-1; i++)
                        out << ng.words_[i] << ",";
                out << ng.words_[ng.n_-1]<< ")";
                return out;
        }

bool n_gram::operator==(const n_gram & rhs) const{
                for (int i=0; i<n_; i++)
                        if (words_[i]!=rhs.words_[i])
                                return false;
                return true;
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
