#include<iostream>
using namespace std;
#ifdef QUEUE_List
template <class T>
struct Node{
	T val;
	Node* next;
	Node(T& x, Node* p = nullptr) :val(x), next(p){}
};

template <class T>
class QueueList{
private:
	Node<T>* front;
	Node<T>* rear;
	int size;
public:
	QueueList() :size(0){
		int n = 0;
		front = rear = new Node<T>(n);
		rear->next = nullptr;
	}
	QueueList(const QueueList<T>& x){
		if (x.isEmpty()){
			QueueList();
		}
		size = x.size;
		Node<T>* ptr = x.front;
		Node<T>* src = x.front;
		while (ptr != x.rear){
			ptr =new  Node(src->val);
			ptr = ptr->next;
			src = src->next;
		}
		ptr = new Node(src->val);
	}
	bool isEmpty()const{ return size == 0; }
	int getSize()const{ return size; }
	bool enqueue(T& x);
	bool dequeue(T& x);
	void printQueue()const;
};



template <class T>
bool QueueList<T>::enqueue( T& x){
	Node<T> *newNode=new Node<T>(x);
	if (isEmpty()){
		rear = newNode;
		front= rear;
	}
	else{
		newNode->next = rear->next;
		rear->next = newNode;
		rear = newNode;
	}
	size++;
	return true;
}
template <class T>
bool QueueList<T>::dequeue(T& x){
	if (isEmpty())return false;
	Node<T>* ptr = front;
	front = front->next;
	x = ptr->val;
	size--;
	delete ptr;
	return true;
}

template <class T>
void QueueList<T>::printQueue()const{
	Node<T>* ptr = front;
	cout << "front->";
	while (ptr != rear){
		cout << ptr->val << "->";
		ptr = ptr->next;
	}
	cout << ptr->val << "->rear\n";
}
#endif  //QUEUE_LIST
#ifdef QUEUE_ARR
template <class T>
class ArrQueue{
private:
	T * arr;
	int capacity;
	int size;
	int front, rear;
public:
	ArrQueue(const int x = 20){
		front = rear = -1;
		size = 0;
		arr = new T[x];
		capacity = x;
	}
	ArrQueue(const ArrQueue<T>& x);
	bool enqueue(const T& x);
	bool dequeue(T& x);
	bool isEmpty()const{ return size == 0; }
	bool isFull()const{ return size == capacity-1; }
	T getFront()const{ return arr[(front + 1)%capacity ]; }
	T getRear()const{ return arr[rear]; }
	T getSize()const{ return size; }
	T getCapacity()const{ return capacity; }
	void printQueue()const;
};
template <class T>
ArrQueue<T>::ArrQueue(const ArrQueue<T>& x){
	rear = x.rear; front = x.front;
	capacity = x.capacity;
	size = x.capacity;
	arr = new T[capacity];
	for (int i = 0; i < capacity; i++)
		arr[i] = x.arr[i];
}
template <class T>
bool ArrQueue<T>::enqueue(const T& x){
	if (isFull()){
		return false;
	}
	rear = (rear + 1) % capacity;
	arr[rear] = x;
	size++;
	return true;
}
template <class T>
bool ArrQueue<T>::dequeue(T& x){
	if (isEmpty())
		return false;
	x = arr[front];
	front = (front + 1) % capacity;
	size--;
	return true;
}
template <class T>
void ArrQueue<T>::printQueue()const{
	if (isEmpty()){
		cout << "front->rear\n";
		return;
	}
	else if (front>rear){
		cout << "front->";
		for (int i = front+1; i < capacity; i++){
			cout << arr[i] << "->";
		}
		for (int i = 0; i <=rear; i++){
			cout << arr[i] << "->";
		}
		cout << "rear\n";
	}
	else if (front < rear){
		cout << "front->";
		for (int i = front + 1; i <= rear; i++){
			cout << arr[i] << "->";
		}
		cout << "rear\n";
	}
	return;
}
#endif // QUEUE_ARR