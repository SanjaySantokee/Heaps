#include <iostream>
#include <cstdlib>
#include "DataTypes.h"
#include "Queue.h"

using namespace std;


Queue * initQueue () {
	Queue * q = new Queue;
	q->top = NULL;
	q->last = NULL;
	return q;
}


bool isEmptyQueue (Queue * q) {
	if (q->top == NULL)
		return true;
	else
		return false;		
}


int sizeQueue (Queue * q) {

	QueueNode * curr;
	int size;

	curr = q->top;	
	size = 0;
	
	while (curr != NULL) {
		curr = curr->next;
		size = size + 1;
	}
	
	return size;
}

void enqueue (Queue * q, Incident data) {
	QueueNode * newElement = new QueueNode;
	newElement->data = data;
	newElement->next = NULL;
	
	if (isEmptyQueue(q)) {
		q->top = newElement;
		q->last = newElement;
	}
	else {
		q->last->next = newElement;
		q->last = newElement;
	}
}


Incident dequeue (Queue * q) {

	QueueNode * toRemove;
	Incident data;

	if (isEmptyQueue(q)) {
		data.patientID = -1;		// to indicate error if dequeuing from an empty queue
		return data;
	}
	
	toRemove = q->top;
	data = toRemove->data;
	q->top = toRemove->next;
	if (q->top == NULL)
		q->last = NULL;
		
	delete toRemove;
	
	return data;
}
