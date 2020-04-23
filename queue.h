#ifndef GENQUEUE_H_
#define GENQUEUE_H_
#include <iostream>
#include "listnode.h"
using namespace std;

template<typename T>
class GenQueue {

public:
	GenQueue();
	~GenQueue();

	bool isEmpty();
	void insert(T G);
	int getSize();

	T remove();
	T peek();

	 doublyLinkedList<T> *newQueue;

};

//--------------------------------------------

template<typename T>
GenQueue<T>::GenQueue() {
	newQueue = new  doublyLinkedList<T>();
}

template<typename T>
GenQueue<T>::~GenQueue() {
	delete newQueue;
}

template<typename T>
bool GenQueue<T>::isEmpty() {
	return(newQueue->isEmpty());
}

template<typename T>
void GenQueue<T>::insert(T G) {
	newQueue->insertBack(G);
}

template<typename T>
T GenQueue<T>::remove() {
	if(newQueue->isEmpty()) {
		return NULL;
	}
	return(newQueue->removeFront());
}

template<typename T>
T GenQueue<T>::peek() {
	return(newQueue->getFront());
}

template<typename T>
int GenQueue<T>::getSize() {
	return(newQueue->getSize());
}

#endif /* GENQUEUE_H_ */
