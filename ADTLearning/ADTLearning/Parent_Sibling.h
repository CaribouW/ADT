#include<iostream>
template <class T>
struct TreeNode{
	T val;
	TreeNode<T>* first_child, next_sibling;
	TreeNode<T>(T& x){
		val = x;
		first_child = next_sibling = nullptr;
	}
};

template <class T>
class Tree_se{
private:
	TreeNode<T>* root, *current;
	Tree_se<T>(){ root = current = nullptr; }
	bool Find(TreeNode<T>* p, T val);  //Find the val in the tree of root p;
	bool firstChild(TreeNode<T>* root, TreeNode <T>* p);
	bool nextSibling(TreeNode<T>* p);
	bool parent(TreeNode<T>* root, TreeNode<T>* p);
public:
	bool Find(T val){
		TreeNode<T>* p = current;
		if (p == nullptr || current == root){
			current = nullptr;
			return false;
		}
		return Find(p, val);
	}
	bool isEmpty()const{ return root == nullptr; }
	bool firstChild(){
		TreeNode<T>* p = current;
		if (current == nullptr || current->first_child == nullptr){
			current = nullptr;
			return false;
		}
		return firstChild(root, p);
	}
	bool nextSibling(){
		TreeNode<T>* p = current;
		if (current == nullptr || current->next_sibling == nullptr){
			current = nullptr;
			return false;
		}
		return nextSibling(p);
	}
	bool parent(){
		if (current == nullptr || current == root){
			current = nullptr;
			return false;
		}
		return parent(root, current);
	}


};