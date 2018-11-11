#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node{
	int element;
	Position Next;
};

struct Node CurSorSpace[1024];
