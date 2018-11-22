#include<iostream>
#include<cassert>
#ifdef tree_isomorphism

/*
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -

*/


struct node{
	char ch;
	int leftIndex, rightIndex;
	node(char ch, int leftIndex, int  rightIndex){
		this->ch = ch;
		this->leftIndex = leftIndex;
		this->rightIndex = rightIndex;
	}
	node();
};
int fetchIndex(char ch){
	if (ch == '-')
		return -1;
	else
		return ch - '0';
}

node& buildTree(){
	using namespace std;
	int nodeVal;
	cin >> nodeVal;
	node* nodes = new node[nodeVal];
	int* check = new int[nodeVal];
	for (int i = 0; i < nodeVal; i++){
		char ch;
		char leftCh, rightCh;
		int leftIndex, rightIndex;
		cin >> ch; cin.get();
		cin >> leftCh; cin.get();
		cin >> rightCh;
		leftIndex = fetchIndex(leftCh);
		rightIndex = fetchIndex(rightCh);
		nodes[i] = node(ch, leftIndex, rightIndex);
	}
	return *nodes;
}

void solve(){
	using namespace std;
	node tree_a = buildTree();
	node tree_b = buildTree();
	
}


#endif