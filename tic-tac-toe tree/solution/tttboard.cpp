#include "tttboard.h"
#include <vector>
#include <iostream>

using namespace std;

tttboard::tttboard(int n){
	n_ = n;
	for (int i=0; i<n*n; i++)
		b_.push_back(0);
}

tttboard::tttboard(int n, vector<int> board){
	n_=n;
	b_ = board;
}

bool tttboard::operator==(const tttboard& rhs) const {
	if (n_!=rhs.n_)
		return false;
	if (b_.size() != (rhs.b_).size())
		return false;
	for (int i=0; i< b_.size(); i++)
		if (b_[i]!=rhs.b_[i])
			return false;
	return true;
}


vector<tttboard> tttboard::possibleNextBoards(int turn) const{
	vector<tttboard> children;
	for (int i = 0; i < n_*n_; i++){
		if (b_[i] == 0){
			tttboard child = *this;
               		child.b_[i] = turn;
                        children.push_back(child);
		}
	}
	return children;		
}


bool tttboard::won(int turn){
	for (int i=0; i<n_; i++){ // row i
		int s=0; 
		for (int j=0; j<n_; j++) // column j
			s+=b_[i*n_+j]; 
		if (s==n_*turn)
			return true;
	}

	for (int j=0; j<n_; j++){ // column j
                int s=0; 
                for (int i=0; i<n_; i++) // row i
                        s+=b_[i*n_+j]; 
                if (s==n_*turn)
                        return true;
        }

	int s1 = 0, s2 = 0;
	for (int i=0; i< n_; i++){ // row i
		s1+=b_[i*n_+i];
		s2+=b_[i*n_+(n_-1-i)];	 
	}
	if ((s1==n_*turn)||(s2==n_*turn))
		return true;

	return false;
}

bool tttboard::lost(int turn){
        for (int i=0; i<n_; i++){ // row i
                int s=0; 
                for (int j=0; j<n_; j++) // column j
                        s+=b_[i*n_+j]; 
                if (s==-1*n_*turn)
                        return true;
        }

        for (int j=0; j<n_; j++){ // column j
                int s=0;
                for (int i=0; i<n_; i++) // row i
                        s+=b_[i*n_+j];
                if (s==-1*n_*turn)
                        return true;
        }

        int s1 = 0, s2 = 0;
        for (int i=0; i< n_; i++){ // row i 
                s1+=b_[i*n_+i];
                s2+=b_[i*n_+(n_-1-i)];
        }
        if ((s1==-1*n_*turn)||(s2==-1*n_*turn))
                return true;

        return false;
}

int tttboard::turn(){
        int s = 0;
        for (int i=0; i<b_.size(); i++)
                s+=b_[i];
        if (s==0)
                return 1;
        else
                return -1;
}

ostream & operator<<(ostream& out, tttboard board){
	out << "{";
	int n = board.b_.size();
	for (int i=0; i<n-1; i++)
		out << board.b_[i] << ",";
	if (n>0)
		out << board.b_[n-1];
	out << "}";
	return out;
}

