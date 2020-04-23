#ifndef LISTNODE_H_
#define LISTNODE_H_

#include <iostream>
using namespace std;

template <typename T>

class ListNode {

	public:

		T data;
		ListNode *next;
		ListNode *prev;

		ListNode() {}

		ListNode(T G) { //G is data

			next = NULL;
			prev = NULL;
			data = G;

		}

		~ListNode() {
			if(next != NULL) {
				delete next;
			}
			prev = NULL;
			next = NULL;
		}
};

template<typename T>
class  doublyLinkedList {

public:

	 doublyLinkedList();
	~ doublyLinkedList();

	ListNode<T> *front;
	ListNode<T> *back;

	void insertFront(T G);
	void insertBack(T G);
	int size;
	int Search(T G);
	bool isEmpty();
	void print();
	int getSize();


	T getFront();
	T removeFront();
	T removeBack();
	T remove(T G);
	T deleteAtPos(int pos);

};

template<typename T>
 doublyLinkedList<T>:: doublyLinkedList() {
	size = 0;
	front = NULL;
	back = NULL;

}

template<typename T>
 doublyLinkedList<T>::~ doublyLinkedList() {
	ListNode<T> *curr = front;
	while (size != 0) {
		front = front->next;
		delete curr;
		size--;
	}
}

template<typename T>
bool  doublyLinkedList<T>:: isEmpty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int  doublyLinkedList<T>::getSize() {
	return size;
}

template<typename T>
void  doublyLinkedList<T>::print() {
	ListNode<T> *current = front;
	while(current != NULL) {
		cout << current->data << endl;
		current = current->next;
	}
}

template<typename T>
T  doublyLinkedList<T>::getFront() {
	return front->data;
}

template<typename T>
void  doublyLinkedList<T>::insertFront(T G) {
	ListNode<T> *node = new ListNode<T>(G);
	if(isEmpty()) {
		front = node;
		back = node;
	}
	else {
		node->next = front;
		front->prev = node;
		front = node;
	}
	++size;
}

template<typename T>
void  doublyLinkedList<T>::insertBack(T G) {
	ListNode<T> *node = new ListNode<T>(G);
	if(isEmpty()) {
		front = node;
		back = node;
	}
	else {
		node->prev = back;
		back->next = node;
		back = node;
	}
	++size;
}

template<typename T>
T  doublyLinkedList<T>::removeFront() {

	if(isEmpty()) {
		return NULL;
	}

	ListNode<T> *node = front;
	//check if Empty before Removing
	T temp = front->data;
	if(front->next != NULL) {
		front->next->prev = NULL;
		front = front->next;
	}
	node->next = NULL;
	delete node;
	size--;
	return temp;
}

template<typename T>
T  doublyLinkedList<T>::removeBack() {
	if(isEmpty()) {
		return NULL;
	}
	ListNode<T> *node = back;
	T temp = back->data;
	back->prev->next = NULL;
	back = back->prev;
	node->prev = NULL;
	delete node;
	size--;
	return temp;
}

template<typename T>
T  doublyLinkedList<T>::remove(T G) {
	if(isEmpty()) {
		return NULL;
	}
	ListNode<T> *current = front;
	while(current->data != G) {
		current = current->next;
		if(current == NULL) {
			return NULL;
		}
	}

	if(current == front) {
		front = current->next;
	}

	else {
		current->prev->next = current->next;
	}

	if(current == back) {
		back = current->prev;
	}

	else {
		current->next->prev = current->prev;
	}
	
	current->next = NULL;
	current->prev = NULL;
	T temp = current->data;
	size--;
	delete current;
	return(temp);
}

template<typename T>
T  doublyLinkedList<T>:: deleteAtPos(int pos) {
	ListNode<T> *current = front;

	int index = 0;

	while(index != pos) {
		current = current->next;
		if(current == NULL) {
			return NULL;
		}
		++index;
	}

	if(current == front) {
		front = current->next;
	}
	else {
		current->prev->next = current->next;
	}
	if(current == back) {
		back = current->prev;
	}
	else {
		current->next->prev = current->prev;
	}

	current->next = NULL;
	current->prev = NULL;
	T G = current->data;
	delete current;
	size--;
	return G;
}

template<typename T>
int  doublyLinkedList<T>::Search(T G) {
	int index = -1;
	ListNode<T> *current = front;

	while(current != NULL) {
		if (current->data == G) {
			return (++index);
		}

		current = current->next;
		++index;
	}
	return index;
}

#endif /* LISTNODE_H_ */
