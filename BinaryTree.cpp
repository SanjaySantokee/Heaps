#include <iostream>
#include "DataTypes.h"
#include "BinaryTree.h"

using namespace std;

BTNode * createBTNode (Patient data) {
	BTNode * newNode;
	
	newNode = new BTNode;
	newNode->patient = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	
	return newNode;

}


void displayPatient (Patient p) {
	
	cout << "ID: " << p.patientID << endl;
	cout << "Name: " << p.patientName << endl;
	cout << "Telephone: " << p.phone << endl;
	cout << endl;
}


void visitNode (BTNode * btNode) {
	displayPatient (btNode->patient);
}


void preOrderBT (BTNode * bt) {
	if (bt == NULL)
		return;

	visitNode (bt);		
	preOrderBT (bt->left);
	preOrderBT (bt->right);
}


void inOrderBT (BTNode * bt) {
	if (bt == NULL)
		return;
		
	inOrderBT (bt->left);
	visitNode (bt);
	inOrderBT (bt->right);
}


void postOrderBT (BTNode * bt) {
	if (bt == NULL)
		return;

	postOrderBT (bt->left);
	postOrderBT (bt->right);
	visitNode (bt);		
}


int getHeightBT (BTNode * bt) {
	if (bt == NULL)
		return 0;
		
	int leftHeight, rightHeight;
	
	leftHeight = getHeightBT (bt->left);
	rightHeight = getHeightBT (bt->right);
	
	if (leftHeight > rightHeight)
		return 1 + leftHeight;
	else
		return 1 + rightHeight;
}


int getWeightBT (BTNode * bt) {
	if (bt == NULL)
		return 0;
		
	if (bt->left == NULL && bt->right == NULL)
		return 1;
		
	return getWeightBT (bt->left) + getWeightBT (bt->right);
}
