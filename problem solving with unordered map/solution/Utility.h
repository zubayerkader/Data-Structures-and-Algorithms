#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <math.h>


using namespace std;

class sum_of_components_hash{ 
    public:
    std::size_t operator () (const string & str) const;
};


class polynomial_hash{
   public:
   polynomial_hash();

   polynomial_hash(int a):a_(a){}

   std::size_t operator () (const string & str) const;

   private:
	int a_;
};	

class cyclic_hash{
   public:
   cyclic_hash();
   
   cyclic_hash(int sh):sh_(sh){}

   std::size_t operator() (const string & str) const;

   private:
        int sh_;
};

class n_gram;

class n_gram_hash {
    public:
    std::size_t operator () (const n_gram &ng) const;
};

class n_gram{
public:
        n_gram(int n, const vector<string>& v):n_(n), words_(v){}

        bool operator==(const n_gram & rhs) const;

        friend ostream& operator<<(ostream& out, const n_gram& ng);

        friend class n_gram_hash;
private:
        int n_;
        vector<string> words_;

};

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ");

#endif
