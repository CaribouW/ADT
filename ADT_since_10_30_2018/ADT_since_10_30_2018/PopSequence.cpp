#include<iostream>
#include<cassert>
#include<stack>
#ifdef pop_sequence
/*

Each input file contains one test case.
For each case, the first line contains 3 numbers (all no more than 1000)

M (the maximum capacity of the stack),
N (the length of push sequence), and K (the number of pop sequences to be checked).
Then K lines follow, each contains a pop sequence of N numbers.
All the numbers in a line are separated by a space.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2


Sample Output:
YES
NO
NO
YES
NO
*/

void solve(){
	using namespace std;
	int capacity;
	int testcaseNum;
	int sequenceLen;
	cin >> capacity; cin >> sequenceLen; cin >> testcaseNum;
	int* arr = new int[sequenceLen];
	for (int lenIndex = 0; lenIndex < testcaseNum; lenIndex++){
		stack<int>* s = new stack<int>();
		int size = 0;
		bool k = 1;
		int readerVal;
		int top_val = 0;
		int push_val = 1;
		for (int i = 0; i < sequenceLen; i++){
			cin >> readerVal;
			arr[i] = readerVal;
		}
		for (int i = 0; k&& i < sequenceLen; i++){
			readerVal=arr[i];
			if (top_val < readerVal){
				for (; push_val <= readerVal; top_val++){
					if (size >= capacity){
						k = 0;
						break;
					}
					s->push(push_val++);
					//top_val = s->top();
					size++;
				}
				s->pop();
				size--;
			}
			else{
				top_val = s->top();
				if (top_val == readerVal){
					s->pop();
					size--;
				}
				else{
					k = 0;
					break;
				}
			}
		}
		if (k)
			cout << "YES";
		else
			cout << "NO";
		cout << endl;
	}
}


#endif