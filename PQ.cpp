#include<iostream>
#define LeftChild(i)(2*i+1)
#define Parent(i)((i+1)/2-1)
using namespace std;
struct PriorityHeapNode;
typedef struct PriorityHeapNode* PQ;
typedef int elementType;

struct PriorityHeapNode{
	int size;
	int capacity;
	elementType* elements;
}; //The top of the heap is always the max one of the array.

PQ Heapify(elementType* arr, int size, int capacity);
void PercDown(elementType* arr, int rootIndex, int size);
void PercUp(elementType* arr, int endIndex);
void Insert(PQ P, elementType X);
elementType DeleteMax(PQ P);
void swap(elementType* val_1, elementType* val_2);
void printArr(elementType* arr, int size);
void HeapSort(elementType* arr, int size);

PQ Heapify(elementType* arr, int size, int capacity){
	PQ P = (PQ)malloc(sizeof(struct PriorityHeapNode));
	if (P == NULL){
		cout << "No more space for the heap!\n";
		return NULL;
	}
	P->elements = arr;
	for (int i = size; i < capacity; i++)
		P->elements[i] = 0;
	for (int index = size / 2; index >= 0; index--){
		PercDown(arr, index, size);
	}
	P->size = size;
	P->capacity = capacity;
	return P;
}
void PercDown(elementType* arr, int rootIndex, int size){
	if (rootIndex >= size)
		return;
	int childIndex;
	int headElement = arr[rootIndex];
	for (; LeftChild(rootIndex) < size; rootIndex = childIndex){
		childIndex = LeftChild(rootIndex);
		if (childIndex < size - 1 &&
			arr[childIndex] < arr[childIndex+1])
			childIndex++;
		if (headElement < arr[childIndex]){
			arr[rootIndex] = arr[childIndex];
		}
		else
			break;
	}
	arr[rootIndex] = headElement;
}
void PercUp(elementType* arr, int endIndex){
	if (endIndex == 0)
		return;
	int endElement = arr[endIndex];
	int parentIndex;
	for (; Parent(endIndex)>=0; endIndex = Parent(endIndex)){
		parentIndex = Parent(endIndex);
		if (endElement > arr[parentIndex])
			arr[endIndex] = arr[parentIndex];
		else
			break;
	}
	arr[endIndex] = endElement;
}
void Insert(PQ P, elementType X){
	if (P == NULL){
		cout << "Null pointer!\n";
		return;
	}
	if (P->size == P->capacity){
		cout << "Full Heap!\n";
		return;
	}
	P->elements[P->size++] = X;
	PercUp(P->elements, P->size - 1);
}
elementType DeleteMax(PQ P){
	if (P == NULL || P->size == 0){
		cout << "Null heap!\n";
		return 0;
	}
	int maxElement = P->elements[0];
	swap(&P->elements[0], &P->elements[P->size - 1]);
	PercDown(P->elements, 0, --P->size);
	return maxElement;
}
void swap(elementType* val_1, elementType* val_2){
	int tmp = *val_1;
	*val_1 = *val_2;
	*val_2 = tmp;
}
void printArr(elementType* arr, int size){
	cout << "[";
	for (int index = 0; index < size; index++){
		cout << arr[index] << ',';
	}
	cout << "]\n";
}
void HeapSort(elementType* arr, int size){
	for (int index = size / 2-1; index >= 0; index--)
		PercDown(arr, index, size);
	for (int index = size - 1; index > 0; index--){
		swap(&arr[0], &arr[index]);
		PercDown(arr, 0, index);
	}
}

int main(){
	int arr[] = { 1, 55, 23, 7521, 83, 3412 };
	int size = 6;
	PQ P = Heapify(arr, size, size << 3);
	Insert(P, 9999);
	printArr(P->elements, P->size);
	HeapSort(P->elements, P->size);
	printArr(P->elements, P->size);
	cin.get();
}