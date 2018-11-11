#include"laucher.h"
#ifdef HASH
using namespace std;
const int DefaultSize = 20;
class HashTable{
private:
	int* table;
	int capacity;
	int size;
	int getNearPrime(int value);
	int HashFunc(int value){
		return value%size;
	}
public:
	friend ostream& operator<<(ostream& out, HashTable& H);
	friend istream& operator>>(istream& in, HashTable& H);
	HashTable(int sz = DefaultSize){
		size = getNearPrime(sz);
		table = new int[size];
		for (int i = 0; i < size; i++)
			table[i] = INT_MIN;
	}
	void printTbl()const{
		for (int i = 0; i < size; i++){
			cout << "---------" << endl;
			cout << "----" << table[i] << endl;
		}
	}
	void relocate(int value);

};

#endif