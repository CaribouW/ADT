#include"BST.h"
#define BST_
#ifdef BST_

template <class T>
istream& operator>>(istream& in, BST<T>& B){
	queue<TreeNode<int>*> q;
	char input_str[1024];
	in >> input_str;
	TreeNode<int>* root = B.getRoot();
	if (input_str == nullptr || input_str[0] == '#'){
		root = nullptr;
		return in;
	}
	int continue_ = 1;
	root = new TreeNode<int>(input_str[0] - '0');
	q.push(root);
	TreeNode<int>* ptr;
	for (int index = 0;continue_!=0; index++){
		ptr = q.front();
		q.pop();
		char ch = input_str[Child(index)];
		TreeNode<int>* node;
		switch (ch){
		case '#':
			node = nullptr;
			ptr->left = node;
			break;
		case '\0':
			continue_ = 0;
			break;
		default:
			int val = ch - '0';
			node = new TreeNode<int>(val);
			q.push(node);
			ptr->left = node;
		}
		if (continue_){
			char ch = input_str[Child(index)+1];
			switch (ch){
			case '#':
				node = nullptr;
				ptr->right = node;
				break;
			case '\0':
				continue_ = 0;
				break;
			default:
				int val = ch - '0';
				node = new TreeNode<int>(val);
				q.push(node);
				ptr->right = node;
			}
		}
	}
	return in;
}

template <class T>
void creatBinTree(istream& in, TreeNode<T>* & subTree){

} //create the tree
template <class T>
bool BST<T>::insert(TreeNode<T>* & subTree, const T& x){
	if (subTree == nullptr){
		TreeNode<T>* node = new TreeNode<T>(x);
		if (node == nullptr){
			cout << "No more space" << endl;
			return false;
		}
		else{
			subTree = node;
			return true;
		}
	}
	if (subTree->val == x)return false;
	else if (subTree->val < x)return insert(subTree->right, x);
	else return insert(subTree->left, x);
}
template <class T>
bool BST<T>::remove(TreeNode<T>* & subTree, const T& x){
	if (subTree == nullptr){
		cout << "No such element" << endl;
		return false;
	}
	else{
		if (subTree->val < x)return remove(subTree->right, x);
		else if (subTree->val>x)return remove(subTree->left, x);
		else{
			if (subTree->left&&subTree->right){
				TreeNode<T> tmp = findMin(subTree->right);
				subTree->val = tmp->val;
				return remove(subTree->right, subTree->val);
			}
			else{
				TreeNode<T> tmp = subTree;
				if (subTree->left)
					subTree = subTree->left;
				else subTree = subTree->right;
				delete tmp;
				return true;
			}
		}
	}
}
template <class T>
bool BST<T>::find(TreeNode<T>* subTree, const T& x)const{

}
template <class T>
TreeNode<T> BST<T>::findMax(TreeNode<T>* subTree)const{
	if (subTree == nullptr){
		cout << "null ptr!" << endl;
		return nullptr;
	}
	while (subTree->right)subTree = subTree->right;
	return subTree;
}
template <class T>
TreeNode<T> BST<T>::findMin(TreeNode<T>* subTree)const{
	if (subTree == nullptr){
		cout << "null ptr!" << endl;
		return nullptr;
	}
	while (subTree->left)subTree = subTree->left;
	return subTree;
}


template <class T>
void BST<T>::preOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const{
	if (subTree == nullptr){
		cout << "null" << endl;
		return;
	}
	TreeNode<T>* ptr = subTree;
	stack->push(ptr);
	while (!stack->empty()){
		ptr = stack->top();
		stack->pop();
		cout << ptr->val << ",";
		if (ptr->right)stack->push(ptr->right);
		if (ptr->left)stack->push(ptr->left);
	}

}
template <class T>
void BST<T>::inOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const{
	if (subTree == nullptr){
		cout << "null" << endl;
		return;
	}
	TreeNode<T>* ptr = subTree;
	do
	{
		while (ptr != nullptr){
			stack->push(ptr);
			ptr = ptr->left;
		}
		if (!stack->empty()){
			ptr = stack->top();
			stack->pop();
			cout << ptr->val << ",";
			ptr = ptr->right;
		}
	} while (ptr || !stack->empty());
}
template <class T>
void BST<T>::postOrder(stack<TreeNode<T>*>* stack, TreeNode<T>* subTree)const{
}
template <class T>
void BST<T>::levelOrder(queue<TreeNode<T>*>* queue, TreeNode<T>* subTree)const{
	if (subTree == nullptr){
		cout << "null" << endl;
		return;
	}
	TreeNode<T>* ptr = subTree;
	queue->push(subTree);
	while (!queue->empty()){
		ptr = queue->front();
		queue->pop();
		cout << ptr->val << ",";
		queue->push(ptr->left);
		queue->pop(ptr->right);
	}
}

template <class T>
int BST<T>::leafCount(TreeNode<T>* root)const{
	int result = 1;
	if (root == nullptr)return 0;
	if (root->left == nullptr&&root->right == nullptr){
		return 1;
	}
	if (root->left)
		result += leafCount(root->left);
	if (root->right)
		result += leafCount(root->right);
	return result;
}
template <class T>
TreeNode<T>* BST<T>::swapChildern(TreeNode<T>* root){
	if (root == nullptr || (root->left == nullptr&&root->right == nullptr))
		return root;
	TreeNode<T>* left = swapChildern(root->left);
	TreeNode<T>* right = swapChildern(root->right);
	TreeNode<T>* tmp = left;
	left = right;
	right = tmp;
	return root;
}

#endif
BST<int> getInput(){
	BST<int> *B=new BST<int>();
	queue<TreeNode<int>*> q;
	char input_str[1024];
	cin >> input_str;
	TreeNode<int>* root = B->getRoot();
	if (input_str == nullptr || input_str[0] == '#'){
		root = nullptr;
		return *B;
	}
	int continue_ = 1;
	root = new TreeNode<int>(input_str[0] - '0');
	q.push(root);
	TreeNode<int>* ptr;
	for (int index = 0; continue_ != 0; index++){
		ptr = q.front();
		q.pop();
		char ch = input_str[Child(index)];
		TreeNode<int>* node;
		switch (ch){
		case '#':
			node = nullptr;
			ptr->left = node;
			break;
		case '\0':
			continue_ = 0;
			break;
		default:
			int val = ch - '0';
			node = new TreeNode<int>(val);
			q.push(node);
			ptr->left = node;
		}
		if (continue_){
			char ch = input_str[Child(index) + 1];
			switch (ch){
			case '#':
				node = nullptr;
				ptr->right = node;
				break;
			case '\0':
				continue_ = 0;
				break;
			default:
				int val = ch - '0';
				node = new TreeNode<int>(val);
				q.push(node);
				ptr->right = node;
			}
		}
	}
	B->root = root;
	return *B;
}
void exe(){
	BST<int> Tree;
	do{
		cout << endl << "Please input the string to denote the tree:" << endl;
		Tree = getInput();
		cout << endl << "In order:" << endl;
		Tree.inOrder(Tree.getRoot());
		cout << endl << "Pre order:" << endl;
		Tree.preOrder(Tree.getRoot());
		cout << endl << "Post order:" << endl;
		Tree.postOrder(Tree.getRoot());
		cout << endl;
	} while (Tree.root);
	cin.get();
}
int main(){
	exe();
}