#include <iostream>
#include "DataTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

bool containsBST (BTNode * bst, Patient key) {
	
	Patient p;
	
	if (bst == NULL)
		return false;
	
	p = bst->patient;
	
	if (key.patientID == p.patientID)
		return true;
	
	if (key.patientID < p.patientID)
		return containsBST (bst->left, key);
	else
		return containsBST (bst->right, key);
}

BTNode * containsBSTNonRecursive (BTNode * bst, Patient key) {
	
	while (bst != NULL) {
		Patient p = bst->patient;
		if (key.patientID == p.patientID)
			return bst;
		else
		if (key.patientID < p.patientID)
			bst = bst->left;
		else
			bst = bst->right;
	}
	
	return NULL;
}

BTNode * insertBST (BTNode * bst, Patient key) {
	
	BTNode * newNode;
	BTNode * curr;
	
	newNode = createBTNode (key);
	
	if (bst == NULL)
		return newNode;
	
	curr = bst;
	
	while (true) {
		Patient p = curr->patient;
		if (key.patientID < p.patientID) {
			if (curr->left == NULL) {
				curr->left = newNode;
				newNode->parent = curr;
				return newNode;
			}
			curr = curr->left;
		}		
		else {
			if (curr->right == NULL) {
				curr->right = newNode;
				newNode->parent = curr;				
				return newNode;
			}
			curr = curr->right;
		}
	}
}
