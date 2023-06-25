#pragma once

#include "HashTable.h"




class GraphHT
{
public:
	GraphHT(const size_t& size, List<std::string> nodeList);
	GraphHT(const size_t& size);
	GraphHT(const GraphHT& other);
	~GraphHT();

	void AddNode(const std::string& n);
	void SetConnection(const std::string& n1, const std::string& n2, int weight);

	const size_t& GetNodeIndex(const std::string& n) const;
	int GetConnection(const std::string& n1, const std::string& n2) const;
	const size_t& GetSize() const { return SIZE; }
	int GetEdgeWeightSum(List<std::string> nodeList) const;
	int GetEdgeNum(List<std::string> nodeList) const;

	void CreateMSTPrim(List<std::string> nodeList);

private:
	HashTable<size_t>* nodes;
	const size_t SIZE;
	HashTable<int>** hashTableLists;
};
