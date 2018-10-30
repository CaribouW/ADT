#include<iostream>
#include<cstring>

static int* next;

int KMP_search(char* text,char* pattern);
void getNext(char* pattern);

int KMP_search(char* text, char* pattern){
	int len_t = strlen(text);
	int len_p = strlen(pattern);
	getNext(pattern);
	int index_t=0, index_p=0;
	while (index_t < len_t&&index_p < len_p){
		if (index_p < 0 || text[index_t] == pattern[index_p]){
			++index_p;
			++index_t;
		}
		else{
			index_p = next[index_p];
		}
	}
	if (index_p < len_p)return -1;
	else
		return index_t - len_p;
}

void getNext(char* pattern){
	int len = strlen(pattern);
	int index = 0;
	int k = -1;
	next[0] = -1;
	while (index < len){ 
		if (k < 0 || pattern[index] == pattern[k]){
			next[++index] = ++k;
		}
		else{
			k = next[k];
		}
	}

}