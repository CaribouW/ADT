#define Poly
#ifdef Poly
#include<iostream>
using namespace std;
struct PolyNode{
	int val;
	int exp;
	PolyNode* link;
	/**
	*When the exp=-1, the val denotes the number of the nodes in the poly
	*/
	PolyNode(int val, int exp){
		this->val = val;
		this->exp = exp;
		link = nullptr;
	}
};
class PolyNomial{
	/**
	* The exp of the poly is the decreasing order
	*/
public:
	PolyNomial(){ first = new PolyNode(0, -1); }
	~PolyNomial(){ destroy(); }
	friend istream& operator>>(istream& in, PolyNomial& P);
	friend ostream& operator<<(ostream& out, PolyNomial& P);
	void operator+(PolyNomial& P);
	void operator*(PolyNomial& P);
	void destroy();
private:
	PolyNode* first;
};

istream& operator>>(istream& in, PolyNomial& P){
	int val = 0;
	int exp = 0;
	in >> val;
	int counter = val;
	P.first = new PolyNode(val, -1);
	PolyNode* ptr = P.first;
	while (counter > 0 && (in >> val) && (in >> exp)){
		ptr->link = new PolyNode(val, exp);
		ptr = ptr->link;
		counter--;
	}
	return in;
}
ostream& operator<<(ostream& out, PolyNomial& P){
	cout << P.first->val << " ";
	PolyNode* ptr = P.first->link;
	if (ptr == nullptr){
		return out;
	}
	while (ptr->link != nullptr){
		out << ptr->val << " " << ptr->exp << " ";
		ptr = ptr->link;
	}
	out << ptr->val << " " << ptr->exp << " " << endl;
	return out;
}
void PolyNomial::operator+(PolyNomial& P){
	PolyNode* ptr_1 = first->link;
	PolyNode* ptr_2 = P.first->link;
	int size = 0;
	PolyNomial result;
	PolyNode* ptr = result.first;
	while (ptr_1&&ptr_2){
		if (ptr_1->exp > ptr_2->exp){
			ptr->link = new PolyNode(ptr_1->val, ptr_1->exp);
			ptr_1 = ptr_1->link;
		}
		else if (ptr_1->exp < ptr_2->exp){
			ptr->link = new PolyNode(ptr_2->val, ptr_2->exp);
			ptr_2 = ptr_2->link;
		}
		else{
			ptr->link = new PolyNode(ptr_1->val + ptr_2->val, ptr_1->exp);
			ptr_1 = ptr_1->link;
			ptr_2 = ptr_2->link;
		}
		++size;
		ptr = ptr->link;
	}
	while (ptr_1){
		ptr->link = new PolyNode(ptr_1->val, ptr_1->exp);
		ptr_1 = ptr_1->link;
		++size;
	}
	while (ptr_2){
		ptr->link = new PolyNode(ptr_2->val, ptr_2->exp);
		ptr_2 = ptr_2->link;
		++size;
	}
	result.first->val = size;
	cout << result;
}
void PolyNomial::operator*(PolyNomial& P){

}
void PolyNomial::destroy(){
	PolyNode* ptr = first;
	while (ptr != nullptr){
		PolyNode* tmpPtr = ptr;
		delete ptr;
		ptr = tmpPtr;
	}
}

#endif