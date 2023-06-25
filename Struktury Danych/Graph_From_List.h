#pragma once

#include "List.h"




struct adjElem
{
	size_t index;
	int weight;

	bool operator==(const adjElem& other) const
	{
		return index == other.index;
	}
};



template<typename T>
class GraphAL
{
public:
	GraphAL(const size_t& size, List<T> nodeList);
	GraphAL(const size_t& size);
	GraphAL(const GraphAL<T>& other);
	~GraphAL();

	void SetNode(const size_t& index, const T& val);
	void SetConnection(const size_t& i1, const size_t& i2, int weight);

	const T& GetNode(const size_t& index) const;
	int GetConnection(const size_t& i1, const size_t& i2) const;
	const size_t& GetSize() const { return SIZE; }
	int GetEdgeWeightSum() const;
	int GetEdgeNum() const;

	void CreateMSTPrim();

private:
	T* nodes;
	const size_t SIZE;
	List<adjElem>* adjLists;
};




#include "Graph_From_List.inl"