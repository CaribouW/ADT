#include"MathStack.h"
static const char LeftParenthese = '(';
static const char RightParenthese = ')';
static const char LeftBracket = '[';
static const char RightBracket = ']';
static const char LeftBrace = '{';
static const char RightBrace = '}';
static const char add = '+';
static const char decrease = '-';
static const char multiple = '*';
static const char divide = '/';
int IsBalance(char* str);
int computeSuccfix(char *str);
char* infix2succfinx(char* infix);
double compute(char* infix);
double praseDouble(char* str);

int IsBalance(char* str){
	if (str == NULL){
		printf("Empty str!\n");
		return -1;
	}
	head BalanceStack = Initial(126);
	char tmp;
	int index = 0;
	while ((tmp = str[index++]) != '\0'){
		if (tmp == LeftBrace || tmp == LeftBracket || tmp == LeftParenthese){
			push(BalanceStack, tmp);
			continue;
		}
		switch (tmp){
		case ')':
			if (BalanceStack->top == -1)
				return 0;
			else{
				char out = pop(BalanceStack);
				if (out == '(')
					break;
				else
					return 0;
			}
		case ']':
			if (BalanceStack->top == -1)
				return 0;
			else{
				char out = pop(BalanceStack);
				if (out == '[')
					break;
				else
					return 0;
			}
		case '}':
			if (BalanceStack->top == -1)
				return 0;
			else{
				char out = pop(BalanceStack);
				if (out == '{')
					break;
				else
					return 0;
			}
		default:
			break;
		}
	}
	return 1;
}
int computeSuccfix(char** str){
	int index = 0;
	char* tmp;
	char* num1;
	char* num2;
	head computeStack = Initial(128);
	while ((tmp = str[index++]) != '\0'){
		switch (tmp){
		case '*':
			if (computeStack->top <= 0){
				printf("Compute Error!\n");
				return 0;
			}
			num1 = pop(computeStack);
			num2 = pop(computeStack);
			push(computeStack, (char*)(num1*num2));
			break;
		case '/':
			if (computeStack->top <= 0){
				printf("Compute Error!\n");
				return 0;
			}
			num1 = pop(computeStack);
			num2 = pop(computeStack);
			push(computeStack, (char*)(num1/num2));
			break;
		case '+':
			if (computeStack->top <= 0){
				printf("Compute Error!\n");
				return 0;
			}
			num1 = pop(computeStack);
			num2 = pop(computeStack);
			push(computeStack, (char)(num1+num2));
			break;
		case '-':
			if (computeStack->top <= 0){
				printf("Compute Error!\n");
				return 0;
			}
			num1 = pop(computeStack);
			num2 = pop(computeStack); 
			push(computeStack, (char)(num1-num2));
			break;
		default:
			push(computeStack, praseInt(tmp));
			break;
		}
	}
	return getTop(computeStack);

}
char* infix2succfinx(char* infix){

}
double compute(char* infix){

}
double prasedouble(char* str){
	if (str == NULL){
		printf("Null ptr while prasing.\n");
		return 0;
	}return (int)(str - '0');
}
int main(){
	stack s = Initial(34);
	push(s, "hahah");
	push(s, "hava");
}