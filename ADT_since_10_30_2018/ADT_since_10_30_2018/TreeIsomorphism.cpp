#include<iostream>
#include<cassert>
#define tree_isomorphism
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


struct TreeNode{
	char ch;
	int leftIndex, rightIndex;
	TreeNode(char ch, int leftIndex, int  rightIndex){
		this->ch = ch;
		this->leftIndex = leftIndex;
		this->rightIndex = rightIndex;
	}
	TreeNode();
};
int fetchIndex(char ch){
	if (ch == '-')
		return -1;
	else
		return ch - '0';
}


void solve(){
	using namespace std;
	int nodeVal;
	for (int k = 0; k < 2; k++){
		cin >> nodeVal;
		TreeNode* nodes = new TreeNode[nodeVal];
		int* check = new int[nodeVal];
		for (int i = 0; i < nodeVal; i++){
			char ch;
			char leftCh, rightCh;
			int leftIndex, rightIndex;
			cin >> ch;cin.get();
			cin >> leftCh;cin.get();
			cin >> rightCh;
			leftIndex = fetchIndex(leftCh);
			rightIndex = fetchIndex(rightCh);
			nodes[i] = TreeNode(ch, leftIndex, rightIndex);
		}
		delete[] nodes;
		delete[] check;
	}
	



	
}


#endif