#pragma once

#include "Node.h"



template<typename T>
class List
{
public:
	List();
	List(const List<T>& other);
	~List();

	void PushFront(const T& val);
	void PushBack(const T& val);

	T Front() const;
	T Back() const;

	T PopFront();
	T PopBack();

	T RemoveNode(const T& val);
	T& GetNode(const T& val);
	T GetNode(const T& val) const;

	int GetRoadLength(const T& val) const;

	size_t Size() const;

	void DeleteList();
	bool IsEmpty() const;

protected:
	node<T>* head;
	node<T>* tail;
};



#include "List.inl"