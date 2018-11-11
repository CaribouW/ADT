#include<iostream>
#include<cstdlib>
using namespace std;

struct Node;
typedef int elementType;
typedef struct Node* PtrToTree;

PtrToTree Initilize(int element);
PtrToTree Insert(int element, PtrToTree T);
PtrToTree Delete(int element, PtrToTree T);
PtrToTree find(int key, PtrToTree T);
void PrePrint(PtrToTree T);
void MiddlePrint(PtrToTree T);
void RearPrint(PtrToTree T);
void LevelPrint(PtrToTree T);
struct Node{
	elementType element;
	PtrToTree left;
	PtrToTree right;
};

PtrToTree Initilize(int element){
	PtrToTree T = new Node;
	if (T == NULL){
		cout << "No more space!\n";
		return NULL;
	}
	T->element = element;
	T->left = T->right = NULL;
	return T;
}
PtrToTree Insert(int element, PtrToTree T){
	if (T == NULL){
		return Initilize(element);
	}
	int val = T->element;
	if (val == element)
		return T;
	else if (val < element)
		T->right=Insert(element, T->right);
	else
		T->left=Insert(element, T->left);
	return T;
}
PtrToTree Delete(int element, PtrToTree T){
	return T;
}

PtrToTree find(int key, PtrToTree T){
	if (T == NULL){
		cout << "Not found!\n";
		return NULL;
	}
	int val = T->element;
	if (val == key)
		return T;
	else if (val < key){
		return find(key, T->right);
	}
	else{
		return find(key, T->left);
	}
}
void PrePrint(PtrToTree T){
	if (T == NULL){
		return;
	}
	cout << T->element << ",";
	PrePrint(T->left);
	PrePrint(T->right);
}
void MiddlePrint(PtrToTree T){
	if (T == NULL){
		return;
	}
	PrePrint(T->left);
	cout << T->element << ",";
	PrePrint(T->right);
}
void RearPrint(PtrToTree T){
	if (T == NULL){
		return;
	}
	PrePrint(T->left);
	PrePrint(T->right);
	cout << T->element << ",";
}
void LevelPrint(PtrToTree T){

}