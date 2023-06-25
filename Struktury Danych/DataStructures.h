#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "HashTable.h"
#include "Graph_From_List.h"
#include "Graph_From_HashTable.h"

using namespace std;



struct edgeItem
{
	size_t index1, index2;
	int weight;
};



class DataStructures
{
public:
	DataStructures();
	~DataStructures();

	void Run();

	void HashTableProgram();
	void GraphProgram();

private:
	template<typename T>
	void DisplayHashTable(const HashTable<T>& ht, const List<string>& l)
	{
		List<string> tempKeyList(l);
		List<T>* htLists = new List<T>[ht.GetSize()];

		while (!tempKeyList.IsEmpty())
		{
			try
			{
				string key = tempKeyList.PopFront();
				htLists[ht.GetIndex(key)].PushBack(ht.GetElement(key));
			}
			catch (const char* msg)
			{
				throw msg;
			}
		}

		for (size_t i = 0; i < ht.GetSize(); i++)
		{
			cout << i << ".\t";

			while (!htLists[i].IsEmpty())
			{
				cout << htLists[i].PopFront() << '\t';
			}

			cout << '\n';
		}
	}

	template<typename T>
	void DisplayGFL(const GraphAL<T>& gfl)
	{
		size_t size = gfl.GetSize();

		cout << "node\t     node:edge\n";
		for (size_t i = 0; i < size; i++)
		{
			cout << gfl.GetNode(i) << "\t->";

			for (size_t j = 0; j < size; j++)
			{
				if (j == i) continue;

				int w = gfl.GetConnection(i, j);
				if (w) cout << '\t' << gfl.GetNode(j) << ':' << w;
			}

			cout << '\n';
		}

		cout << "Num of edges : " << gfl.GetEdgeNum() << '\n';
		cout << "Sum of edges : " << gfl.GetEdgeWeightSum() << '\n';
	}

	void DisplayGFH(const GraphHT& ght, List<std::string> nodeNames)
	{
		int eNum = ght.GetEdgeNum(nodeNames), ews = ght.GetEdgeWeightSum(nodeNames);
		size_t size = ght.GetSize();

		std::string* nNames = new std::string[size];
		for (size_t i = 0; i < size; i++)
		{
			nNames[i] = nodeNames.PopFront();
		}

		cout << "node\t     node:edge\n";
		for (size_t i = 0; i < size; i++)
		{
			cout << nNames[i] << "\t->";
			for (size_t j = 0; j < size; j++)
			{
				if (i == j) continue;

				int w = ght.GetConnection(nNames[i], nNames[j]);
				if(w) cout << '\t' << nNames[j] << ':' << w;
			}
			cout << '\n';
		}

		delete[] nNames;

		cout << "Num of edges : " << eNum << '\n';
		cout << "Sum of edges : " << ews << '\n';
	}

	template<typename T>
	void GenerateRandomGraph(List<edgeItem>& graphEdges, size_t size, List<T> nodeNames, float fill, int minW, int maxW)
	{
		if (fill >= 0.9999)
		{
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = i + 1; j < size; j++)
				{
					graphEdges.PushBack({ i, j, minW + rand() % (maxW - minW + 1) });
				}
			}

			return;
		}


		List<size_t>* edges = new List<size_t>[size];

		size_t* randVer = new size_t[size];
		for (size_t i = 0; i < size; i++)
		{
			randVer[i] = i;
		}


		for (size_t i = 0; i < size; i++)
		{
			for (size_t max = size - 1; max > 0; max--)
			{
				size_t r = rand() % max;

				size_t tmp = randVer[max];
				randVer[max] = randVer[r];
				randVer[r] = tmp;
			}


			for (size_t j = 0; j < size; j++)
			{
				if (i != randVer[j]) edges[i].PushBack(randVer[j]);
			}
		}


		List<std::pair<size_t, size_t>> finalEdges;

		{
			int numOfVisited = 1;

			while (numOfVisited < size)
			{
				size_t V1 = randVer[rand() % numOfVisited];
				size_t V2index = numOfVisited + rand() % (size - numOfVisited);
				size_t V2 = randVer[V2index];


				edges[V1].RemoveNode(V2);
				edges[V2].RemoveNode(V1);


				finalEdges.PushBack({ V1, V2 });

				size_t tmp = randVer[numOfVisited];
				randVer[numOfVisited] = randVer[V2index];
				randVer[V2index] = tmp;

				numOfVisited++;
			}
		}


		int numOfNotEmpty = size;
		for (size_t i = 0; i < numOfNotEmpty; i++)
		{
			while (edges[randVer[i]].IsEmpty())
			{
				randVer[i] = randVer[numOfNotEmpty - 1];

				numOfNotEmpty--;
			}
		}

		int fEdgeNum = fill * size * (size - 1) / 2.0 - size + 1;
		for (int i = 0; i < fEdgeNum; i++)
		{
			size_t V1index = rand() % numOfNotEmpty;
			size_t V1 = randVer[V1index], V2;

			while (edges[V1].IsEmpty())
			{
				randVer[V1index] = randVer[numOfNotEmpty - 1];
				V1 = randVer[V1index];

				numOfNotEmpty--;
			}

			V2 = edges[V1].PopFront();
			edges[V2].RemoveNode(V1);

			finalEdges.PushBack({ V1, V2 });
		}


		while(!finalEdges.IsEmpty())
		{
			std::pair<size_t, size_t> v_v = finalEdges.PopFront();

			graphEdges.PushBack({ v_v.first, v_v.second, minW + rand() % (maxW - minW + 1) });
		}



		delete[] edges;
		delete[] randVer;
	}


	void CopyToGALandGHT(GraphAL<std::string>& gal, GraphHT& ght, List<std::string> nodeNames, List<edgeItem> graphEdges)
	{
		size_t size = nodeNames.Size();

		std::string* nNames = new std::string[size];
		for (size_t i = 0; i < size; i++)
		{
			nNames[i] = nodeNames.PopFront();
			gal.SetNode(i, nNames[i]);
			ght.AddNode(nNames[i]);
		}


		while (!graphEdges.IsEmpty())
		{
			edgeItem edi = graphEdges.PopFront();

			gal.SetConnection(edi.index1, edi.index2, edi.weight);
			ght.SetConnection(nNames[edi.index1], nNames[edi.index2], edi.weight);
		}


		delete[] nNames;
	}
};