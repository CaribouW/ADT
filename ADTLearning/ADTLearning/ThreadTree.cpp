#include<iostream>
#define THREAD_TREE

#ifdef THREAD_TREE
template <class T>
struct ThreadNode{
	int l_tag, r_tag;   // tag=1 then the ptr is pointed to the child , otherwise the node 
						// is pointed to the next or the last position in the inOrder.

};

#endif