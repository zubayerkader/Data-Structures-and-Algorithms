#include "gTree.h"
#include "tttboard.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t "){
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


void expand(gTree<tttboard>& tttTree, gTNode<tttboard> * p, int turn){
	
	vector<tttboard> nextBoards = p->getData().possibleNextBoards(turn);	
	
	for (int i=0; i<nextBoards.size(); i++){
		tttTree.addNode(nextBoards[i], p);
		expand(tttTree, p->getChildren().back(), turn*-1);
	}
}

string board_label(gTNode<tttboard>* p){
	if (p==NULL)
		return "invalid";
	std::vector<gTNode<tttboard>*> & children = p->getChildren();

	tttboard b = p->getData();

	int turn = b.turn();
	bool won = b.won(turn);
	bool lost = b.lost(turn);

	if (won && lost)
		return "invalid";
	else if (won)
		return "winning board";
	else if (lost)
		return "losing board";
	else if (children.size()==0)
		return "not sure";
			
	bool not_sure_found = false;
	for (int i=0; i<children.size(); i++)
		if (board_label(children[i])=="losing board")
			return "winning board";
		else if (board_label(children[i])=="not sure")
			not_sure_found = true;
	if (not_sure_found)
		return "not sure";
	return "losing board";
}


int main(int argc, char** argv){
	if ((argc!=2) && (argc!=3)){
		cout << "Usage: executable.o n board(optional!)\n";
		return 1;
	}

	int n= atoi(argv[1]);
	gTree<tttboard> tttTree;
        tttboard root(n);
        tttTree.addNode(root, NULL);

        expand(tttTree, tttTree.getRoot(), 1);

	if (argc==2){
        	cout << "pre-order:" << endl;
        	preorderPrint(tttTree.getRoot());
        	cout << endl;
        	cout << "post-order:" << endl;
        	postorderPrint(tttTree.getRoot());
        	cout << endl;
        	cout << "size: " << size(tttTree.getRoot()) << endl;
	}
	if (argc==3){
		string str_board = argv[2];
		vector<string> tokens;
        	Tokenize(str_board,tokens," {,}");
        	vector<int> board;
        	for (int i=0; i<tokens.size(); i++){
                	board.push_back(atoi(tokens[i].c_str()));
        	}
        	if (n*n!= board.size()){
                	cout<< "n and board are not consistent!\n";
                	return 1;
        	}

        	tttboard subtree_root(n,board);		

		cout << board_label(findItem(tttTree.getRoot(), subtree_root)) << endl;
			
	}
	return 0;
}

