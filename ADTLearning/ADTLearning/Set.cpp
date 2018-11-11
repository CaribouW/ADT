#include<iostream>
#define SET_INT

#ifdef SET
using namespace std;
template <class T>
struct SetNode{
	T val;
	int parent;
};

template <class T>
class Set{
private:
	SetNode* nodeArr;
	int size;
public:
	Set<T>(int size = 20){
		this->size = size;
		nodeArr = new SetNode[size];
		for (int i = 0; i < size; i++){
			nodeArr[i].parent = -1;
		}
	}
	~Set<T>(){
		delete[] nodeArr;
	}


};

#endif

#ifdef SET_INT
class Set{
private:
	int* nums;
	int capacity;
public:
	Set(int size = 20) :capacity(size){
		nums = new int[size];
		for (int i = 0; i < size; i++)
			nums[i] = -1;
	}
	~Set(){ delete[] nums; }
	void Union(int root1, int root2);
	int Find(int x);                  //ret the root of the element x.
	void WeightedUnion(int root1, int root2);
	int CollapsingFind(int i);
};

void Set::Union(int root1, int root2){
	nums[root1] += nums[root2];
	nums[root2] = root1;
}

int Set::Find(int x){
	while (nums[x] >= 0)
		x = nums[x];
	return x;
	/*
	if(nums[x]<0)return x;
	else
		return Find(nums[x]);
	*/
}

void Set::WeightedUnion(int root1, int root2){
	int r1 = Find(root1);
	int r2 = Find(root2);
	int temp;
	if (r1 != r2){
		temp = r1 + r2;
	}
	//r1 is bigger than r2
	if (nums[r1] < nums[r2]){
		nums[r2] = r1;
		nums[r1] = temp;
	}
	else{
		nums[r1] = r2;
		nums[r2] = temp;
	}
}

int Set::CollapsingFind(int i){
	int root;
	//launch finding,where the i denotes the root.
	for (root = i; nums[root] >= 0; root = nums[root]);
	//collapsing 
	while (root != i){
		int tmpFather = nums[i]; //get the father.
		nums[i] = root; //change the root.
		i = tmpFather; //move upward.
	}
	return root;
}
#endif

