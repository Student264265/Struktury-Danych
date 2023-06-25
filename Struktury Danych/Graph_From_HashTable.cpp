#include "Graph_From_HashTable.h"



GraphHT::GraphHT(const size_t& size, List<std::string> nodeList) :
	SIZE(size)
{
	if (SIZE == 0) throw "GraphHTSizeCannotBe0Exemption";

	nodes = new HashTable<size_t>(SIZE);
	hashTableLists = new HashTable<int>*[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		nodes->InsertElement(i, nodeList.PopFront());

		hashTableLists[i] = new HashTable<int>(SIZE - 1);
	}
}

GraphHT::GraphHT(const size_t& size) :
	SIZE(size)
{
	if (SIZE == 0) throw "GraphHTSizeCannotBe0Exemption";

	nodes = new HashTable<size_t>(SIZE);
	hashTableLists = new HashTable<int>*[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		hashTableLists[i] = new HashTable<int>(SIZE - 1);
	}
}

GraphHT::GraphHT(const GraphHT& other) :
	SIZE(other.SIZE)
{
	nodes = new HashTable<size_t>(*other.nodes, SIZE);
	hashTableLists = new HashTable<int>*[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		hashTableLists[i] = new HashTable<int>(*other.hashTableLists[i], SIZE - 1);
	}
}

GraphHT::~GraphHT()
{
	for (size_t i = 0; i < SIZE; i++)
	{
		delete hashTableLists[i];
	}
	delete[] hashTableLists;

	delete nodes;
}



void GraphHT::AddNode(const std::string& n)
{
	size_t count = nodes->GetCount();

	if (count == SIZE) throw "GraphHTNodeLimitReachedExemption";

	nodes->InsertElement(count, n);
}

void GraphHT::SetConnection(const std::string& n1, const std::string& n2, int weight)
{
	if (n1 == n2) throw "GraphHTInvalidConnectionExemption";

	size_t index1, index2;

	try
	{
		index1 = nodes->GetElement(n1);
		index2 = nodes->GetElement(n2);
	}
	catch (const char* msg)
	{
		std::string thr = "GraphHTExemption : ";
		thr.append(msg);
		throw thr.c_str();
	}


	hashTableLists[index1]->InsertElement(weight, n2);
	hashTableLists[index2]->InsertElement(weight, n1);
}



const size_t& GraphHT::GetNodeIndex(const std::string& n) const
{
	size_t index;

	try
	{
		index = nodes->GetElement(n);
	}
	catch (const char* msg)
	{
		throw "GraphHTNoSuchNodeExistsExemption";
	}

	return index;
}

int GraphHT::GetConnection(const std::string& n1, const std::string& n2) const
{
	if (n1 == n2) throw "GraphHTInvalidConnectionExemption";

	size_t index1, index2;

	try
	{
		index1 = nodes->GetElement(n1);
		index2 = nodes->GetElement(n2);
	}
	catch (const char* msg)
	{
		std::string thr = "GraphHTExemption : ";
		thr.append(msg);
		throw thr.c_str();
	}


	int weight;
	try
	{
		weight = hashTableLists[index1]->GetElement(n2);
	}
	catch (const char* msg)
	{
		return 0;
	}

	return weight;
}

int GraphHT::GetEdgeWeightSum(List<std::string> nodeList) const
{
	int ews = 0;

	std::string* nNames = new std::string[SIZE];
	for (size_t i = 0; i < SIZE; i++)
	{
		nNames[i] = nodeList.PopFront();
	}

	for (size_t i = 0; i < SIZE; i++)
	{
		size_t index = nodes->GetElement(nNames[i]);

		for (size_t j = 0; j < SIZE; j++)
		{
			if (i == j) continue;

			try
			{
				ews += hashTableLists[index]->GetElement(nNames[j]);
			}
			catch (const char* msg)
			{

			}
		}
	}

	delete[] nNames;

	return ews / 2;
}

int GraphHT::GetEdgeNum(List<std::string> nodeList) const
{
	int eNum = 0;

	for (size_t i = 0; i < SIZE; i++)
	{
		size_t index = nodes->GetElement(nodeList.PopFront());

		eNum += hashTableLists[index]->GetCount();
	}

	return eNum / 2;
}






struct HTLitem
{
	size_t index1, index2;
	int weight;
};

void GraphHT::CreateMSTPrim(List<std::string> nodeList)
{
	std::string* nNames = new std::string[SIZE];
	for (size_t i = 0; i < SIZE; i++)
	{
		nNames[i] = nodeList.PopFront();
	}


	List<HTLitem> finalNodes;


	int edgeNum = 0;

	// create an array to track selected nodes
	bool* selected = new bool[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		selected[i] = false;
	}

	selected[0] = true;

	size_t x;  //  node allready in MST
	size_t y;  //  node not in MST


	while (edgeNum < SIZE - 1)
	{
		int min = 0x7FFFFFFF;
		x = 0;
		y = 0;

		int val;

		for (size_t i = 0; i < SIZE; i++)
		{
			if (selected[i])
			{
				for (size_t j = 0; j < SIZE; j++)
				{
					if (!selected[j])
					{
						try
						{
							val = hashTableLists[i]->GetElement(nNames[j]);

							if (val < min) {
								min = val;
								x = i;
								y = j;
							}
						}
						catch (const char* msg)
						{

						}
					}
				}
			}
		}

		// Add smallest edge to MST
		finalNodes.PushBack({ x, y, min});

		selected[y] = true;
		edgeNum++;
	}


	delete[] selected;


	// Update graph with MST edges
	for (size_t i = 0; i < SIZE; i++)
	{
		hashTableLists[i]->DeleteHashTable();
	}

	while (!finalNodes.IsEmpty())
	{
		HTLitem item = finalNodes.PopFront();

		hashTableLists[item.index1]->InsertElement(item.weight, nNames[item.index2]);
		hashTableLists[item.index2]->InsertElement(item.weight, nNames[item.index1]);
	}

	delete[] nNames;
}
