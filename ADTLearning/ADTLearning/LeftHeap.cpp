#include<iostream>
using namespace std;

struct TreeNode;//big heap;
typedef struct TreeNode* PriorityQueue;
typedef int elementType;

struct TreeNode{
	elementType element;
	PriorityQueue Left;
	PriorityQueue Right;
	int tpl;
};

PriorityQueue Initialize(int* nums,int size);
PriorityQueue Initialize();
elementType FindMaxium(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);
PriorityQueue MergeHelper(PriorityQueue H1,PriorityQueue H2);
PriorityQueue InsertHelper(elementType X, PriorityQueue H);
PriorityQueue DeleteMaxhelper(PriorityQueue H);
void Destory(PriorityQueue H);
void SwapChildren(PriorityQueue H);

PriorityQueue Initialize(int* nums, int size){
	if (nums == NULL){
		cout << "Null arr!\n";
		return 0;
	}
	if (size == 0)
		return Initialize();
	PriorityQueue H = new TreeNode;
	if (H == NULL){
		cout << "No more space for the heap!" << endl;
		return NULL;
	}
	H->Left = H->Right=NULL;
	H->tpl = 0;
	H->element = nums[0];
	for (int index = 1; index < size; index++){
		H = InsertHelper(nums[index], H);
	}
	return H;
}
PriorityQueue Initialize(){
	PriorityQueue H = new TreeNode;
	H->Left = H->Right = NULL;
	H->tpl = 0;
	return H;
}
void Destory(PriorityQueue H){
	delete H;
}
elementType FindMaxium(PriorityQueue H){
	return H->element;
}
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2){
	if (H1 == NULL)return H2;
	if (H2 == NULL)return H1;
	if (H1->element < H2->element){
		return MergeHelper(H2, H1);
	}
	else
		return MergeHelper(H1, H2);
}
PriorityQueue MergeHelper(PriorityQueue H1, PriorityQueue H2){
	if (H1->Left == NULL){
		H1->Left = H2;
	}
	else{
		H1->Right = Merge(H1->Right, H2);
		if (H1->Left->tpl < H1->Right->tpl){
			SwapChildren(H1);
		}
		H1->tpl = H1->Right->tpl + 1;
	}
	return H1;
}
void SwapChildren(PriorityQueue H){
	if (H == NULL)
		return;
	PriorityQueue tmp = H->Left;
	H->Right = H->Left;
	H->Left = tmp;
}
PriorityQueue InsertHelper(elementType X, PriorityQueue H){
	PriorityQueue singleNode = new TreeNode;
	if (singleNode == NULL){
		cout << "No more space when inserting new nodes!\n";
		return NULL;
	}
	singleNode->Left = singleNode->Right = NULL;
	singleNode->element = X;
	singleNode->tpl = 0;
	H = Merge(H, singleNode);
	return H;
}
PriorityQueue DeleteMaxhelper(PriorityQueue H){
	if (H == NULL){
		cout << "Null pointer!\n";
		return NULL;
	}
	if (H->tpl == 0){
		Destory(H);
		return NULL;
	}
	PriorityQueue leftChild = H->Left;
	PriorityQueue rightChild = H->Right;
	free(H);
	return Merge(leftChild, rightChild);
}