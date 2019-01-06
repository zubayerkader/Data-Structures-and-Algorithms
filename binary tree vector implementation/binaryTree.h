#ifndef BINARYSEARCHTREE_H 
#define BINARYSEARCHTREE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "binaryTreeInterface.h"

using namespace std;


template <typename E>
class binaryTree:binaryTreeInterface<E>{
  public:
	binaryTree(){}

	void addNode(E itm){
		tree_data_.push_back(itm);
	}

	void remove_all(E itm){
		while (remove_one(itm)){
		}
	}

	bool remove_one(E itm){
		for (int i=0; i<tree_data_.size(); i++)
			if (tree_data_[i]==itm){
				tree_data_[i]=tree_data_.back();
				tree_data_.pop_back();
				return true;
			}
		return false;
	}

	bool isEmpty(){return tree_data_.size()==0;}

	int size(){return tree_data_.size();}

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
		if (index >= tree_data_.size())
			return false;
		return true;
	}	
	
	int leftChildIndex(int i){
		return 2*(i+1)-1;
	}

	int rightChildIndex(int i){
		return 2*(i+1);
	}

	vector<E> tree_data_;
};


#endif


