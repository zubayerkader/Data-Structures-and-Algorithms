/*
 * genericLinkedListStack.h
 *
 *  Created on: Oct 6, 2017
 *      Author: Michael Akerman
 */

#ifndef GENERICLINKEDLISTSTACK_H_
#define GENERICLINKEDLISTSTACK_H_

#include <iostream>
using namespace std;


//**********NODE CLASS********
template <typename E>
class SNode{
private:
	E elem;
	SNode<E>*next;

	template<typename T>
	friend class genericLinkedList;
};


//*******LINKED LIST CLASS*******
template <typename E>
class genericLinkedList{
public:
	//housekeeping functions
	genericLinkedList(): head(NULL){}
	~genericLinkedList(){
		while(!isempty())
			removeFront();
	}

	//singly linked list operation functions
	bool isempty() const {
		return (head == NULL);
	}
	const E& top() const {
		return head->elem;
	}
	const E& front() const{
		return head->elem;
	}
	void addFront(const E& e){
		SNode<E>*v = new SNode<E>;
		v->elem = e;
		v->next = head;
		head = v;
	}
	void removeFront(){
		SNode<E>* old = head;
		head = old->next;
		delete old;
	}
	void print(){
		SNode<E>* tmp = head;
		while (tmp != NULL){
			cout << tmp->elem << endl;
			tmp = tmp->next;
		}
	}
private:
	SNode<E>* head;
	template<typename T>
	friend class genericLinkedListStack;
};

//**********STACK CLASS************
template<typename E>
class genericLinkedListStack{
public:
	//housekeeping functions
	genericLinkedListStack(): S(), n(0){}

	//stack operation functions
	int size() const {
		return n;
	}
	bool isempty() const {
		return n==0;
	}
	const E& top() const{
		if(isempty())
			cout << "Top of empty stack" << endl;
		return S.front();
	}
	template<typename T>
	void push(const T& e){
		++n;
		S.addFront(e);
	}
	void pop(){
		if (isempty())
			cout << "Pop from empty stack" << endl;
		--n;
		S.removeFront();
	}
	void print(){
		S.print();
	}
private:
	genericLinkedList<E> S;
	int n;
};







#endif /* GENERICLINKEDLISTSTACK_H_ */

