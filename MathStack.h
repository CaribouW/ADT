#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node;
typedef struct Node* stack;
typedef struct Node* head;
struct Node{
	double* charSequence;
	int capacity;
	int top;
	stack next;
};

stack Initial(int capacity);
double pop(stack Charstack);
void push(stack Charstack,char* ch);
void printStack(stack Charstack);
double getTop(stack Charstack);
int str2decimal(char* ch);
double dot2double(char* ch);

stack Initial(int capacity){
	stack Charstack = (stack)malloc(sizeof(struct Node));
	if (Charstack == NULL){
		printf("Data OverFlow when Initial!\n");
		return NULL;
	}
	Charstack->capacity = capacity;
	Charstack->next = NULL;
	Charstack->top = -1;
	return Charstack;
}
void printStack(stack Charstack){
	if (Charstack->top == -1){
		printf("Empty stack!\n");
		return;
	}
	int index = Charstack->top;
	for (int i = 0; i < index; i++){
		printf("%.2f ", Charstack->charSequence[i]);
	}
	putchar('\n');
}
double pop(stack Charstack){
	if (Charstack->top == -1){
		printf("Empty stack!\n");
		return '\0';
	}return Charstack->charSequence[Charstack->top--];
}
void push(stack Charstack,char* ch){
	if (Charstack->top == Charstack->capacity-1){
		printf("Stack is full!\n");
		return;
	}
	double result = 0;
	int index = 0;
	int decimal = 1;
	while (ch[index]){
		if (ch == '\\.'){
			decimal = 0;
			break;
		}
		index++;
	}
	if (decimal == 0){
		result = dot2double(ch);
	}
	else if (decimal == 1){
		result = str2decimal(ch);
	}
	Charstack->charSequence[++Charstack->top] = result;
}
double getTop(stack Charstack){
	if (Charstack->top == -1){
		printf("Empty stack!\n");
		return '\0';
	}
	return Charstack->charSequence[Charstack->top];
}
int str2decimal(char* ch){
	int index = 0;
	if (ch == NULL){
		printf("Null ptr when str2decimal!\n");
	}
	char tmp;
	int result = 0;
	int index = 0;
	while ((tmp=ch[index++])!='\0'){
		int num = (int)(ch - '0');
		result = result * 10 + num;
	}
	return result;
}
double dot2double(char* ch){
	double result = 0;
	int index = 0;
	char tmp;
	while ((tmp = ch[index]) != '\\.'){
		index++;
	}
	const int dot = index;

	return result;
}