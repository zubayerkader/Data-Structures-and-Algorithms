#include <iostream>
#include <vector>
#include <unordered_map>
#include "Utility.h"

using namespace std;

int main(int argc, char** argv){
	if (argc<3){
		cout << "Please provide the input vector V and the input integer S" << endl;
		return 1;
	}

	string strVec = argv[1];
	int S = atoi(argv[2]);


	vector<string> tokens;
	Tokenize(strVec, tokens, "{,} \t");

	int first_item = 0;
	if (tokens.size()>0)
		first_item = atoi(tokens[0].c_str());		

	unordered_map<int,int> index;
	pair<int, int> answer = make_pair(-1,-1);


	for (int i=0; i< tokens.size(); i++){
		int itm = atoi(tokens[i].c_str());
		index[itm] = i;
		if (first_item==S-itm){
			answer = make_pair(0, i);
			break;
		}
		else{
			int candidate = index[S-itm];
			if (candidate!=0){
				answer = make_pair(candidate, i);
				break;
			}
		}		
	}

	cout << "answer: (" << answer.first << "," << answer.second << ")" << endl; 

	return 0;
}

