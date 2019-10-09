#include <iostream>
   using namespace std;

struct Patient {
	int patientID;
	string patientName;
	string phone;
};

struct Incident {
	int patientID;
	string condition;
	int priority;
};
   
struct BTNode {
	Patient patient;
	BTNode * left;
	BTNode * right;
	BTNode * parent;
};

struct QueueNode {
	Incident data;
	QueueNode * next;	
};
