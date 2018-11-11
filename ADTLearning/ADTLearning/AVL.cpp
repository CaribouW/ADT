#include<iostream>
#include<queue>
#define AVL_TREE
#ifdef AVL_TREE
using namespace std;
template <class T>
struct TreeNode{
	T val;
	TreeNode<T>* left, *right;
	int height;

	TreeNode<T>(T& x):left(nullptr),right(nullptr),T(x),height(0){}
};

template <class T>
class AVL_T{
private:
	enum balance
	{balanced,left_left,right_right,
	left_right,right_left};              //indicate the five situations of the balance tree.
	TreeNode<T>* root;
	int NodeCounter;
	void levelOrder(queue<TreeNode<T>*> queue, TreeNode<T>* root, ostream& out)const;
	void destory(TreeNode<T>* root);
	bool insert(TreeNode<T>* root, const T& item);
	bool remove(TreeNode<T>* root, const T& item);
	bool empty()const{ return root == nullptr; }
	TreeNode<T>* findMax(TreeNode<T>* root)const;
	TreeNode<T>* findMin(TreeNode<T>* root)const;
	balance isBalance(TreeNode<T> *root)const;
	TreeNode<T>* singleRotateLeft(TreeNode<T>* root);
	TreeNode<T>* singleRotateRight(TreeNode<T>* root);
	TreeNode<T>* doubleRotateLeft(TreeNode<T>* root);
	TreeNode<T>* doubleRotateRight(TreeNode<T>* root);

public:

	AVL_T<T>(const T& x){
		root = new TreeNode<T>(x);
		NodeCounter = 1;
	}
	AVL_T<T>(const AVL_T<T>* x);
	AVL_T<T>(){
		root = nullptr;
		NodeCounter = 0;
	}
	~AVL_T(){
		destory(root);
	}
	TreeNode<T>* getRoot()const{ return this->root; }
	friend ostream& operator<<(ostream& out, AVL_T<T>& Tree){
		levelOrder(new queue<TreeNode<T>*>, Tree.getRoot(), out);
		return out;
	}
	bool insert(const T& item){ return insert(root, item); }
	bool remove(const T& item){ return remove(root, item); }
};
template <class T>
bool AVL_T<T>::insert(TreeNode<T>* root, const T& item){

}
template <class T>
bool AVL_T<T>::remove(TreeNode<T>* root, const T& item){

}
template <class T>
void AVL_T<T>::destory(TreeNode<T>* root){
	if (root == nullptr)return;
	destory(root->left);
	destory(root->right);
	delete root;
}

template <class T>
TreeNode<T>* AVL_T<T>::findMax(TreeNode<T>* root)const{
	if (root == nullptr){
		return nullptr;
	}
	while (root->right)root = root->right;
	return root;
}
template <class T>
TreeNode<T>* AVL_T<T>::findMin(TreeNode<T>* root)const{
	if (root == nullptr){
		return nullptr;
	}
	while (root->left)root = root->left;
	return root;
}

template <class T>
void AVL_T<T>::levelOrder(queue<TreeNode<T>*> queue, TreeNode<T>* root, ostream& out)const{
	if (root==nullptr){
		out << "empty tree!" << endl;
		return;
	}
	TreeNode<T>* ptr = root;
	queue.push(ptr);
	while (!queue.empty()){
		ptr=queue.front();
		queue->pop();
		out << ptr->val << "(" << ptr->height << ")";
		if(ptr->left)
			queue->push(ptr->left);
		if (ptr->right)
			queue->push(ptr->right);
	}
	out << endl;
}
/**
Return the new root after the rotation

**/

//left_left unbalance
template <class T>
TreeNode<T>* AVL_T<T>::singleRotateLeft(TreeNode<T>* root){
	TreeNode<T>* ptr = root->left;
	root->left = ptr->left;
	ptr->left = root;
	return ptr;
}
//right_right unbalance
template <class T> 
TreeNode<T>* AVL_T<T>::singleRotateRight(TreeNode<T>* root){
	TreeNode<T> ptr = root->right;
	root->right = ptr->right;
	ptr->right = root;
	return ptr;
}
//left_right unbalance
template <class T>
TreeNode<T>* AVL_T<T>::doubleRotateLeft(TreeNode<T>* root){
	root->left = singleRotateRight(root->left);
	return singleRotateLeft(root);
}
//right_left unbalance
template <class T>
TreeNode<T>* AVL_T<T>::doubleRotateRight(TreeNode<T>* root){
	root->right = singleRotateLeft(root->right);
	return singleRotateRight(root->right);
}

#endif

