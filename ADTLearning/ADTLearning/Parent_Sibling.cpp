#include"Parent_Sibling.h"
template <class T>
bool Tree_se<T>::Find(TreeNode<T>* p, T x){
	bool result = false;
	if (p->val == x){ return true; current = p; }
	else{

		TreeNode<T>* child = p->first_child;
		while (child != nullptr && !(result = Find(child, x)){
			child = child->next_sibling;
		}
	}
	return result;
}

template <class T>
bool Tree_se<T>::parent(TreeNode<T>* root, TreeNode<T>* p){
	TreeNode<T>* child = p->first_child;
	bool result = false;
	while (child != nullptr&&child != p){
		if (result = (parent(child, p))return result;
		child = child->next_sibling;
	}
	if (child != nullptr&&child == p){ current = root; return true; }
	else{
		current = nullptr;
		return false;
	}
}

