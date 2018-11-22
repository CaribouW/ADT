#include"config.h"
template <class T, class E>
Graph<T, E>::Graph(int sz){
	maxWeight = INT_MAX;
	maxVertex = sz;
	numEdges = numVertex = 0;
	VerticesList = new T[sz];
	Edge = (E**)new E*[sz];
	for (int i = 0; i < sz; i++){
		Edge[i] = new E[sz];
	}
	for (int i = 0; i < sz; i++){
		for (int j = 0; j < sz; j++)
			Edge[i][j] = i == j ? 0 : maxWeight;
	}
}

template <class T, class E>
int Graph<T, E>::getFirstNeighbor(int v){
	if (v != -1){
		for (int i = 0; i < numVertex; i++){
			if (isValidEdge(v, i)return i;
		}
	}
	return -1;
}
template <class T, class E>
int Graph<T, E>::getNextNeightbor(int v, int w){
	if (v != -1 && w != -1){
		for (int i = w + 1; i < numVertex; i++){
			if (isValidEdge(v, i))
				return i;
		}
	}
	return -1;
}

template <class T, class E>
bool Graph<T, E>::insertEdge(int v1, int v2, E cost){
	if (v1 > -1 && v1<numVertex&&
		v2>-1 && v2 < numVertex&&
		Edge[v1][v2] != maxWeight){
		Edge[v1][v2] = cost;
		return true;
		numEdges++;
	}
	return false;
}
template <class T, class E>
bool Graph<T, E>::insertVertex(const T& vertex){
	if (numVertex == maxVertex)return false;
	VerticesList[numVertex++] = vertex;
	return true;
}
template <class T, class E>
bool Graph<T, E>::removeVertex(int v){
	return 1;
}
template <class T, class E>
bool Graph<T, E>::removeEdge(int v1, int v2){
	return 1;
}
