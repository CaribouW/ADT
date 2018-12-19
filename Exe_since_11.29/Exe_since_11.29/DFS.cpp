#include<iostream>
#include<fstream>
#include<stack>
#include<string>
using namespace std;
class Graph{
public:
	Graph(int node_size = 100){
		this->node_size = node_size;
		edges = new int*[node_size];
		color = new int[node_size];
		father = new int[node_size];
		Stack = new stack<string>();
		for (int i = 0; i < node_size; i++){
			color[i] = -1;
			father[i] = -1;
			edges[i] = new int[node_size];
			for (int j = 0; j < node_size; j++){
				edges[i][j] = -1;
			}
		}
	}
	void refresh(){
		circleConter = 0;
		for (int i = 0; i < node_size; i++){
			color[i] = -1;
			father[i] = -1;
		}
	}
	void DFS(int** edges, int v){
		color[v] = 0;
		for (int w = firstNeigh(v); w != -1; w = nextNeigh(v, w)){
			if (color[w] == -1){
				father[w] = v;
				DFS(edges, w);
			}
			else if (color[w] == 0){//we have one circle , find back through the arry{father}
				circleConter++;
				int end = w;
				int begin = v;
				string tmp("");
				while (begin != end){
					tmp.append(to_string(begin).append("->"));
					//Stack->push(string(to_string(begin)));
					begin = father[begin];
				}
				tmp.append(to_string(begin));
				Stack->push(tmp);
				//cout << Stack->top() << endl;
			}
		}
		color[v] = -1; //
	}
	int firstNeigh(int v){
		if (v >= 0 && v < node_size){
			for (int index = 0; index < node_size; index++){
				if (edges[v][index] == 1)
					return index;
			}
		}
		return -1;
	}
	int nextNeigh(int v, int w){
		if (v >= 0 && v < node_size
			&& w >= 0 && w < node_size){
			for (int index = w + 1; index < node_size; index++){
				if (edges[v][index] == 1)
					return index;
			}
		}
		return -1;
	}
	/*
	* Print the 
	* edges in the graph
	*/
	void printGraph(){
		for (int i = 0; i < node_size; i++)
			for (int j = 0; j < node_size; j++)
				if (edges[i][j] == 1)
					cout << i << "->" << j << endl;
	}
	void findCircle(char* file_name){
		refresh();
		ifstream file(file_name, ios::in);
		if (!file)
			return;
		int v1, v2;
		char dot;
		while (!file.eof()){ //set up all of the edges
			file >> v1 >> dot >> v2;
			edges[v1][v2] = 1;
		}
		for (int i = 0; i < node_size; i++){
			if (color[i] < 0)//not be visited
				DFS(edges, i);
			if (circleConter != 0){ //if we have one circle found, then deal with the stack
				cout << circleConter << endl;
				while (!Stack->empty()){
					cout << Stack->top() << endl;
					Stack->pop();
				}
				break;
			}
		}
		if (circleConter == 0)
			cout << "0" << endl;

	}
private:
	//-1 not found
	//0 just visiting
	//1 visited all
	int node_size;
	int circleConter = 0;
	int* color;
	int* father;
	int** edges;
	char* file;
	stack<string>* Stack;
};