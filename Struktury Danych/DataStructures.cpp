#include "DataStructures.h"



DataStructures::DataStructures()
{
	srand(time(NULL));
}

DataStructures::~DataStructures()
{
	
}






void DataStructures::Run()
{
	GraphProgram();
}



void DataStructures::HashTableProgram()
{
	HashTable<float>* table = new HashTable<float>(8);
	List<string> keyList;

	char option = 'a';
	while (1)
	{
		cout << "Welcome to HashTable menu, what would you like to do?\n";
		cout << "1. Add Element (float).\n";
		cout << "2. Get Element.\n";
		cout << "3. Remove Element.\n";
		cout << "4. Get size and count.\n";
		cout << "5. Display HashTable.\n";
		cout << "6. Get minimum, maximum and average length of road to elements.\n";
		cout << "7. Change HashTable size.\n";
		cout << "8. Remove all elements of HashTable.\n";
		cout << "9. Get all keys (Don't tell anyone).\n";
		cout << "0. End Task.\n";
		cin >> option;
		cout << "\n\n";

		switch (option)
		{
		case '1':
		{
			float val;
			string key;
			
			cout << "Enter value (float) and key (string) : ";
			cin >> val >> key;

			table->InsertElement(val, key);

			try
			{
				keyList.GetNode(key);
			}
			catch (const char* msg)
			{
				keyList.PushBack(key);
			}

			break;
		}
		case '2':
		{
			string key;
			cout << "Please enter key (string) : ";
			cin >> key;

			try
			{
				cout << "\nYour value is : " << table->GetElement(key) << '\n';
			}
			catch (const char* msg)
			{
				cout << "\nError. You got " << msg << "-ed.\n";
			}

			break;
		}
		case '3':
		{
			string key;
			cout << "Please enter key (string) : ";
			cin >> key;

			try
			{
				cout << "\nRemoved value is : " << table->RemoveElement(key) << '\n';
				keyList.RemoveNode(key);
			}
			catch (const char* msg)
			{
				cout << "\nError. You got " << msg << "-ed.\n";
			}

			break;
		}
		case '4':
		{
			cout << "HashTable size as an array : " << table->GetSize() << '\n';
			cout << "Number of elements inside HashTable : " << table->GetCount() << '\n';

			break;
		}
		case '5':
		{
			cout << "HashTable contents :\n";
			DisplayHashTable(*table, keyList);

			break;
		}
		case '6':
		{
			int min = 0, max = 0, sum = 0, num = 0;;

			List<string> tempList(keyList);

			try
			{
				int r = table->GetRoadLength(tempList.PopFront());

				min = max = r;

				sum += r;
				num++;
			}
			catch(const char* msg)
			{
				cout << "Error. You got " << msg << "-ed.\n";
				break;
			}
			

			while (!tempList.IsEmpty())
			{
				try
				{
					int r = table->GetRoadLength(tempList.PopFront());
					
					if (r < min) min = r;
					else if (r > max) max = r;

					sum += r;
					num++;
				}
				catch (const char* msg)
				{
					cout << "Error. You got " << msg << "-ed.\n";
				}
			}

			cout << "Minimum road is : " << min << '\n';
			cout << "Maximum road is : " << max << '\n';
			cout << "Average road is : " << float(sum) / float(num) << '\n';

			break;
		}
		case '7':
		{
			size_t newSize;

			cout << "Please enter the new size for HashTable : ";
			cin >> newSize;

			try
			{
				HashTable<float>* newTable = new HashTable<float>(*table, newSize);

				delete table;
				table = newTable;
			}
			catch (const char* msg)
			{
				cout << "\nError. You got " << msg << "-ed.\n";
			}

			break;
		}
		case '8':
		{
			cout << "Removing all elements.\n";

			table->DeleteHashTable();
			keyList.DeleteList();

			break;
		}
		case '9':
		{
			cout << "In case you forgot your keys, here they are :\n";

			List<string> tmpList(keyList);

			while (!tmpList.IsEmpty())
			{
				cout << tmpList.PopFront() << '\n';
			}

			break;
		}
		case '0':
			cout << "Ending Task.\n";
			delete table;
			return;

		default:
			cout << "Unknown command.\n";
		}

		cout << "\n\n";
	}
}



