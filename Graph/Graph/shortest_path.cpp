#include"config.h"
void print_shortestPah(Graph& G, int v, E dist[], int path[]){
	cout << "From vertex v = [" << v << "] we have the shortest path" << endl;
	int n = G.vertexNum();
	int* d = new int[n];
	for (int i = 0; i < n; i++){
		if (i != v){
			int j = i, k = 0;
			while (j != v){
				d[k++] = j;
				j = path[j];
			}
			cout << "node [" << i << "] has the path:" << v << "-";
			while (k > 0){ cout << d[--k] << "-"; }
			cout << endl << "The length is [" << dist[i] << "]" << endl;
		}
	}
	for (int i = 0; i < n * 3; i++)cout << "-";
	cout << endl;
	for (int i = 0; i < n; i++){
		cout << "dist [" << i << "] = " << dist[i]<<endl;
	}
	for (int i = 0; i < n; i++){
		cout << "path [" << i << "] = " << path[i] << endl;
	}
	delete[] d;
}
void shortest_path(Graph& G, int v, E dist[], int path[]){
	if (v < 0 || v >= G.vertexNum()){
		cout << "v is illegal" << endl;
		return;
	}
	int n = G.vertexNum();
	E w, min;
	bool* visited = new bool[n];
	/*
	Initilaze the whole arr.
	*/
	for (int i = 0; i < n; i++){
		visited[i] = false;
		dist[i] = G.getWeight(v, i);
		if (dist[i] < G.getMaxWeight())
			path[i] = v;
		else
			path[i] = -1;
	}

	visited[v] = true;
	dist[v] = 0;
	for (int i = 0; i < n - 1; i++){
		min = INT_MAX; int u = v;
		for (int j = 0; j < n; j++){
			/*
			find the next node u
			*/
			if (!visited[j] && dist[j] < min){
				u = j;
				min = dist[j];
			}
		}
		visited[u] = true;//We have visited the node u
		for (int k = 0; k < n; k++){
			w = G.getWeight(u, k); //compute the dis (u,k) ,u is the new node 
			if (!visited[k] 
				&& w < G.getMaxWeight()){
				if (w + dist[u] < dist[k]){
					dist[k] = w + dist[u];
					path[k] = u;
				}
			}
		}
	}
}
void Bellman_Ford(Graph& G, int v, E dist[], int path[]){
	if (v < 0 || v >= G.vertexNum()){
		cout << "v is illegal" << endl;
		return;
	}
	int n = G.vertexNum();
	for (int i = 0; i < n; i++){
		dist[i] = G.getWeight(v, i);
		path[i] = (i != v&&dist[i] < G.getMaxWeight()) ?
		v : -1;
	}
	for (int k = 2; k < n; k++){
		for (int u = 0; u < n; u++){
			if (u != v)
				for (int j = 0; j < n; j++){
					E w = G.getWeight(j, u);
					if (w > 0 && w < G.getMaxWeight() && w + dist[j] < dist[u]){
						dist[u] = w + dist[j];
						path[u] = j;
					}
				}
		}
	}
}
void FLoyd(Graph& G, E** A, int** path){
	int n = G.vertexNum();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			A[i][j] = G.getWeight(i, j);
			if (i != j&&A[i][j] < G.getMaxWeight())
				path[i][j] = i;
			else
				path[i][j] = -1;
		}
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++){
				if (A[i][j] < A[i][k] + A[k][j]){
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
			}
}