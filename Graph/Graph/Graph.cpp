#include"config.h"

Graph::Graph(int size){
	maxVertex = size;
	numEdge = 0;
	numVertex = 0;
	maxWeight = INT_MAX;
	Edge = (E**)new E*[size];
	for (int i = 0; i < size; i++)
		Edge[i] = new E[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			Edge[i][j] = ((i == j) ? 0 : INT_MAX);
}
ostream& operator<<(ostream& out, Graph& G){
	int edgeNum = G.edgeNum();
	out << "edge num = " << edgeNum
		<< endl;
	for (int i = 0; i < edgeNum; i++){
		for (int j = 0; j < edgeNum; j++){
			int weight = G.getWeight(i, j);
			if (weight > 0 && weight < G.maxWeight)
				out << "(" << i << "," << j << ")" << "=" << weight << endl;
		}
	}
	return out;

}
/*
intput:
m n k    //row numvertex EdgeLine
i j weight     //(i,j)=weight

5 5 7
0 1 10
0 3 30
0 4 100
1 2 50
2 4 10
3 2 20
3 4 60


*/
istream& operator>>(istream& in, Graph& G){
	int row, column, edgeNum;
	in >> row >> column >> edgeNum;
	int i, j, weight;
	G.maxVertex = row;
	G.numVertex = column;
	G.Edge = new int*[row];
	for (int k = 0; k < edgeNum; k++){
		G.Edge[k] = new int[row];
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < row; j++)
			G.Edge[i][j] = (i == j) ? 0 : INT_MAX;
	for (int k = 0; k < edgeNum; k++){
		in >> i >> j >> weight;
		if (i < 0 || i >= G.maxVertex ||
			j < 0 || j >= G.maxVertex){
			cout << "Please give the right num!The last info will not be counted" << endl;
			i--;
			continue;
		}
		G.Edge[i][j] = weight;
		G.numEdge++;
	}
	return in;
}

int Graph::getFirstNeighbor(int v){
	if (v >= 0 && v < maxVertex){
		for (int i = 0; i < maxVertex; i++){
			if (Edge[v][i]>0 && Edge[v][i] < maxWeight)
				return i;
		}
	}
	return -1;
}

int Graph::getNextNeighbor(int v, int w){
	if (v >= 0 && v < maxVertex){
		if (w >= 0 && w < maxVertex){
			for (int i = w + 1; i < maxVertex; i++){
				if (Edge[v][i] > 0 && Edge[v][i] < maxWeight)
					return i;
			}
		}
	}
	return -1;
}