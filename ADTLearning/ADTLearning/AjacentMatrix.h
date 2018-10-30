#include"Graph.h"

//Adjacency matrix denotes the graph
template <typename T, typename E>
class GraphMatrix :public Graph<T, E>{
	friend std::istream& operator>>(std::istream in, GraphMatrix<T, E>& G);
	friend std::ostream& operator<<(std::ostream out, GraphMatrix<T, E>& G);
public:
	GraphMatrix(int sz = DefaultVertices);
	~GraphMatrix(){ delete[] Edge; delete[] VerticesList; }
	T getVal(const int i)const{
		return i >= 0 && i <= numVertices ? VerticesList[i] : nullptr;
	}     //get the value of the target vertex i .

	E getWeight(const int v1,const int v2)const{
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : nullptr;
	}  //get the weight of the target edge i .

	int getFirstNeighbor(const int v)const;  //get the first neighbor of the vertex v .
	int getNextNeightbor(const int v, const  int w)const; //Get the neighbor w's next neighbor.
	bool insertVertex(const T& vertex);      //insert the vertex.
	bool insertEdge(const int v1, const int v2, const  E weight);  //(v1,v2) and the weight.
	bool removeVertex(const int v);
	bool removeEdge(const int v1, const int v2);

private:
	T* VerticesList;           //The list of the vertex.
	E** Edge;				   //The digram of the edges.
	int getVertexPos(T vertex){
		for (int i = 0; i < numVertices; i++){
			if (VerticesList[i] == vertex)return i;
		}
		return -1;
	}
};