#include<iostream>
#include<cassert>
#define DefaultSize 20;
#define matrix_graph

#ifdef matrix_graph
using namespace std;
template <class T, class E>
class Graph{
	friend istream& operator>>(istream& in, Graph<T, E>& G);
	friend ostream& operator<<(ostream& out, Graph<T, E>& G);
public:
	Graph(int sz = DefaultSize);
	~Graph(){ delete[] VerticesList; delete[] Edge; }
	T getValue(int i){
		return i >= 0 && i <= numVertex ? VerticesList[i] : nullptr;
	}
	E getWeight(int v1, int v2){
		return v1 != -1 && v2 != -1 ?
			Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeightbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);

private:
	T* VerticesList;
	E** Edge;
	int numEdges, numVertex, maxVertex;
	int maxWeight;
	int getVertexPos(T vertex){
		for (int i = 0; i < numVertex; i++){
			if (vertex == VerticesList[i])return i;
		}
		return -1;
	}
	bool isValidEdge(int v1, int v2){
		if (v1 >= 0 && v1 < numVertex&&
			v2 >= 0 && v2 < numVertex){
			return Edge[v1][v2]>0 &&
				Edge[v1][v2] < maxWeight;
		}
		return false;
	}
};
#else
using namespace std;
template <class T, class E>
class Graph{
	friend istream& operator>>(istream& in, Graph<T, E>& G);
	friend ostream& operator<<(ostream& out, Graph<T, E>& G);
public:
	Graph(int sz = DefaultSize);
	~Graph();
	int getFirstNeighbor(int v);
	int getNextNeightbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);

private:
	int numEdges, numVertex, maxVertex;
	int maxWeight;
};

#endif