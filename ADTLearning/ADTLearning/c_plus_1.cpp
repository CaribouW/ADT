#include<iostream>
using namespace std;
#ifdef templateClass
template <typename T>
struct ListNode{
	T val;
	ListNode* link;
	ListNode(const ListNode* link = nullptr){ this->link = link; }
	ListNode(const T val, const ListNode* link = nullptr){ this->val = val; this->link = link; }
};

template <typename T>
class List{
public:
	void run();
};
template <typename T>
void List<T>::run(){
	cout << "tem" << endl;
}

template<>
void List<int>::run(){
	cout << "int" << endl;
}

int main(){
	List<int> l;
	l.run();
	cin.get();
}


#endif
#ifdef transfer
template <typename T>
class house{
private:
	T price;
public:
	house(const T val){ price = val; }
	house(const house& h);
	void doubleParam(int && x);
	operator T()const{ return price; };
};

class ListNode{
	int val;
	ListNode* link;
};

class List{
private:
	ListNode* first;
public:
	List();
	void printList(){ cout << "f" << endl; };
};
class DList :public List{
public:
	void p(){
		printList();
	}
};
#endif
#ifdef extends
class father{
public:
	void p(){ cout << "father" << endl; }
	virtual void v() = 0;
private:
	void pri(){ cout << "pri father" << endl; }
};

class son : public father{
public:
	void p(){ cout << "son" << endl; }
	virtual void print() final{ cout << "as" << endl;}
	void v(){ cout << ""; }
};
#endif
#ifdef friends
class A{
private:
	int pri;
public:
	friend class B;
	void run();
};

class B{
private:
	int Bpri;
	double dou;
public:
	void Brun(){ cout << "Brun" << endl; }
	void set_A(A& a){ a.pri = 3; };
};

void A::run(){
}
#endif
#ifdef exp
class exp_son :public std::exception{
public:
	void run(){
		try{
			expt();
		}
		catch (std::domain_error& x){

		}
		catch (std::out_of_range& x){

		}
		catch (std::bad_exception& x){
		}
		catch (...){

		}
	}
	void expt();
};
void exp_son::expt(){
	throw std::out_of_range("error");
}

#endif

#ifdef str
#include<string>
#include<memory>
int main(){
	auto_ptr<int> p(new int(3));
	shared_ptr<string> str_p(new string());
	str_p->append("java");
	cout << *p << endl;
	cout << str_p.get() << endl;
	cin.get();
}
#endif