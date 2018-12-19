#include"config.h"

#ifdef matrix_graph
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
			if (isValidEdge(v, i))return i;
		}
	}
	return -1;
}
template <class T, class E>
int Graph<T, E>::getNextNeightbor(int v, int w){
	if (v != -1 && w != -1){
		//search from w index
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
	if (v < 0 || v >= numVertex || numVertex == 1)return false;
	//put the last vertex to the v_th vertex
	VerticesList[v] = VerticesList[numVertex - 1];
	for (int i = 0; i < numVertex; i++)
		if (isValidEdge(i, v))
			numEdges--;

	//put the last column to the v_th column
	for (int i = 0; i < numVertex; i++){
		Edge[i][v] = Edge[i][numVertex - 1];
	}
	//put the last row to the v_th row
	for (int i = 0; i < numVertex; i++){
		Edge[v][i] = Edge[v][numVertex];
	}
	numVertex--;
	return 1;
}
template <class T, class E>
bool Graph<T, E>::removeEdge(int v1, int v2){
	if (isValidEdge(v1, v2)){
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return 1;
	}
	return 0;
}

template <class T,class E>
istream& operator>>(istream& in, Graph<T, E>& G){
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	for (i = 0; i < n; i++){
		in >> e1;
		G.insertVertex(e1);
	}
}
#else
template <class T, class E>
Graph<T, E>::Graph(int sz){
	maxVertex = sz;
	numVertex = numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertex];
	if (NodeTable == nullptr){
		cout << "No more space for the nodeTable!" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertex; i++){
		NodeTable[i].link = nullptr;
	}
}
template <class T, class E>
int Graph<T, E>::getFirstNeighbor(int v){
	if (v != -1){
		Edge<T, E>* ptr = NodeTable[v].adj;
		if (ptr != null)
			return ptr->dest;
	}
	return -1;
}
template <class T, class E>
int Graph<T, E>::getNextNeightbor(int v, int w){
	if (v != -1){
		Edge<T, E>* ptr = NodeTable[v].adj;
		while (ptr != nullptr&&ptr->link.dest != w){
			ptr = ptr->link;
		}
		if (ptr != nullptr&&ptr->link != nullptr)
			return ptr->link.dest;
	}
	return -1;
}

template <class T, class E>
bool Graph<T, E>::insertEdge(int v1, int v2, E cost){
}
template <class T, class E>
bool Graph<T, E>::insertVertex(const T& vertex){
	if (numVertex == maxVertex)return false;
	NodeTable[numVertex++].data = vertex;
	return true;
}
template <class T, class E>
bool Graph<T, E>::removeVertex(int v){

}
template <class T, class E>
bool Graph<T, E>::removeEdge(int v1, int v2){
	bool result;
	if (v1 != -1 && v2 != -1){
		Edge<T, E> *ptr, *pre;
		Edge<T, E>* head = NodeTable[v1].adj;
		while (ptr != nullptr&&ptr->dest != v2){
			pre = ptr;
			ptr = ptr->link;
		}
		if (ptr != nullptr){
			if (ptr == head)
				NodeTable[v1].adj = ptr->link;
			else{
				pre->link = ptr->link;
			}
			delete pre->link;
		}
		else
			return false;
	}
	
	return false;
}


#endif