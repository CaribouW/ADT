#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node* stack;
typedef struct Node{
	int num;
	struct Node* next;
}stackNode;

stack getStackNode(void);
int isEmpty(stack s);
void makeEmpty(stack s);
void pop(stack s);
void push(stack s);
int getTopElement(stack s);
int size(stack s);

stack getStackNode(void){
	stack p;

	p = (stack)malloc(sizeof(stackNode));
	if (!p)
		printf("Data overflow!\n");
//	makeEmpty(p);
	p->next = NULL;
	return p;
}

int isEmpty(stack s){
	return s->next == NULL;
}

void makeEmpty(stack s){
	if (s == NULL)
		printf("No existed stack!\n");
	while (!isEmpty(s))
		pop(s);
}

void pop(stack s){
	stack tmp;

	if (isEmpty(s)){
		printf("Empty stack.\n");
		return;
	}

	tmp = s->next;
	s->next = tmp->next;
	free(tmp);
}

void push(int num,stack s){
	stack tmp;

	tmp = (stack)malloc(sizeof(struct Node));
	if (tmp == NULL)
		printf("Data overflow!\n");
	else{
		tmp->next = s->next;
		s->next = tmp;
		tmp->num = num;
	}
}

int getTopElement(stack s){
	if (!isEmpty(s))
		return s->next->num;
	printf("Empty stack.\n");
}

int size(stack s){
	stack tmp = s;
	int count = 0;

	if (isEmpty(s))
		return count;
	while (tmp->next != NULL){
		count++;
		tmp = tmp->next;
	}
	return count;
}