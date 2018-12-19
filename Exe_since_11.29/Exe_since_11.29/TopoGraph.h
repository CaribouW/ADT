#include<iostream>
#include<stack>
#include<fstream>
using namespace std;
class TopoGraph{
public:
	TopoGraph(int size = 100){
		node_size = size;
		edge = new int*[size];
		indegree = new int[size];
		non_indegree_stack = new stack<int>();
		for (int i = 0; i < size; i++){
			indegree[i] = -1;  //no such node :-1   we have the node : val >= 0 
			edge[i] = new int[size];
			for (int j = 0; j < size; j++)
				edge[i][j] = 0;
		}
	}
	~TopoGraph(){
		delete[] edge;
		delete[] indegree;
	}
	void topo_sort(){
		//1.check all of the zero_indegree nodes,push into the stack
		//2.while stack not empty, we pop the node on the top of the stack,and remove it. check the indegree at the same time
		// if we find one zero node,then we push to the top.
		for (int i = 0; i < node_size; i++){// 1
			if (indegree[i] == 0)
				non_indegree_stack->push(i);
		}
		while (!non_indegree_stack->empty()){
			int top_val = non_indegree_stack->top();
			cout << top_val << ",";
			non_indegree_stack->pop();
			for (int w = findFirstNeigh(top_val); w != -1; w = findNextNeigh(top_val, w)){
				if (--indegree[w] == 0)
					non_indegree_stack->push(w);
			}
			remove_node(top_val);
		}
	}
	void Initialize(char* file_name){
		ifstream file(file_name, ios::in);
		if (!file)
			return;
		int v1, v2;
		int weight;
		char dot;
		while (!file.eof()){ //set up all of the edges
			file >> v1 >> dot >> v2 >> dot >> weight; //v1 -> v2
			edge[v1][v2] = weight;
			indegree[v1] = indegree[v1] == -1 ? 0 : indegree[v1];
			indegree[v2] = indegree[v2] == -1 ? 1 : (indegree[v2] + 1);
		}
	}
	int get_weight(int v, int w){
		return edge[v][w];
	}
	// assume <i,j> is the edge_(k)
	//Ae[k] means the earliest time Activity_k occurs.		Ae[k] = Ve[i]
	//Al[k] means the latest time Activity_k occurs.		Al[k] = Vl[j] - weight[k]
	//Ve[i] means the longest path from begin to node_(i)   Ve[i] = max(weight<i-1,i> + Ve[i-1])
	//Vl[i] means the shortest path from end to node_(i)    Vl[i] = min(Vl[i+1] - weight<i,i+1>)
	int AOE(int n){
		int result = 0;
		int* Ve = new int[n];
		int* Vl = new int[n];
		for (int i = 0; i < n; i++){
			Ve[i] = 0;
			Vl[i] = INT_MAX;
		}
		for (int i = 0; i < n; i++){
			for (int w = findFirstNeigh(i); w != -1; w = findNextNeigh(i, w)){
				int weight = get_weight(i, w);
				if (Ve[w] < weight + Ve[i])
					Ve[w] = weight + Ve[i];
			}
		}

		for (int i = 0; i < n; i++)
			cout << Ve[i] << ",";
		cout << endl;

		Vl[n - 1] = Ve[n - 1];
		Vl[0] = Ve[0];
		for (int i = n - 2; i > 0; i--){
			for (int w = findFirstNeigh(i); w != -1; w = findNextNeigh(i, w)){
				int weight = get_weight(i, w);
				if (Vl[i] > Vl[w] - weight)
					Vl[i] = Vl[w] - weight;
			}
		}
		for (int i = 0; i < n; i++)
			cout << Vl[i] << ",";
		cout << endl;
		for (int i = 0; i < n; i++){
			int Ae, Al;
			for (int j = findFirstNeigh(i); j != -1; j = findNextNeigh(i, j)){
				int weight = get_weight(i, j);
				Ae = Ve[i];
				Al = Vl[j] - weight;
				if (Ae == Al){
					result += weight;
					cout << "< " << i << " , " << j << " >" << endl;
				}
			}
		}

		delete[] Ve;
		delete[] Vl;
		return result;
	}

private:
	int* key_path;
	int** edge;
	int node_size;
	int* indegree;
	stack<int>* non_indegree_stack;
	int findFirstNeigh(int v){
		if (v >= 0 && v < node_size){
			for (int i = 0; i < node_size; i++){
				if (edge[v][i] != 0)
					return i;
			}
		}
		return -1;
	}
	int findNextNeigh(int v, int w){
		if (v >= 0 && v < node_size&&
			w >= 0 && w < node_size - 1){
			for (int i = w + 1; i < node_size; i++){
				if (edge[v][i] != 0)
					return i;
			}
		}
		return -1;
	}
	void clear_egdes(){
		for (int i = 0; i < node_size; i++){
			indegree[i] = 0;
			for (int j = 0; j < node_size; j++)
				edge[i][j] = 0;
		}

	}
	/*
	* remove the node of v
	* and clear the target row_(v)
	*/
	int remove_node(int v){
		if (v < 0 || v >= node_size)
			return -1;
		for (int i = 0; i < node_size; i++){
			if (edge[v][i] != 0){
				edge[v][i] = 0; //clear the target edge
			}
			edge[i][v] = 0;
		}
	}
};