#ifndef TTTBOARD_H
#define TTTBOARD_H

#include <iostream>
#include <vector>

using namespace std;

class tttboard
{
public:
    tttboard(int n=3);
    tttboard(int n, vector<int> board);
    
    vector<int> getBoard() const;
    vector<tttboard> possibleNextBoards(int turn) const;
    bool operator==(const tttboard& board) const;
    friend ostream& operator<< (ostream& out, const tttboard& board);
	
private:
    vector<int> b_;
    int n_;
};

#endif 
