#include<iostream>
const int DefaultVertices = 30;

template <typename T,typename E>
class Graph{
public:
	const E maxWeight;
	Graph(int sz = DefaultVertices);
	~Graph();
	bool GraphEmpty()const{ return numEdges == 0; }
	bool GraphFull()const{
		if (numVertices == maxVertices ||
			numEdges == maxVertices*(maxVertices - 1) / 2)
			return true;
		else
			return false;
	}
	int NumberOfVertices()const{ return numVertices; }
	int NumberOfEdges()const{ return numEdges; }
	virtual T getVal(const int i)const;     //get the value of the target vertex i .
	virtual E getWeight(const int v1,const int v2)const;  //get the weight of the target edge i .
	virtual int getFirstNeighbor(const int v)const;  //get the first neighbor of the vertex v .
	virtual int getNextNeightbor(const int v,const  int w)const; //Get the neighbor w's next neighbor.
	virtual bool insertVertex(const T& vertex);      //insert the vertex.
	virtual bool insertEdge(const int v1, const int v2,const  E weight);  //(v1,v2) and the weight.
	virtual bool removeVertex(const int v);
	virtual bool removeEdge(const int v1, const int v2);


protected:
	int maxVertices;
	int numEdges;
	int numVertices;				  //current numbers of the vertices
	virtual int getVertex(T vertex);  //get the position of the vertex
};
