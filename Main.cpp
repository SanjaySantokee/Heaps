//Sanjay Santokee
//816008051

#include <iostream>
#include "DataTypes.h"
#include "Queue.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "MaxHeap.h"
#include "MaxPriorityQueue.h"
#include <fstream>
using namespace std;

void menu(){
	cout<<"\t Patient Management System \n";
	cout<<"\t --------------------------------------------- \n";
	cout<<"\t 1. Add New Patient to Patient Database \n";
	cout<<"\t 2. Add Patient to Priority Queue \n";
	cout<<"\t 3. Increase Patient Priority \n";
	cout<<"\t 4. Display Information on Next Patient to be Treated \n";
	cout<<"\t 5. Treat Highest Priority Patient \n";
	cout<<"\t 6. Display List of Patients Currently Awaiting Treatment \n";
	cout<<"\t 7. Display List of Patients Already Treated \n";
	cout<<"\t 8. Display List of Patients in Patient Database \n";
	cout<<"\t 9. Quit \n";
	cout<<"\n\n\t Please enter an option: \n";
}

BTNode * readPatients(BTNode * bst){
	ifstream in;
	in.open("Patient.txt");
	
	Patient temp;
	
	if(!in.is_open()){
		cout<<"No Patient file found"<<endl;
		temp.patientID= -9999;
		bst = insertBST(bst, temp);
		return bst;
	}



	while(!in.eof()){
		in>>temp.patientID >> temp.patientName >> temp.phone;
		
		bool check = containsBST(bst, temp);
		
		if(check == false){
			if (bst == NULL)
	            bst = insertBST(bst, temp);
	        else
	            insertBST(bst, temp);
		}
		
		else cout<<"\n\nPatient was already Inserted into Patient Database."<<endl;
		
	}

	cout<<"\n Patient File successfully read \n";

	in.close();
	return bst;
}

int readIncidents(Incident A[], BTNode* bst, int heapSize){
	Incident temp;
	
	if (bst == NULL)
		return -999;
	
	ifstream in;
	in.open("Incident.txt");

	if(!in.is_open()){
		cout<<"No file found"<<endl;
		return -1;
	}

	int i=0, k;

	while(!in.eof()){
		in>>temp.patientID >> temp.condition >> temp.priority;
		
		k= indexOfHeap (A, heapSize, temp.patientID);
		//because a patient can have more than one illness
		if((temp.patientID == A[k].patientID) && (temp.condition == A[k].condition) && (temp.priority == A[k].priority))
			cout<<"Patient with incident has already been inserted in the Priority Queue."<<endl;
		else{
			i++;
			A[i]= temp;
		}
	}

	cout<<"\n Incident File successfully read \n\n";

	in.close();
	return i;
}


BTNode* option1(BTNode * bst, int patientID){
	Patient p;

	p.patientID = patientID;

	cout<<"Please enter the Patient's Name: ";
	cin >> p.patientName;

	cout<<"Please enter the Patient's Telephone Contact: ";
	cin >> p.phone;
	
	bool check = containsBST(bst, p);
	if(check == false){
		if(bst==NULL)
			bst = insertBST(bst, p);
		else
			insertBST(bst, p);
			
		cout<<"\n\nPatient Successfully Inserted into Patient Database."<<endl;
	}
		
	if (check == true) 
		cout<<"\n\nPatient was already Inserted into Patient Database."<<endl;

	return bst;
}

int option2(Incident A[], int heapSize, BTNode* bst, int patientID){
	
	Incident temp;
	temp.patientID = patientID;

	cout<<"Please enter the Patient's Condition: ";
	cin >> temp.condition;

	cout<<"Please enter the Patient's Priority: ";
	cin >> temp.priority;
	
	Patient pTemp;
	pTemp.patientID= temp.patientID;
	int k;
	bool check = containsBST(bst, pTemp);
	if (check==true){
		
		k= indexOfHeap (A, heapSize, pTemp.patientID);
		//because a patient can have more than one illness
		if((temp.patientID == A[k].patientID) && (temp.condition == A[k].condition) && (temp.priority == A[k].priority))
			cout<<"Patient with incident has already been inserted in the Priority Queue."<<endl;
		else{
			heapInsert(A,heapSize,temp);
			heapSize++;
			cout<<"Patient Successfully inserted into Priority Queue."<<endl;
		}
	}
	
	if (check==false){
	cout<<"\nPatient "<<temp.patientID<<" doesnt exist."<<endl;
	cout<<"Please insert this new Patient into the Patient Database using the first option"<<endl;
	}
	
	return heapSize;
}

void option3(Incident A[], int heapSize, BTNode* bst, int patientID){
	Incident temp;
	Patient pTemp;
	int newPriority=0;
	
	temp.patientID = patientID;

	bool check;
	check = containsBST(bst, pTemp);
	
	int i= indexOfHeap (A,heapSize,temp.patientID);
	
	if(check==false && i==-1){
		cout<<"Patient doesnt exist in Patient Database, ";
		cout<<"and therefore doesn't exist in the Priority Queue since they wasn't admitted into the Emergency Department for treatment."<<endl;
		return;
	}
	
	
	if(i == -1){
		cout<<"Patient doesnt exist in Priority Queue since they wasn't admitted into the Emergency Department for treatment."<<endl;
		return;
	}
	
	cout<<"Patient Found in Priority Queue.\n\n";
	cout<<"Please Enter New Priority of Patient "<<temp.patientID<<": ";
	cin>>newPriority;
	heapIncreasePriority(A,heapSize,i,newPriority);
	
}

