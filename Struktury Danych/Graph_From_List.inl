#include "Graph_From_List.h"





template<typename T>
inline GraphAL<T>::GraphAL(const size_t& size, List<T> nodeList) :
	SIZE(size)
{
	if (SIZE == 0) throw "GraphALSizeCannotBe0Exemption";

	nodes = new T[SIZE];
	adjLists = new List<adjElem>[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		nodes[i] = nodeList.PopFront();
	}
}

template<typename T>
GraphAL<T>::GraphAL(const size_t& size) :
	SIZE(size)
{
	if (SIZE == 0) throw "GraphALSizeCannotBe0Exemption";

	nodes = new T[SIZE];
	adjLists = new List<adjElem>[SIZE];
}

template<typename T>
GraphAL<T>::GraphAL(const GraphAL<T>& other) :
	SIZE(other.SIZE)
{
	nodes = new T[SIZE];
	adjLists = new List<adjElem>[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		nodes[i] = other.nodes[i];
		adjLists[i] = other.adjLists[i];
	}
}

template<typename T>
GraphAL<T>::~GraphAL()
{
	delete[] nodes;
	delete[] adjLists;
}



template<typename T>
void GraphAL<T>::SetNode(const size_t& index, const T& val)
{
	if (index >= SIZE) throw "GraphALOutOfBoundsExemption";

	nodes[index] = val;
}

template<typename T>
void GraphAL<T>::SetConnection(const size_t& i1, const size_t& i2, int weight)
{
	if (i1 >= SIZE || i2 >= SIZE) throw "GraphALOutOfBoundsExemption";
	if (i1 == i2) throw "GraphALInvalidConnectionExemption";

	adjElem temp1 = { i1, weight }, temp2 = { i2, weight };

	try
	{
		adjLists[i1].GetNode(temp2).weight = weight;
		adjLists[i2].GetNode(temp1).weight = weight;
	}
	catch (const char*)
	{
		adjLists[i1].PushBack(temp2);
		adjLists[i2].PushBack(temp1);
	}
}



template<typename T>
const T& GraphAL<T>::GetNode(const size_t& index) const
{
	if (index >= SIZE) throw "GraphALOutOfBoundsExemption";

	return nodes[index];
}

template<typename T>
int GraphAL<T>::GetConnection(const size_t& i1, const size_t& i2) const
{
	if (i1 >= SIZE || i2 >= SIZE) throw "GraphALOutOfBoundsExemption";
	if (i1 == i2) throw "GraphALInvalidConnectionExemption";

	adjElem temp2 = { i2, 0 };

	try
	{
		int w = adjLists[i1].GetNode(temp2).weight;
		return w;
	}
	catch (const char*)
	{
		return 0;
	}
}

template<typename T>
inline int GraphAL<T>::GetEdgeWeightSum() const
{
	int ews = 0;

	for (size_t i = 0; i < SIZE; i++)
	{
		List<adjElem> tmpList(adjLists[i]);

		while (!tmpList.IsEmpty())
		{
			ews += tmpList.PopFront().weight;
		}
	}

	return ews / 2;
}

template<typename T>
inline int GraphAL<T>::GetEdgeNum() const
{
	int eNum = 0;

	for (size_t i = 0; i < SIZE; i++)
	{
		List<adjElem> tmpList(adjLists[i]);

		while (!tmpList.IsEmpty())
		{
			eNum++;
			tmpList.PopFront();
		}
	}

	return eNum / 2;
}





struct PQitem
{
	size_t i1, i2;
	int weight;

	bool operator<=(const PQitem& other) const
	{
		return weight <= other.weight;
	}
};


template<typename T>
void GraphAL<T>::CreateMSTPrim()
{
	List<PQitem> finalNodes;


	int edgeNum = 0;

	// create an array to track selected nodes
	bool* selected = new bool[SIZE];
	for(int i = 0; i < SIZE; i++)
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
							val = adjLists[i].GetNode({ j, 0 }).weight;

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
		finalNodes.PushBack({ x, y, min });

		selected[y] = true;
		edgeNum++;
	}


	delete[] selected;


	// Update graph with MST edges
	for (size_t i = 0; i < SIZE; i++)
	{
		adjLists[i].DeleteList();
	}

	while (!finalNodes.IsEmpty())
	{
		PQitem item = finalNodes.PopFront();

		adjLists[item.i1].PushBack({ item.i2, item.weight });
		adjLists[item.i2].PushBack({ item.i1, item.weight });
	}
}