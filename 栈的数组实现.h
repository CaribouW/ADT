#include<stdio.h>
#include<stdlib.h>
#define EmptyTOS (-1)
struct Node;
typedef struct Node* stack;
struct Node{
	int Capacity;
	int TopOfStack;
	int* Arry;
};
void DisposeStack(stack);
int IsEmpty(stack);
void MakeEmpty(stack);
void Push(stack s, int num);
void Pop(stack s);
int GetTop(stack s);

void DisposeStack(stack s){
	if (s != NULL){
		free(s->Arry);
		free(s);
	}
}
int IsEmpty(stack s){
	return s->TopOfStack == EmptyTOS;
}
void MakeEmpty(stack s){
	s->TopOfStack = EmptyTOS;
}

void Push(stack s, int num){
	if (s->TopOfStack == s->Capacity)
		printf("Data overflow!\n");
	else
		s->Arry[++s->TopOfStack] = num;
}
void Pop(stack s){
	if (IsEmpty(s))
		printf("Empty stack!\n");
	else
		s->TopOfStack--;
}
int GetTop(stack s){
	if (IsEmpty(s)){
		printf("Data error!\n");
		return 0;
	}
	else
		return s->Arry[s->TopOfStack];
}