#ifndef TTTBOARD_H
#define TTTBOARD_H

#include <iostream>
#include <vector>

using namespace std;

class tttboard{
	public:

		tttboard(int n=3);

		tttboard(int n, vector<int> board);

		bool operator==(const tttboard& rhs) const;		

		vector<tttboard> possibleNextBoards(int turn) const;

		bool won(int turn);

		bool lost(int turn);

		int turn();

		friend ostream & operator<<(ostream& out, tttboard board);

	private:
 		vector<int> b_;
		int n_;	
};

#endif 
