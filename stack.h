#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>

template<class T>
class Stack {
	private:
		typedef struct Node {
			T data;
			struct Node* next;
		} node;
		node* top;
		int length;
	public:
		Stack();
		~Stack();
		bool clear_stack();
		bool is_empty();
		bool get_top(T* const elem);
		bool push(T elem);
		T pop();
		bool pop(T* point);
		int stack_length();
		bool get_elem(int position, T* elem);
		bool print_stack();
		bool upside_stack();
};

template<class T>
Stack<T>::Stack() {
	top=0;
	length=0;
}

template<class T>
Stack<T>::~Stack() {
	node* p=top;
	while(top!=0) {
		top=top->next;
		delete p;
		p=top;
	}
}

template<class T>
bool Stack<T>::clear_stack() {
	if (top==0)
		return true;

	node* p=top;
	while(top!=0) {
		delete p;
		top=top->next;
		p=top;
	}
	length=0;
	return true;
	return false;
}

template<class T>
bool Stack<T>::is_empty() {
	if (top==0)
		return true;
	else
		return false;
}

template<class T>
bool Stack<T>::get_top(T* const elem) {
	if (top!=0) {
		*elem=top->data;
		return true;
	}
	return false;
}

template<class T>
bool Stack<T>::push(T elem) {
	if (top==0) {
		node* new_point=new node;
		if (new_point==0)
			return false;
		new_point->data=elem;
		new_point->next=0;
		top=new_point;
		length+=1;
		return true;
	}

	node* new_point1= new node;
	if (new_point1==0)
		return false;

	new_point1->data=elem;
	new_point1->next=top;
	top=new_point1;
	length+=1;
	return true;
}

template<class T>
T Stack<T>::pop() {
	T elem;
	node* p=top;
	top=top->next;
	elem=p->data;
	delete p;
	length-=1;
	return elem;
}

template<class T>
bool Stack<T>::pop(T* point) {
	if (top==0) {
		return false;
	}
	node* p=top;
	top=top->next;
	(*point)=p->data;
	delete p;
	length-=1;
	return true;
}

template<class T>
int Stack<T>::stack_length() {
	return length;
}

template <class T>
bool Stack<T>::print_stack() {
	node* p=top;
	if(p==0)
		return false;

	while(p!=0) {
		std::cout << p->data << ' ';
		p=p->next;
	}
	std::cout << std::endl;
	return true;
}

template<class T>
bool Stack<T>::upside_stack() {
	int l=length;
	T array[l];
	for (int i=0; i<l; i++) {
		if(this->pop(&array[i])==false)
			return false;
	}
	for (int i=0; i<l; i++) {
		if(this->push(array[i])==false)
			return false;
	}
	return true;
}

template<class T>
bool Stack<T>::get_elem(int position, T* const elem) {
	if (position>length||position<=0) {
		return false;
	}

	int i=1;
	node* point=top;
	while(i<position) {
		point=point->next;
		i+=1;
	}
	*elem=point->data;
	return true;
}


#endif