#include<iostream>
#include"TopoGraph.h"

int main(){
	char * file_name = "test.txt";
	TopoGraph t(20);
	t.Initialize(file_name);
	cout << t.AOE(9) << endl; 
	cin.get();
}