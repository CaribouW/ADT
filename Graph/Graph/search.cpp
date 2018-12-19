#include"config.h"
#include<queue>
void DFS(Graph& G, int v, bool* visited){
	cout << "val = [" << v << "]"<<endl;
	visited[v] = true;
	for (int i = G.getFirstNeighbor(v); i != -1; i = G.getNextNeighbor(v, i)){
		if (!visited[i]){
			DFS(G, i, visited);
		}
	}
}

void DFS(Graph& G, int v){
	int n = G.vertexNum();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;
	cout << "deap first search begin" << endl;
	DFS(G, v, visited);
	delete[] visited;
}
void BFS(Graph& G, int v){
	int n = G.vertexNum();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;
	queue<int>* q = new queue<int>();

	q->push(v);
	visited[v] = true;
	cout << "broad fist search begin" << endl;
	cout << "val = [" << v << "]" << endl;
	while (!q->empty()){
		int w = q->front();
		q->pop();
		for (int i = G.getFirstNeighbor(w); i != -1; i = G.getNextNeighbor(w, i)){
			if (!visited[i]){
				q->push(i);
				visited[i] = true;
				cout << "val = [" << i << "]" << endl;
			}
		}
	}
}
