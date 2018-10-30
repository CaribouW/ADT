#include<iostream>
template <class T>
class GenListNode;

template <class T>
struct Items{
	int utype;
	union{
		int ref;
		T value;
		GenListNode<T>* head_link;
	}info;
	Items() :utype(0), info.ref(0){}
	Items(Items<T>& x){
		utype = x.utype;
		info = x.info;
	}
};

template <class T>
class GenListNode{
	
private:
	int utype;
	GenListNode<T>* tail_link;  //pointer to the next node at the same level.
	union{
		int ref;				//The node's counter.
		T value;				//The value of the data.
		GenListNode<T>* head_link; //The next node of the sub_list.
	}info;
public:
	GenListNode():utype(0), info.ref(0), tail_link(nullptr){}
	GenListNode(GenListNode<T>& x){
		utype = x.utype;
		info = x.info;
		tail_link = x.tail_link;
	}
	bool operator==(GenListNode<T>* l);
};

template <class T>
class GenList{
public:
	GenList();
	~GenList();
	bool Head(Items<T>& item);
	bool Tail(GenList<T>& list);
	GenListNode<T>* First();			//Get the first element;
	GenListNode<T>* Next();				//Get the next element after the list.
	void Copy(GenList<T>& R);
	int Length();						//Ret the length
	int Depth();						//Ret the depth
	friend std::istream& operator>>(std::istream in, GenList<T> R);
private:
	GenListNode<T>* first;				//The head node;
	GenListNode<T>* Copy(GenListNode<T>* ls);
	int Length(GenListNode<T>* ls);
	int Depth(GenListNode<T>* ls);
	void Remove(GenListNode<T>* ls,T x);
	void CreateList(std::istream in, GenList<T>*& ls);
	
};
template <class T>
bool GenListNode<T>::operator==(GenListNode<T>* l){
	int x;
	if (l->tail_link == nullptr&&tail_link == nullptr)return true;
	if (l->tail_link != nullptr&&tail_link != nullptr
		&&tail_link->utype == l->tail_link->utype){
		switch (tail_link->utype)
		{case 1:          //all the normal node
			x = (tail_link->info.value == l->tail_link->info.value);
			break;
		case 2:			// The next node is the head_link
			x = (tail_link->info.head_link == l->tail_link->info.head_link);
			break;
		default:
			break;
		}
		if (x){
			return (tail_link==l->tail_link);
		}
	}
	return false;
}

template <class T>
void GenList<T>::Copy(GenList<T>& R){
	first = Copy(R.first);
}

template <class T>
GenListNode<T>* GenList<T>::Copy(GenListNode<T>* ls){
	GenListNode<T>* result = nullptr;
	if (ls != nullptr){
		result = new GenListNode<T>;
		result->utype = ls->utype;
		switch (ls->utype)
		{
		case 0:
			result->info.ref = ls->info.ref;
			break;
		case 1:
			result->info.value = ls->info.value;
			break;
		case 2:
			result->info.head_link = Copy(ls->info.head_link);
			break;
		default:
			break;
		}
		result->tail_link = Copy(ls->tail_link);
	}
	return result;
}

template <class T>
int GenList<T>::Length(GenListNode<T>* ls){
	if (ls == nullptr)return 0;
	return 1 + Length(ls->tail_link);  //Similar to the linkedList
}

template <class T>
int GenList<T>::Depth(GenListNode<T>* ls){
	if (ls == nullptr)return 0;
	else if (ls->tail_link == nullptr)return 1;
	GenListNode<T>* tmpPtr = ls->tail_link;
	int result = 0;
	while (tmpPtr != nullptr){
		int n;
		if (tmpPtr->utype == 2){
			n = Depth(tmpPtr->info.head_link);
			m = (m > n) ? m : n;
		}
		tmpPtr = tmpPtr->tail_link;  //Move the ptr leftWards.
	}
	return result + 1;
}

template <class T>
void GenList<T>::Remove(GenListNode<T>* ls,T x){
	if (ls->tail_link != nullptr){
		GenListNode<T>* ptr = ls->tail_link;
		for (; ptr != nullptr&&ptr->utype == 1 && ptr->info.value == x;ptr=ls->tail_link){
			ls->tail_link = ptr->tail_link;
			delete ptr;
		}
		if (ptr != nullptr){
			if (ptr->utype == 2)
				Remove(ptr->info.head_link, x);
			Remove(ptr->tail_link, x);
		}
	}
}

template <class T>
bool GenList<T>::Head(Items<T>& item){
	if (first->tail_link == nullptr)
		return false;
	item.info = first->tail_link->info;
	item.utype = first->tail_link->utype;
	return true;
}

template <class T>
bool GenList<T>::Tail(GenList<T>& list){
	if (first->tail_link == nullptr)
		return false;
	list.first->utype = 0;
	list.first->info.ref = 0;
	list.first->tail_link = Copy(first->tail_link->tail_link);
	return true;
}