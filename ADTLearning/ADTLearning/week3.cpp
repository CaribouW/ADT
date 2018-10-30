#include<iostream>
#include<string>
#define STACK
#define LIST
using namespace std;
#ifdef LIST
struct Node{
	int val;
	Node(int val=0){ this->val=val; }
};

template <class T>
struct ListNode{
	T val;
	ListNode<T>* link;
	ListNode(ListNode<T>*ptr = NULL){ link = ptr; }
	ListNode(const T& item, ListNode<T>* ptr = NULL){
		val = item;
		link = ptr;
	};
};

template <class T>
class List{
protected:
	ListNode<T>* first;
public:
	List(){ first = new ListNode<T>(); }
	List(const T& x){ first = new ListNode<T>(x); }
	List(List<T>& L);
	~List(){ makeEmpty(); }
	void makeEmpty();
	int getLength()const;
	ListNode<T>* getHead(){ return first; }
	ListNode<T>* Search(const T x);     //Get the element node that contains the val of X;
	ListNode<T>* Locate(int order); //Get the node at the order of index(from 1);
	bool getData(int order, T& x)const; //Get the data at the order of index and let the value to the x;
	void setData(int order, T& x);
	bool isEmpty()const{ return first->link == NULL; }
	bool insert(int order, T& x);
	bool Delete(int order, T& x);
};
template <class T>
int List<T>::getLength()const{
	int count = 0;
	ListNode<T>* head = getHead()->link;
	while (head != NULL){
		++count;
		head = head->link;
	}
	return count;
}
template <class T>
List<T>::List(List<T>& L){
	T value;
	ListNode<T>* L_ptr = L.getHead();
	ListNode<T>* dest_ptr = first = new ListNode<T>;
	while (L_ptr->link != NULL){
		value = L_ptr->link->val;
		dest_ptr->link = new ListNode<T>(value);
		L_ptr = L_ptr->link;
		dest_ptr = dest_ptr->link;
	}
}
template <class T>
void List<T>::makeEmpty(){
	ListNode<T>* ptr;
	while (first->link != NULL){
		ptr = first->link;
		first->link = ptr->link;
		delete ptr;
	}
}
template <class T>
ListNode<T>* List<T>::Search(const T x){
	ListNode<T>* head = first;
	while (head->link != NULL){
		T val = head->link->val;
		if (x == val)
			return head->link;
	}
	return NULL;
}
#endif
#ifdef DoubleList
struct DblNode{
	int val;
	DblNode* llink;
	DblNode* rlink;
	DblNode(DblNode* left=NULL, DblNode* right=NULL){ llink = left; rlink = right; }
	DblNode(int val, DblNode* left = NULL, DblNode* right = NULL){
		this->val = val;
		llink = left;
		rlink = right;
	}
};
class DList{
private:
	DblNode* first;
public:
	DList();
	DList(int val){ 
		first = new DblNode(val);
		first->llink = first->rlink = first;
	};
	~DList(){ makeEmpty(); }
	int getLength()const;
	void makeEmpty();
	bool isEmpty(){ return first == first->rlink; }
	bool Delete(const int order,int& x,const int d=0);  //delete the node at the order of i,which begins with 1.
	bool insert(const int order, int& x,const int d=0); //insert the val after the order, which begins with 1.
	DblNode* getHead()const{ return first; }
	DblNode* search(int order)const;
	DblNode* locate(int order, int d=0);//d=0 then find rightwards,and d!=0 then find leftwards.
};
bool DList::Delete(const int order, int& x, const int d = 0){

}
void DList::makeEmpty(){
	DblNode* tmpPtr = first->llink;
	while (tmpPtr != first){
		if (tmpPtr->llink == first){
			first->llink = first->rlink = first;
			delete tmpPtr;
		}
		else{
			DblNode* nextNode = tmpPtr->llink;
			tmpPtr->llink->rlink = tmpPtr->rlink;
			tmpPtr->rlink->llink = tmpPtr->llink;
			delete tmpPtr;
		}
	}
}
int DList::getLength()const{
	DblNode* p = first;
	int count = 0;
	while (p->llink != first){
		count++;
		p = p->llink;
	}
	return count;
}
#endif
#ifdef STACK
class SeqStack{
private:
	int* elements;
	int topIndex;
	int capacity;
public:
	SeqStack(int size = 50){
		elements = new int[size];
		topIndex = -1;
		capacity = size;
	}
	~SeqStack(){ delete[] elements; }
	bool isEmpty()const{ return topIndex == -1; }
	bool isFull()const{ return topIndex == capacity - 1; }
	bool push(int& x);
	bool pop(int& x);
	int getSize()const{ return topIndex + 1; }
	void makeEmpty(){ topIndex = -1; }
};
bool SeqStack::push(int& x){
	if (isFull())return false;
	elements[++topIndex] = x;
	return true;
}
bool SeqStack::pop(int& x){
	if (isEmpty())return false;
	x = elements[topIndex--];
	return true;
}

struct StackNode{
	int val;
	StackNode* next;
	StackNode(StackNode* ptr = NULL){ next = ptr; }
	StackNode(const int& val,  StackNode* ptr = NULL){ this->val = val; next = ptr; }
};
class LinkedStack{
private:
	StackNode* topPtr;
	void destory();
public:
	LinkedStack(){ topPtr = new StackNode(); }
	~LinkedStack(){ destory(); }
	bool push(int& X);
	bool pop(int& X);
	int getTop()const;
	bool isEmpty()const{ return topPtr->next == NULL; }
	void printStack()const;
};

void LinkedStack::destory(){
	while (topPtr->next != NULL){
		StackNode* nextNode = topPtr->next;
		delete topPtr;
		topPtr = nextNode;
	}
}
bool LinkedStack::push(int& x){
	StackNode* node = new StackNode(x);
	node->next = topPtr->next;
	topPtr->next = node;
	return true;
}
bool LinkedStack::pop(int& x){
	if (isEmpty())return false;
	StackNode* node = topPtr->next;
	topPtr->next = node->next;
	x = node->val;
	delete(node);
	return true;
}
int LinkedStack::getTop()const{
	if (isEmpty())return 0;
	else
		return topPtr->next->val;
}
void LinkedStack::printStack()const{
	StackNode* p = topPtr->next;
	if (p == NULL)cout << "empty stack\n";
	else{
		while (p->next != NULL){
			cout << p->val << "->";
			p = p->next;
		}
		cout << p->val << endl;
	}
}
#endif

