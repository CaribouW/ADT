#include"laucher.h"
#ifdef Sibling
#include<iostream>

template <class T>
struct Node{
	T data;
	Node<T>* firstChild, *nextSibling;
	Node<T>(T value = 0, Node<T>* fc = nullptr, Node<T>* ns = nullptr) : data(value),
		firstChild(fc), nextSibling(ns){}
};

template <class T>
class Sibling_tree{

};


#endif