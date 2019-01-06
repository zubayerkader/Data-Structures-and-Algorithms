#include "tttboard.h"
#include <vector>
#include <iostream>

using namespace std;

tttboard::tttboard(int n)
{
	n_ = n;
	for (int i=0; i<n*n; i++)
		b_.push_back(0);
}

tttboard::tttboard(int n, vector<int> board)
{
    this->n_ = n;
    this->b_ = board;
}

vector<int> tttboard::getBoard() const
{
    return this->b_;
}

vector<tttboard> tttboard::possibleNextBoards(int turn) const
{
	vector<tttboard> children;
	//ToDo for step 2
    for (int i=0; i<n_*n_; i++)
    {
        vector<int> v=b_;
        if(b_[i] == 0)
        {
            v[i]=turn;
            tttboard child(n_, v);
            children.push_back(child);
        }
    }
	return children;
}

bool tttboard::operator==(const tttboard& board) const
{
    return ((this->n_ == board.n_) && (this->b_ == board.b_));
}

ostream& operator<<(ostream& out, const tttboard& board)
{
    cout << "{";
    for (int i=0; i<board.b_.size()-1; i++)
    {
        cout << board.b_[i] << ",";
    }
    cout << board.b_[board.b_.size()-1] << "}";
    return out;
}





