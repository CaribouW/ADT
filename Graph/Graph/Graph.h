#include<iostream>
#define DefaultSz 20
typedef int E;
using namespace std;
class Graph{
	friend ostream& operator<<(ostream& out, Graph& G);
	friend istream& operator>>(istream& in, Graph& G);
private:
	E** Edge;
	int maxVertex;
	int maxWeight;
	int numEdge, numVertex;
public:
	Graph(int size = DefaultSz);
	~Graph(){ delete[] Edge; }
	int getWeight(int v1, int v2){
		if (v1 >= 0 && v1 < numEdge
			&&v2 >= 0 && v2 < numEdge)
			return Edge[v1][v2];
		else
			return INT_MAX;
	}
	int vertexNum()const{ return numVertex; }
	int edgeNum()const{ return numEdge; }
	int getMaxWeight(){ return maxWeight; }
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
};