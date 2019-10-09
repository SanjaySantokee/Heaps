#include <iostream>
#include "DataTypes.h"
#include "MaxHeap.h"
   using namespace std;

int parent(int i) {
	if(i<=1)
		return -1;
	return i/2;
}

int leftChild(int i) {
	return (i*2);
}

int rightChild (int i) {
	return (i*2)+1 ;
}

void maxHeapify (Incident A[], int heapSize, int i) {

	Incident temp;
	
	int left= leftChild(i);
	int right= rightChild(i);
	
	int largest = i;

	if( (left <= heapSize) && (A[left].priority > A[largest].priority) )
		largest = left;

	else largest = i;

	if(right <= heapSize && (A[right].priority > A[largest].priority))
		largest = right;

	if (largest != i){
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;

		maxHeapify(A, heapSize, largest);

	}
}


void buildMaxHeap(Incident A[], int lengthA) {
	//find parent of last non leaf node
	int heapSize= lengthA;

	for(int lengthA= heapSize/2; lengthA >= 1; lengthA--){
		maxHeapify(A, heapSize, lengthA);
	}

}

void displayHeap (Incident A[], int heapSize) {

	for(int i=1; i<=heapSize; i++)
		cout<<i<<". "<<A[i].priority<<endl;

	return;
}
