#include<iostream>
#include<queue>
#include<stack>
#include<cmath>
#define Child(x)((x*2)+1)
#define Father(x)((x-1)/2)
using namespace std;
template <class T>
struct TreeNode{
	T val;
	TreeNode<T> *left, *right;
	TreeNode<T>(const T& x) : left(nullptr), right(nullptr){
		val = x;
	}
	TreeNode<T>(const TreeNode<T>& x){
		val = x.val;
		left = right = nullptr;
	}
};
template <class T>
class BST{
public:
	friend istream& operator>>(istream& in, BST<T>& B);
	friend ostream& operator<<(ostream& out, BST<T>& B);
	TreeNode<T>* leftChild()const{ return root == nullptr ? nullptr : root->left; }
	TreeNode<T>* rightChild()const{ return root == nullptr ? nullptr : root->right; }

	BST(){ root = nullptr; NodeCounter = 0; }

	bool isEmpty(){ return root == nullptr; }
	bool insert(const T& item){
		return insert(root, item);
	}
	bool remove(const T& item){
		return remove(root, item);
	}
	void preOrder(TreeNode<T>* root)const{
		if (root == nullptr)return;
		cout << root->val << ",";
		preOrder(root->left);
		preOrder(root->right);
	}
	void inOrder(TreeNode<T>* root)const{
		if (root == nullptr)return;
		inOrder(root->left);
		cout << root->val << ",";
		inOrder(root->right);
	}
	void postOrder(TreeNode<T>* root)const{
		if (root == nullptr)return;
		postOrder(root->left);
		postOrder(root->right);
		cout << root->val << ",";
	}
	void levelOrder()const{
		levelOrder(new queue<TreeNode<T>*>, root);
	}
	TreeNode<T>* getRoot(){ return root; }
	TreeNode<T> *root;
protected:
	int NodeCounter;
	T RefVal;
	void creatBinTree(istream& in, TreeNode<T>* & subTree); //create the tree
	bool insert(TreeNode<T>* & subTree, const T& x);
	bool remove(TreeNode<T>* & subTree, const T& x);
	bool find(TreeNode<T>* subTree, const T& x)const;
	TreeNode<T> findMax(TreeNode<T>* subTree)const;
	TreeNode<T> findMin(TreeNode<T>* subTree)const;

	void preOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const;  //visit the tree with preorder
	void inOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const;
	void postOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const;
	void levelOrder(queue<TreeNode<T>*>* queue, TreeNode<T>* subTree)const;

	int leafCount(TreeNode<T>* root)const;
	TreeNode<T>* swapChildern(TreeNode<T>* root);
};
BST<int> getInput();
