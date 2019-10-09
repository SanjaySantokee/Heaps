#include <iostream>
#include "DataTypes.h"
#include "MaxHeap.h"
#include "MaxPriorityQueue.h"
   using namespace std;

void heapInsert (Incident A[], int heapSize, Incident newIncident) {
    heapSize++;
    A[heapSize]= newIncident;
    buildMaxHeap(A,heapSize);
}


Incident heapMaximum (Incident A[], int heapSize) {

	if(heapSize == 0){
        A[1].patientID= -1;
        return A[1];
	}
	return A[1];
}


Incident heapExtractMax (Incident A[], int heapSize) {

	Incident maxPatient;

    if (heapSize == 0){
        maxPatient.patientID = -1;
        return maxPatient;
    }
    maxPatient= A[1];
    A[1]= A[heapSize];	
    heapSize--;
    buildMaxHeap(A,heapSize);
	
    return maxPatient;

}


void heapIncreasePriority (Incident A[], int heapSize, int i, int newPriority) {

    if(newPriority < A[i].priority){
        cout<<"Error: New Priority is less than current priority!"<<endl;
        return;
    }

    A[i].priority= newPriority;
    buildMaxHeap(A, heapSize);
    cout<<"Patient's Priority Successfully Altered."<<endl;
}


bool isEmptyHeap (Incident A[], int heapSize) {
    if (heapSize == 0)
        return true;

	return false;
}

int indexOfHeap (Incident A[], int heapSize, int patientID) {

    for(int i=1; i<=heapSize; i++){
        if(patientID == A[i].patientID)
            return i;
    }

    return -1;
}
