#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include "Utility.h"

using namespace std;

int main()
{
    unordered_map<n_gram,int,n_gram_hash> bigram_counts;
    ifstream inf;
    inf.open("MostOftenPair_input.txt");
    string line;
    //n_gram_hash h;
    unordered_map<n_gram,int,n_gram_hash>::iterator find;
    while (getline(inf,line).good())
    {
        vector<string> tokens;
        Tokenize(line, tokens, " \t");
        n_gram x1 = n_gram(1,{tokens[0]+" "+tokens[1]});
        n_gram x2 = n_gram(1,{tokens[1]+" "+tokens[0]});
        /*for (auto itr=bigram_counts.begin(); itr!=bigram_counts.end(); itr++)
        {
            if (h(itr->first) == h(x))
                x=itr->first;
        }*/
        find = bigram_counts.find(x1);
        if (find != bigram_counts.end())
        {
            bigram_counts[x1]++;
            continue;
        }
        find = bigram_counts.find(x2);
        if(find != bigram_counts.end())
        {
            bigram_counts[x2]++;
            continue;
        }
        else
            bigram_counts[x1]++;
        
        //bigram_counts[x]++;
    }
    inf.close();

    unordered_map<n_gram,int,n_gram_hash>::iterator it=bigram_counts.begin();
    for (auto itr=bigram_counts.begin(); itr!=bigram_counts.end(); itr++)
    {
        //cout << itr->first << " : " << itr->second << endl;
        if (itr->second >= it->second)
            it=itr;
    }
    
    vector<string> n_gram_array = it->first.getArray();
    vector<string> tokens;
    string s = n_gram_array[0];
    Tokenize(s, tokens, " \t");
    
    cout << tokens[0] << " and " << tokens[1] << " occurred together most often: #occurrence=" << it->second << endl;
    return 0;
}
