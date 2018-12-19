#include<iostream>
#include<cassert>
#define DefaultSize 20
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
	int getWeight(int v1, int v2);
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
template <class T,class E>
struct Edge{
	int dest;  //another end vertex
	E cost;
	Edge<T, E>* link;  //next edge
	Edge(){}
	Edge(int num, E weight) :dest(num), cost(weight),link(nullptr){
		
	}
	bool operator!=(Edge<T, E> &R){
		return dest != R.dest;
	}
};
template <class T,class E>
struct Vertex{
	T data;
	Edge<T, E>* adj;
};

template <class T, class E>
class Graph{
	friend istream& operator>>(istream& in, Graph<T, E>& G);
	friend ostream& operator<<(ostream& out, Graph<T, E>& G);
public:
	Graph(int sz = DefaultSize);
	~Graph();
	T getValue(int i){
		if (i >= 0 && i < numVertex)
			return NodeTable[i].data;
		else
			return 0;
	}
	E getWeight(int v1, int v2){
		if (v1 != -1 && v2 != -1){
			Edge<T, E> ptr = NodeTable[v1].adj;
			while (ptr != nullptr&&ptr->dest != v2)
				ptr = ptr->dest;
			if (ptr != nullptr)return ptr->cost;
		}
		return 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeightbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);

private:
	Vertex<T, E>* NodeTable;              //The list of the vertex.
	int numEdges, numVertex, maxVertex;
	int maxWeight;
};

#endif