void DataStructures::GraphProgram()
{
	GraphAL<string>* graphAl = nullptr;
	GraphHT* graphHt = nullptr;

	const size_t sampleNum = 6;
	size_t samplesSizes[sampleNum] = {
		10, 50, 100, 500, 1000, 1500
	};

	double times[sampleNum][4][4] = { 0 };
	int sNum = 3;
	int f = 3;

	
	
	List<edgeItem> graphEdges;

	List<string> nodeNames;
	for (int i = 0; i < samplesSizes[sNum]; i++)
	{
		nodeNames.PushBack(to_string(i));
	}



	graphAl = new GraphAL<string>(samplesSizes[sNum]);
	graphHt = new GraphHT(samplesSizes[sNum]);



	cout << "--------------------------------\nSize : " << samplesSizes[sNum] << " | fill : " << float(f + 1) * 0.25 << '\n';

	auto start = std::chrono::high_resolution_clock::now();
	GenerateRandomGraph(graphEdges, samplesSizes[sNum], nodeNames, float(f + 1) * 0.25, 1, 1000);
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationChrono = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	double duration = static_cast<double>(durationChrono.count()) / 1000.0;
	cout << "Generating done : " << duration << "\n";
	times[sNum][0][f] = duration;

	start = std::chrono::high_resolution_clock::now();
	CopyToGALandGHT(*graphAl, *graphHt, nodeNames, graphEdges);
	stop = std::chrono::high_resolution_clock::now();
	durationChrono = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	duration = static_cast<double>(durationChrono.count()) / 1000.0;
	cout << "Copying done : " << duration << "\n\n";
	times[sNum][1][f] = duration;

	start = std::chrono::high_resolution_clock::now();
	graphAl->CreateMSTPrim();
	stop = std::chrono::high_resolution_clock::now();
	durationChrono = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	duration = static_cast<double>(durationChrono.count()) / 1000.0;
	cout << "GraphAL Prim done : " << duration << '\n';
	times[sNum][2][f] = duration;

	start = std::chrono::high_resolution_clock::now();
	graphHt->CreateMSTPrim(nodeNames);
	stop = std::chrono::high_resolution_clock::now();
	durationChrono = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	duration = static_cast<double>(durationChrono.count()) / 1000.0;
	cout << "GraphHt Prim done : " << duration << "\n--------------------------------\n\n";
	times[sNum][3][f] = duration;

	cout << "Edge number : " << graphAl->GetEdgeNum() << ", " << graphHt->GetEdgeNum(nodeNames) << " | ";
	cout << "Edge weight : " << graphAl->GetEdgeWeightSum() << ", " << graphHt->GetEdgeWeightSum(nodeNames) << "\n\n";



	delete graphAl;
	delete graphHt;
	


	cout << "\n\n\n\n\n";

	string fNames[4] = { "fill25.csv", "fill50.csv", "fill75.csv", "fill100.csv" };
	
	ofstream file(fNames[f], ios::app);

	if (file.is_open())
	{
		//cout << "a,\t\t" << "b,\t\t" << "c,\t\t" << "d,\t\t" << "e\n";
		//file << "a,\t\t" << "b,\t\t" << "c,\t\t" << "d,\t\t" << "e\n";

		
		cout << samplesSizes[sNum] << ",\t\t";
		file << samplesSizes[sNum] << ",\t\t";
		
		cout << times[sNum][0][f] << ",\t\t" << times[sNum][1][f] << ",\t\t" << times[sNum][2][f] << ",\t\t" << times[sNum][3][f] << "\n";
		file << times[sNum][0][f] << ",\t\t" << times[sNum][1][f] << ",\t\t" << times[sNum][2][f] << ",\t\t" << times[sNum][3][f] << "\n";


		cout << "\n\n\n";

		file.close();
	}
}




/*

	char option = 'a';
	while (1)
	{
		cout << "Welcome to Graph menu, what would you like to do?\n";
		cout << "1. Generate random Graph.\n";
		cout << "2. Set Nodes.\n";
		cout << "3. Set Edges.\n";
		cout << "4. Display Graph.\n";
		cout << "5. Create MST from Prim algorithm.\n";
		cout << "0. End Task.\n";
		cin >> option;
		cout << "\n\n";

		switch (option)
		{
		case '1':
		{


			break;
		}
		case '2':
		{


			break;
		}
		case '3':
		{


			break;
		}
		case '4':
		{


			break;
		}
		case '5':
		{


			break;
		}
		case '0':
			cout << "Ending Task.\n";

			return;

		default:
			cout << "Unknown command.\n";
		}

		cout << "\n\n";
	}
*/