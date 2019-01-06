#include <iostream>
#include <vector>
#include "tttboard.h"
#include "gTree.h"
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

int getTurn(vector<int> b){
    int s = 0;
    for (int i=0; i<b.size(); i++)
        s+=b[i];
    if (s==0)
        return 1;
    else 
        return -1;
}

void makeTree (gTNode<tttboard>* T)
{
    int turn = getTurn(T->getData().getBoard());
    vector<tttboard> v = T->getData().possibleNextBoards(turn);
    if (v.size() == 0)
        return;
    else
    {
        for (int i=0; i<v.size(); i++)
        {
            T->addChild(v[i]);
        }
        for (int i=0; i<(T->getChildren().size()); i++)
        {
            makeTree(T->getChildren()[i]);
        }
    }
}

bool isWin(vector<int> board, int mark) {			// is mark the winner? T or F
    int win = 3*mark;				// +3 for X and -3 for O
    return ((board[0] + board[1] + board[2] == win)	    // row 0
            || (board[3] + board[4] + board[5] == win)	    // row 1
            || (board[6] + board[7] + board[8] == win)	    // row 2
            || (board[0] + board[3] + board[6] == win)	    // column 0
            || (board[1] + board[4] + board[7] == win)	    // column 1
            || (board[2] + board[5] + board[8] == win)	    // column 2
            || (board[0] + board[4] + board[8] == win)	    // diagonal
            || (board[2] + board[4] + board[6] == win));	    // diagonal
}

int getWinner(vector<int> board)      // who wins?
{
    int X=1, O=-1, Tie=0;
    if (isWin(board, X)) return X;
    else if (isWin(board, O)) return O;
    else return Tie;
}

void decideBoard (gTNode<tttboard>* T, vector<int> &v)
{
    vector<int> board = T->getData().getBoard();
    int get_winner = getWinner(board);
    if (get_winner==1 || get_winner==-1)
    {
        v.push_back(get_winner);
        return;
    }
    else if (T->getChildren().size() == 0)
    {
        v.push_back(get_winner);
    }
    else
    {
        for (int i=0; i<T->getChildren().size(); i++)
        {
            decideBoard(T->getChildren()[i], v);
        }
    }
    
}

int main(int argc, char** argv)
{
    if(argc == 3)
    {
        int n= atoi(argv[1]);
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
        
        tttboard root(n,board);
        int turn = getTurn(root.getBoard());
        //cout << turn << endl;
        gTree<tttboard> Tree;
        Tree.addNode(root, NULL);
        makeTree(Tree.getRoot());
        
        vector<int> possible_results;
        
        decideBoard(Tree.getRoot(), possible_results);
        
//        cout << possible_results.size() << endl;
//        for (int i=0; i<possible_results.size(); i++)
//            cout << possible_results[i] << " ";
//        cout << endl;
        
        for (int i=0; i<possible_results.size(); i++)
        {
            if (possible_results[i]==turn*-1)
            {
                cout << "winning board" << endl;
                return 0;
            }
            else if (possible_results[i]==0)
            {
                cout << "not sure" << endl;
                return 0;
            }
        }
        cout << "losing board" << endl;
        
        
//        int X=0, O=0;
//        for (int i=0; i<possible_results.size(); i++)
//        {
//            if (possible_results[i]==1)
//            {
//                X++;
//            }
//            if (possible_results[i]==-1)
//            {
//                O++;
//            }
//            else if (possible_results[i]==0)
//            {
//                cout << "not sure" << endl;
//                return 0;
//            }
//        }
//        cout << "hi"<< endl;
//        turn = turn*-1;
//        if (turn == 1 && X>O)
//            cout << "winning board" << endl;
//        else if (turn == -1 && X>O)
//            cout << "losing board" << endl;
//        else if (turn == 1 && O<X)
//            cout << "losing board" << endl;
//        else if (turn == -1 && O>X)
//            cout << "winning board" << endl;
        
        
        return 0;
    }
    else if (argc == 2)
    {
        int n = atoi(argv[1]);
        vector<int> board;
        board.assign(n*n, 0);
        tttboard root(n, board);
        
        gTree<tttboard> Tree;
        Tree.addNode(root, NULL);
        
        makeTree(Tree.getRoot());
        
        cout << "preorder:\n" ;
        preorderPrint(Tree.getRoot());
        cout <<"\npostorder:\n";
        postorderPrint(Tree.getRoot());
        cout << "\nsize:" << size(Tree.getRoot())<< endl;
        return 0;
    }
}




















