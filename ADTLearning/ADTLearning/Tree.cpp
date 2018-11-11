#include<iostream>
#include<queue>
#include<stack>
using namespace std;
#define BIN_TREE

#ifdef BIN_TREE
template <class T>
struct TreeNode{
	T data;
	TreeNode<T>* left, *right;
	TreeNode<T>() : left(nullptr), right(nullptr){}
	TreeNode<T>(T x, TreeNode<T>* l, TreeNode<T>* r){
		data = x;
		left = l;
		right = r;
	}
};

template <class T>
class BinaryTree{
public:
	friend ostream& operator<<(ostream& out, BinaryTree<T>& tree);
	friend istream& operator>> (istream& in, BinaryTree<T>& tree);
	BinaryTree<T>(){
		root = nullptr;
	}
	BinaryTree<T>(T val){
		root = new TreeNode<T>(val);
	}
	BinaryTree<T>(BinaryTree& s);
	~BinaryTree();

	bool isEmpty()const{ return root == nullptr; }
	BinaryTree<T>* getLeftChild()const{
		return root == nullptr ? root->left : nullptr;
	}
	BinaryTree<T>* getRightChild()const{
		return root == nullptr ? root->right : nullptr;
	}
	int Height()const;
	int Size()const;
	BinaryTree<T>* getRoot()const{ return root; }
	void preOrder()const;
	void inOrder()const;
	void postOrder()const;
	void levelOrder()const;


protected:
	TreeNode<T>* root;
	T RefVal;
	void CreateBinTree(istream& in, TreeNode<T>* & subTree);
	bool Insert(BinaryTree* & subTree, const T & x);
	void destory(TreeNode<T>* & subTree);
};

template <class T>
ostream& operator<<(ostream& out, BinaryTree<T> tree){
	cout << "Binary Tree mode:" << endl;
	TreeNode<T>* root = tree.getRoot();
	if (root == nullptr){
		cout << "empty tree" << endl;
		return out;
	}
	TreeNode<T> p = root;
	queue<TreeNode<T>*>* nodeQueue = new queue();
	nodeQueue->push(root);
	while (!nodeQueue->empty()){
		p = nodeQueue->deque();
		
	}
	return out;
}

template <class T>
istream& operator>>(istream& in, BinaryTree<T> tree){


	return in;
}


#endif