#include<iostream>
#include<fstream>
/**
* 用并查集来判定有向图回路
* 规定，v1->v2 则让v2成为v1的父亲
* 不进行路径压缩
*/
int parent[1024];
int find(int x){
	int r = x;
	while (parent[r] >= 0){
		r = parent[r];
	}
	return r;
}
//edge v1->v2 , then we put v2 to be the parent of v1.
int Union(int v1, int v2){
	int root1 = find(v1);
	int root2 = find(v2);
	parent[root1] = root2;
	return root2;
}

void initParents(){
	for (int i = 0; i < 1024; i++)
		parent[i] = -1;
}

void printCircle(int v1, int v2){
	using namespace std;
	int r = v1;
	while (r != v2){
		cout << r << "->";
		r = parent[r];
	}
	cout << r << endl;
}
void hasSetCircle(){
	using namespace std;
	ifstream file("edges.txt", ios::in);
	if (!file){
		return;
	}
	initParents();
	int v1, v2;
	char dot;
	while (!file.eof()){
		file >> v1 >> dot >> v2;
		//cout << v1 << "->" << v2 << endl;
		//a->b  b->c  c->d  d->a 
		//When d->a ,we find root(d)=root(a)
		//so we print from a to d
		int root1 = find(v1);
		int root2 = find(v2);
		if (root1 == root2&&root2 != v2){ //we find one circle
			//print the path from v1 to v2 and we don't union then 
			printCircle(v2, v1);
		}
		else{
			if (root2 == v2) //v2 is the new one
				Union(v1, v2);
		}
	}
}