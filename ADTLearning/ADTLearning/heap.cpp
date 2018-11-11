#include<iostream>
#define HEAP
#define Parent(x)((x)/2)
#define Child(x)(2*x)
#ifdef HEAP
using namespace std;
template <class T>
class Heap{
private:
	T* arr;
	int capacity;
	int size;

public:
	Heap<T>(int maxSize = 20) : size(0), capacity(maxSize){
		arr = new T[capacity + 1];
	}
	Heap<T>(Heap<T>& H){
		capacity = H.capacity;
		size = H.size;
		arr = new T[capacity + 1];
		for (int i = 0; i < capacity + 1; i++){
			arr[i] = H.arr[i];
		}
	}
	bool insert(const T& item);
	bool removeMax(T& x);
	bool empty()const{ return size == 0; }
	bool full()const{ return size == capacity; }
	void scropUp(int endIndex);
	void scropDown(int heapTop, int endIndex);
};

template <class T>
bool Heap<T>::insert(const T& item){
	if (full())return false;
	size++;
	for (int index = size - 1; Parent(index) > 0; index = Parent(x)){
		if (item < arr[Parent(index)])
			break;
		else
			arr[index] = arr[Parent(index)];
	}
	arr[index] = item;
	return true;
}

template <class T>
bool Heap<T>::removeMax(T& x){
	if (empty())return false;
	T maxItem = arr[1];
	int child;
	T last = arr[size--];
	for (int index = 1; Child(index) <= size; index = child){
		child = Child(index);                             //point to the first left child
		if (child + 1 <= size && arr[child + 1] > arr[child])
			child++;
		if (arr[child] < arr[index])break;
		else
			arr[index] = arr[child];
	}
	arr[index] = last;
	x = maxItem;
	return true;
}

template <class T>
void Heap<T>::scropUp(int endIndex){
	T item = arr[endIndex];
	if (endIndex > size){
		cout << "index error" << endl;
		return;
	}
	for (int index = endIndex; Parent(index) > 0 && item > arr[index]; index = Parent(index)){
		arr[index] = arr[Parent(index)];
	}
	arr[index] = item;
}
//From heapTop to endIndex
template <class T>
void Heap<T>::scropDown(int heapTop, int endIndex){
	T item = arr[heapTop];
	if (endIndex > size){
		cout << "index error" << endl;
		return;
	}
	int child;
	for (int index = heapTop; Child(index) <= endIndex; index = child){
		child = Child(index);
		if (child + 1 <= endIndex&&arr[child] < arr[child + 1])
			child++;
		if (item > arr[child])break;
		else
			arr[index] = arr[child];
	}
	arr[index] = item;
}


#endif

