#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
struct Node{
	int element;
	PtrToNode next;
};

List InitialList(int x);
void MakeEmpty(List head);
List Find(int x,List head);
List AdjustList(PtrToNode positionBefore, List head);
List Add(int x, List head);
void printList(List head);
int contain(int x, List head);
PtrToNode FindBefore(int x, List head);
PtrToNode FindBeforeNode(PtrToNode node, List head);

List InitialList(int x){
	PtrToNode head = (PtrToNode)malloc(sizeof(struct Node));
	if (head == NULL)
		printf("No more space.\n");
	head->element = x;
	head->next = NULL;
	return head;
}
void MakeEmpty(List head){
	head->next = NULL;
}
List Find(int x, List head){
	if (head == NULL||head->next==NULL){
		return head;
	}
	if (!contain(x, head))
		return head;
	PtrToNode tmpNode = head->next;
	while (tmpNode->next != NULL){
		PtrToNode tmp = tmpNode->next;
		if (tmpNode->element == x){
			PtrToNode node = FindBeforeNode(tmpNode, head);
			head = AdjustList(node, head);
		}

		tmpNode = tmp;
	}if (tmpNode->element == x){
		PtrToNode node = FindBeforeNode(tmpNode, head);
		head = AdjustList(node, head);
	}
	return head;
}
List AdjustList(PtrToNode positionBefore, List head){
	if (positionBefore == head)
		return;
	PtrToNode tmp = positionBefore->next;
	positionBefore->next = tmp->next;
	tmp->next = head;
	return tmp;
}
List Add(int x, List head){
	if (head == NULL)
		return head;
	PtrToNode NewNode = (PtrToNode)malloc(sizeof(struct Node));
	if (NewNode == NULL){
		printf("No more space.\n");
		return head;
	}
	while (head->next != NULL){
		head = head->next;
	}
	head->next = NewNode;
	NewNode->next = NULL;
	NewNode->element = x;
	return head;
}
void printList(List head){
	if (head == NULL)
		return;
	printf("[");
	while (head->next != NULL){
		printf("%d,", head->element);
		head = head->next;
	}
	printf("%d]", head->element);
}
int contain(int x, List head){
	if (head == NULL)
		return 0;
	while (head->next != NULL){
		if (head->element == x)
			return 1;
		head = head->next;
	}if (head->element == x)
		return 1;
	return 0;
}
PtrToNode FindBefore(int x, List head){
	if (head == NULL){
		printf("Empty list.\n");
		return NULL;
	}
	while (head->next != NULL){
		if (head->next->element == x)
			return head;
		head = head->next;
	}return NULL;
}
PtrToNode FindBeforeNode(PtrToNode node, List head){
	if (head == NULL){
		printf("Empty list.\n");
		return NULL;
	}if (node == head){
		return head;
	}while (head->next != NULL){
		if (head->next == node)
			return head;
		head = head->next;
	}
	return head;
}