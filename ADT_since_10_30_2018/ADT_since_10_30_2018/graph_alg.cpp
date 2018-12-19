#include "config.h"
#include<queue>
#include<heapapi.h>
#include<set>
template <class T, class E>
void DFS(Graph<T, E>& G, const T& begin);
template <class T, class E>
void DFS(Graph<T, E>& G, int begin, bool visited[]);

template <class T, class E>
void DFS(Graph<T, E>& G, const T& begin){
	int numVertex = G.numVertex;
	bool* visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)visited[i] = false;
	int loc = G.getVertexPos(begin);
	DFS(G, loc, visited);
	delete[] visited;
}

template <class T, class E>
void DFS(Graph<T, E>& G, int begin, bool visited[]){
	cout << G.getValue(begin) << ",";
	visited[begin] = true;
	for (int loc = G.getFirstNeighbor(begin); loc != -1;
		loc = G.getNextNeightbor(begin, loc)){
		if (!visited[loc])
			DFS(G, loc, visited);
	}
}

template <class T, class E>
void BFS(Graph<T, E>& G, const T& begin){
	int numVertex = G.numVertex;
	bool* visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)visited[i] = false;
	int loc = G.getVertexPos(begin);

	cout << G.getValue(loc) << ",";
	visited[loc] = true;
	queue<int> Q;
	Q.push(loc);
	while (!Q.empty()){
		loc = Q.front();
		Q.pop();
		for (int w = G.getFirstNeighbor(loc); w != -1; w = G.getNextNeightbor(loc, w)){
			if (!visited[w]){
				cout << G.getValue(w) << ",";
				visited[w] = true;
				Q.push(w);
			}
		}
	}
}

