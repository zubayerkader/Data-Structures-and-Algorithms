#ifndef BINARYSEARCHTREE_H 
#define BINARYSEARCHTREE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "binaryTreeInterface.h"

using namespace std;


template <typename E>
class binarySearchTree:binaryTreeInterface<E>{
  public:
	binarySearchTree():n_(0),N_(0){}

	void addNode(E itm){
		int index = findItem(itm);
		while (valid(index))// if it exists, add it as the right subtree
			index = findItem(itm,rightChildIndex(index)); 

		while(index>=N_){
			tree_data_.push_back(itm);
			isValid_.push_back(false);
			N_++;
		}
		tree_data_[index]= itm;
		isValid_[index]=true;
		n_++;
		
		
	}

	void remove_all(E itm){
		while (remove_one(itm)){
		}
	}

	bool remove_one(E itm){
		int index = findItem(itm);
		if (!valid(index))
			return false;
		remove(index);
		return true;
	}

	bool isEmpty(){return n_==0;}

	int size(){return n_;}

	void preOrderPrint(){preOrderPrint(0);}
	
	void postOrderPrint(){postOrderPrint(0);}

	void inOrderPrint(){inOrderPrint(0);}

	int height(){return height(0);}

  private:
	int height(int i){
		if (!valid(i))
			return -1;
		int h1=height(2*(i+1)-1);
		int h2=height(2*(i+1));
		if (h1>h2)
			return h1+1;
		else
			return h2+1;
	}
	
	void preOrderPrint(int i){
		if (!valid(i))
			return;
		cout << tree_data_[i] << " ";
		preOrderPrint(2*(i+1)-1); //left child
		preOrderPrint(2*(i+1)); //right child
	}

	void inOrderPrint(int i){
                if (!valid(i))
                        return;
                inOrderPrint(2*(i+1)-1); //left child
                cout << tree_data_[i] << " ";
		inOrderPrint(2*(i+1)); //right child
        }

	void postOrderPrint(int i){
                if (!valid(i))
                        return;
                postOrderPrint(2*(i+1)-1); //left child
                postOrderPrint(2*(i+1)); //right child
		cout << tree_data_[i] << " ";
        }

	bool valid(int index){
		if (index >= N_)
			return false;
		return isValid_[index];
	}	
	
	int leftChildIndex(int i){
		return 2*(i+1)-1;
	}

	int rightChildIndex(int i){
		return 2*(i+1);
	}

	int findItem(E itm, int subtree_root_index=0){
		if (!valid(subtree_root_index))
			return subtree_root_index;
		else if (tree_data_[subtree_root_index]==itm)
			return subtree_root_index;
		else if (tree_data_[subtree_root_index]>itm)
			return findItem(itm, leftChildIndex(subtree_root_index));
		else 
			return findItem(itm, rightChildIndex(subtree_root_index));
	}

	// assumes subtree_root_index is valid itself
	int getRightMostIndex(int subtree_root_index){
		if (!valid(rightChildIndex(subtree_root_index)))
			return subtree_root_index;
		else
			return getRightMostIndex(rightChildIndex(subtree_root_index));
	}

	// assumes subtree_root_index is valid itself
        int getLeftMostIndex(int subtree_root_index){
                if (!valid(leftChildIndex(subtree_root_index)))
                        return subtree_root_index;
                else
                        return getLeftMostIndex(leftChildIndex(subtree_root_index));
        }

	// assumes index is valid itself
        void remove(int index){
                int right = rightChildIndex(index);
                int left = leftChildIndex(index);
                if (valid(right)){  // if there is a right child
                        int leftMost = getLeftMostIndex(right);
                        tree_data_[index] = tree_data_[leftMost];
                        remove(leftMost);
                }
                else if (valid(left)){  // if there is only a left child
                        int rightMost = getRightMostIndex(left);
                        tree_data_[index] = tree_data_[rightMost];
                        remove(rightMost);
                }
                else // there are no children
                {
                        isValid_[index] = false;
                        n_--;
                }

        }


	int n_;
	int N_;
	vector<E> tree_data_;
	vector<bool> isValid_;
};


#endif


