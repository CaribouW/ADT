#include<stdio.h>
#include<stdlib.h>


struct TreeNode;
typedef struct TreeNode* PtrToNode;
typedef PtrToNode Tree;
struct TreeNode{
	int element;
	int height;
	PtrToNode left;
	PtrToNode right;
};
Tree initial_AVL_tree();
/*
T is always the root node of the tree
And we return the new root node.
*/
PtrToNode find(int x, Tree T);
PtrToNode find_min(Tree T);
PtrToNode find_max(Tree T);
Tree insert_tree_node(int x, Tree T);
Tree delete_tree_node(int x, Tree T);
PtrToNode double_rotation_left(PtrToNode T);
PtrToNode double_roration_right(PtrToNode T);
PtrToNode single_roration_left(PtrToNode T);
PtrToNode single_roration_right(PtrToNode T);
void make_empty(Tree T);

Tree initial_AVL_tree(){
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	if (T == NULL){
		printf("Data Overflow!\n");
		return NULL;
	}
	make_empty(T);
	return T;
}
void make_empty(Tree T){
	if (T == NULL)
		return;
	T->left = NULL;
	T->right = NULL;
	T->element = 0;
	T->height = 0;
}

PtrToNode find(int x, Tree T){
	if (T == NULL){
		printf("Empty Tree!\n");
		return NULL;
	}
	if (T->element == x)
		return T;
	else if (T->element < x)
		return find(x, T->right);
	else if (T->element > x)
		return find(x, T->left);
}
PtrToNode find_max(Tree T){
	if (T == NULL){
		printf("Empty tree!\n");
		return NULL;
	}
	if (T->right == NULL)
		return T;
	else return find_max(T->right);
}
PtrToNode find_min(Tree T){
	if (T == NULL){
		printf("Empty tree!\n");
		return NULL;
	}
	if (T->left == NULL)
		return T;
	else return find_min(T->left);
}
Tree insert_tree_node(int x, Tree T){
	if (T == NULL){
		PtrToNode new_T = initial_AVL_tree();
		new_T->element = x;
		return new_T;
	}
	PtrToNode tmp = find(x, T);
	if (tmp)
		return T;


}

Tree delete_tree_node(int x, Tree T){
	if (T == NULL){
		printf("Empty tree!\n");
		return NULL;
	}
	PtrToNode tmp_node = find(x, T);
	if (tmp_node == NULL)
		return T;

}
PtrToNode double_rotation_left(PtrToNode T){
	T->left = single_roration_right(T->left);
	return single_roration_left(T);
}
PtrToNode double_roration_right(PtrToNode T){
	T->right = single_roration_left(T->right);
	return single_roration_right(T);
}
PtrToNode single_roration_left(PtrToNode T){
	if (T == NULL)
		return T;
	PtrToNode tmpNode = T->left;
	T->left = tmpNode->right;
	tmpNode->right = T;
}
PtrToNode single_roration_right(PtrToNode T){
	if (T == NULL)
		return T;
	PtrToNode tmpNode = T->right;
	T->right = tmpNode->left;
	tmpNode->left = T;

	return tmpNode;
}


