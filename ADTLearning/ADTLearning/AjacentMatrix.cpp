#include"AjacentMatrix.h"

template <typename T,typename E>
GraphMatrix<T, E>::GraphMatrix<T, E>(int x):maxVertices(x),numEdges(0),numVertices(0){
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (E**)new E*[maxVertices];
	for (i = 0; i < maxVertices; i++){
		Edge[i] = new E[maxVertices];
	}
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