void option4(Incident A[], int heapSize, BTNode* bst){
	
	Incident temp= heapMaximum(A, heapSize);
	if(temp.patientID == -1){
		cout<<"Priority Queue is Empty."<<endl;
		cout<<"There are no Patients waiting to be treated."<<endl;
		return;
	}
	
	Patient pTemp;
	pTemp.patientID = temp.patientID;
	BTNode *BTtemp =containsBSTNonRecursive(bst, pTemp);
	
	cout<<"\n\nThe highest priority patient on the queue is:- "<<endl;
	cout<<"Patient ID: "<<A[1].patientID<<endl;
	cout <<"Name: " << BTtemp->patient.patientName <<endl;
	cout <<"Telephone: " << BTtemp->patient.phone <<endl;
	cout<<"Condition: "<<temp.condition<<endl;
	cout<<"Priority: "<<temp.priority<<endl<<endl;
	
}

int option5(Incident A[], int heapSize, BTNode* bst, Queue* q){
	
	bool empty= isEmptyHeap(A,heapSize);
		
	if(empty==true && heapSize==0){
		cout<<"Priority Queue is Empty, and therefore no one can be removed."<<endl;
		return -1;
	}
	Incident temp;
	
	temp= heapExtractMax (A, heapSize);
	
	if(temp.patientID == -1)
		return -1;
	
	cout<<"Patient " <<temp.patientID <<" has been treated and removed from the priority queue."<<endl;
	
	enqueue(q,temp);
	return 1;
}

void option6(Incident A[], int heapSize, BTNode* bst){
	
	Patient pTemp;
	Incident temp[100];
	Incident extract;
	BTNode *BTtemp;
	
	if(heapSize <= 0){
		cout<<"No patients waiting to be treated."<<endl;
		return;
	}
	
	for(int i=1; i<= heapSize; i++){
		temp[i] = A[i];
	}
	
	cout<<"Displaying information on all the patients currently waiting to be treated in order of priority: "<<endl<<endl;
	int tempSize= heapSize; //use tempSize becuase I dont want to decrement the loop.
	
	for(int i=1; i<=heapSize; i++){
		
		extract= heapExtractMax (temp, tempSize);
		pTemp.patientID = extract.patientID;
		tempSize--;
		BTtemp = containsBSTNonRecursive(bst, pTemp);
		
		cout << "Patient ID: " << extract.patientID <<endl;
		cout << "Name: " << BTtemp->patient.patientName <<endl;
		cout << "Telephone: " << BTtemp->patient.phone <<endl;
		cout << "Condition: "<< extract.condition <<endl;
		cout << "Priority: "<< extract.priority <<endl;
		cout<<"_________________________________________"<<endl;
	}
}


void option7(Incident A[], Queue *q, int heapSize, BTNode* bst){
	
	QueueNode *curr= q->top;
	Patient pTemp;
	
	if(curr == NULL){
		cout<<"No Patients Have been Treated just yet."<<endl;
		return;
	}
	
	cout<<"Displaying information on all the patients who have already been treated in the order in which they were treated: \n\n";
	cout<<"_________________________________________________________________________________________________________________\n\n";
	while(curr != NULL){
		
		pTemp.patientID= curr->data.patientID;
		BTNode *BTtemp = containsBSTNonRecursive(bst, pTemp);
		if (BTtemp == NULL)
			return;
			
		cout<<"Patient ID: "<< curr->data.patientID <<endl;
		cout << "Name: " << BTtemp->patient.patientName <<endl;
		cout << "Telephone: " << BTtemp->patient.phone <<endl;

		cout<<"_________________________________________"<<endl;
		
		curr = curr->next;
	}
	
}

void option8(BTNode* bst){
	
	if(bst == NULL){
		cout<<"No Patients in Patient Database."<<endl;
		return;
	}
	
	cout<<"Display information on all the patients stored in the patient database in order of Patient ID: "<<endl<<endl;
	cout<<"_______________________________________________________________________________________________"<<endl<<endl;
	inOrderBT(bst);
	cout<<"_______________________________________________________________________________________________"<<endl;
	
}

int main () {

	BTNode * bst = NULL;
	Incident incident[100];
	Queue * q = initQueue();

	bst = readPatients(bst);
	int heapSize=0;
	
	if( bst->patient.patientID == -9999 ){
		cout<<"The Patient File was not found, and therefore a Patient Database does not exist."<<endl<<endl;
		bst= NULL;
	}
	else{
		heapSize = readIncidents(incident,bst,heapSize);
		buildMaxHeap(incident,heapSize);
	}

	
	char option;
	int x, patientID;
	Patient p;

	menu();
	cin >> option;
	cout << "\n";

	while(option!='9'){

	switch(option){
		case '1':
			cout<<"For a new Patient:-"<<endl;
			cout<<"Please enter the Patient's ID: ";
			cin >> patientID;
			if( patientID != 0)
				bst = option1(bst, patientID);
			break;

		case '2':
			cout<<"For a Patient at the Emergency Department for treatment:-"<<endl;
			cout<<"Please enter the Patient's ID: ";
			cin >> patientID;
			if( patientID != 0)
				heapSize= option2(incident, heapSize, bst, patientID);
			break;

		case '3':
			cout<<"Please Enter Patient Id in which you would want to increase the priority of: ";
			cin>>patientID;
			if( patientID != 0)
				option3(incident,heapSize,bst,patientID);
			break;

		case '4':
			option4(incident,heapSize,bst);
			break;

		case '5':
			x= option5(incident,heapSize,bst,q);
			if(heapSize > 0)
				heapSize--;
			break;

		case '6':
			option6(incident,heapSize,bst);
			break;

		case '7':
			option7(incident,q,heapSize,bst);
			break;

		case '8':
			option8(bst);
			break;

		default:
            cout << "--> Error: Invalid option.";
            break;

	}
	cout<<"\n\n\n";

	menu();

	cin >> option;

	cout << "\n";
	}

	return 0;
}
