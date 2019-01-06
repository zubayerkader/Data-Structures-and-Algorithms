#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include <string>

using namespace std;

class n_gram{
public:
        n_gram(int n, const vector<string>& v):n_(n), words_(v){}
        vector<string> getArray() const;
        bool operator== (const n_gram& ng) const;
        n_gram& operator= (const n_gram& ng);
        friend ostream& operator<<(ostream& out, const n_gram& ng);
        friend class n_gram_hash;
private:
        int n_;
        vector<string> words_;

};

// class cyclic_hash{
//    public:
//    cyclic_hash();
   
//    cyclic_hash(int sh):sh_(sh){}

//    std::size_t operator() (const string & str) const;

//    private:
//         int sh_;
// };

class n_gram_hash
{
// public:
// 	n_gram_hash();
// 	n_gram_hash();

	public:
    //n_gram_hash();
    size_t operator () (const n_gram& ng) const;
};

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ");

#endif
