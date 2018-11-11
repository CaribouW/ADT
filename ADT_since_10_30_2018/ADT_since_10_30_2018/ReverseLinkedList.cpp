#include<iostream>
#include<cstdlib>
#include<cassert>
#ifdef reverse_linked_list

/*
sample input

00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
*/
struct node{
	int data;
	int addr;
	int nextAddr;
	node* next;
	node(int a, int b, int c){
		addr = a;
		data = b;
		nextAddr = c;
		next = nullptr;
	}
	node(){}
};


class list{
public:
	int len;
	int subReverseLen;
	node* first;
};


void solve(){
	using namespace std;
	int tmpReader;
	list l;
	l.first = new node();
	cin >> tmpReader;
	l.first->addr = tmpReader;
	cin >> tmpReader;
	l.len = tmpReader;
	cin >> tmpReader;
	l.subReverseLen = tmpReader;
	node* arr = new node[l.len];
	assert(l.len > 0);

	for (int count = 0; count < l.len; count++){
		int addr, data, nextAddr;
		cin >> addr; cin >> data; cin >> nextAddr;
		arr[count] = node(addr,data,nextAddr);
		arr[count].addr = addr;
		arr[count].data = data;
		arr[count].nextAddr = nextAddr;
	}
	int targetAddr = l.first->addr;
	for (int count = 0; count < l.len; count++){

	}



	cin.get();
	return;
}

#endif

#ifdef reverse_arr
using namespace std;
void solve(){
	int len, reverse_len;
	cin >> len; cin >> reverse_len;
	int* arr = new int[len];
	for (int i = 0; i < len; i++){
		cin >> arr[i];
	}

	int i;
	int m = len / reverse_len;
	for (i = 0; i < m*reverse_len; i++){
		int factor = i / reverse_len;
		int remain = i%reverse_len;
		if (remain >= reverse_len / 2)continue;
		int newIndex = (factor + 1)*reverse_len - remain - 1;
		int tmp_val = arr[i];
		arr[i] = arr[newIndex];
		arr[newIndex] = tmp_val;
	}
	reverse_len = len - i;
	if (reverse_len > 0){
		for (; i < len; i++){
			int factor = i / reverse_len;
			int remain = i%reverse_len;
			if (remain >= reverse_len / 2)continue;
			int newIndex = (factor + 1)*reverse_len - remain - 1;
			int tmp_val = arr[i];
			arr[i] = arr[newIndex];
			arr[newIndex] = tmp_val;
		}
	}
	for (int index = 0; index < len; index++){
		cout << arr[index] << " ";
	}
	cout << endl;
	cin.get();
	cin.get();
}
#endif