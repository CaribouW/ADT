#include"laucher.h"
#ifdef SET
class Set{
public:
	Set(int sz = DefaultSize) :size(sz){
		arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = -1;
	}
	~Set(){ delete[] arr; }
	void Union(int root1, int root2);
	int Find(int x);
	int CollapsingFind(int x);
	void WeightedUnion(int root1, int root2);
private:
	int *arr;
	int size;
};

#endif