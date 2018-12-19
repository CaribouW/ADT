#include"search.h"
int main(){
	Graph G(3);
	cin >> G;
	cout << G;
	/*E * dist = new int[G.vertexNum()];
	int* path = new int[G.vertexNum()];
	shortest_path(G, 0, dist, path);
	print_shortestPah(G, 0, dist, path);
	for (int i = 0; i < 5; i++)cout << endl;
	*/
	for (int i = 0; i < G.vertexNum(); i++){
		DFS(G, 0);
		BFS(G, 0);
	}
	cin.get();
	cin.get();
}