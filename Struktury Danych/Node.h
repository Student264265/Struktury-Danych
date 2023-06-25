#pragma once



template<typename T>
struct node
{
	T val;
	node<T>* next;

	node() : next(nullptr) {}
};
