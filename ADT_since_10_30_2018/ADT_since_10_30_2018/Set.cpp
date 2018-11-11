#include"config.h"

void Set::Union(int root1, int root2){
	arr[root1] += arr[root2];
	arr[root2] = root1;
}
int Set::Find(int x){
	return (arr[x] < 0) ? x : Find(arr[x]);
}
int Set::CollapsingFind(int x){
	int root = x;
	while (arr[root] >= 0)
		root = arr[root];
	while (x != root){
		int currentParent = arr[x];
		arr[x] = root;
		x = currentParent;
	}
	return root;
}

void Set::WeightedUnion(int root1, int root2){
	int r1 = Find(root1);
	int r2 = Find(root2);
	int tmp;
	if (r1 != r2)
		tmp = arr[r1] + arr[r2];
	if (arr[r1] < arr[r2]){
		arr[r2] = r1;
		arr[r1] = tmp;
	}
	else{
		arr[r1] = r2;
		arr[r2] = tmp;
	}
}
