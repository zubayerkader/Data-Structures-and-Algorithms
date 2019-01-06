#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "Utility.h"

using namespace std;

int main (int argc, char**argv)
{
    string array = argv[1];
    int input_value = atoi(argv[2]);
    vector<string> tokens;
    Tokenize(array, tokens, " {,}");
    vector<int> input_array;
    
    unordered_map<int, int> um;
    for (int i=0; i<tokens.size(); i++)
    {
        input_array.push_back(atoi(tokens[i].c_str()));
        um[input_array[i]]++;
    }
    
    unordered_map<int, int>::iterator find;
    int i=0;
    for (; i<input_array.size(); i++)
    {
        int x=input_value-input_array[i];
        find = um.find(x);
        if (find != um.end())
            break;
    }
    
    if (find == um.end())
        cout << "answer: " << "(-1,-1)" << endl;
    else
    {
        int j=0;
        for (; j<input_array.size(); j++)
        {
            if (find->first == input_array[j])
                break;
        }
        cout << "answer: " << "(" << i << "," << j << ")" << endl;
    }
    return 0;
}
