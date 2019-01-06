#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "Utility.h"

class pair_hash{
public:
	std::size_t operator()(pair<string,string> p) const{
		return h(p.first)+h(p.second);
	}

private:
	polynomial_hash h;
};

unordered_map<pair<string,string> ,int, pair_hash> pair_count;

int main(int argc, char** argv){
	if (argc<2){
		cout << "Please provide the input_file_name \n";
		return 1;
	}

	string line;
	ifstream inf;
	inf.open(argv[1]);

	int max_sofar = 0; 
	string str1, str2;

	while (getline(inf,line).good()){
		vector<string> tokens;
		Tokenize(line, tokens, " \t");
		pair<string, string> p;

		if (tokens[0]<=tokens[1])
			p = make_pair(tokens[0],tokens[1]);
		else 
			p = make_pair(tokens[1],tokens[0]);
		
		pair_count[p]++;
		if (pair_count[p] > max_sofar){
			max_sofar = pair_count[p];
			str1 = p.first;
			str2 = p.second;
		}	
	}
	inf.close();

	cout << str1 << " and " << str2 << " occoured together most often: #occurance=" << max_sofar << endl;

	return 0;
} 

