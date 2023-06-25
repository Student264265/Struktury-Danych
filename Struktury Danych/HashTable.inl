//#include "HashTable.h"



template<typename T>
inline HashTable<T>::HashTable(size_t size) :
	SIZE(size),
	COUNT(0)
{
	if(SIZE == 0) throw "HashTableSizeCannotBe0Exemption";

	lists = new List<Element<T>>[SIZE];
}

template<typename T>
inline HashTable<T>::HashTable(const HashTable<T>& other, size_t newSize) :
	SIZE(newSize),
	COUNT(0)
{
	if (SIZE == 0) throw "HashTableSizeCannotBe0Exemption";

	lists = new List<Element<T>>[SIZE];

	for (size_t i = 0; i < other.SIZE; i++)
	{
		List<Element<T>> tempList(other.lists[i]);

		while (!tempList.IsEmpty())
		{
			Element<T> elem = tempList.PopFront();
			InsertElement(elem.val, elem.key);
		}
	}
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	DeleteHashTable();

	delete[] lists;
}



template<typename T>
inline void HashTable<T>::InsertElement(const T& val, const std::string& key)
{
	size_t index = HashFunction(key);

	Element<T> elem(val, key);

	Element<T>* v = nullptr;

	try
	{
		v = &lists[index].GetNode(elem);
	}
	catch (const char* msg)
	{
		lists[index].PushBack(elem);
		COUNT++;
		return;
	}

	*v = elem;
}

template<typename T>
inline T HashTable<T>::RemoveElement(const std::string& key)
{
	if (IsEmpty()) throw "HashTableEmptyExemption";

	size_t index = HashFunction(key);

	Element<T> returnVal;

	try
	{
		Element<T> elem(T(), key);

		returnVal = lists[index].RemoveNode(elem);
	}
	catch (const char* msg)
	{
		throw "HashTableNoSuchKeyExistsExemption";
	}

	COUNT--;
	return returnVal.val;
}



template<typename T>
inline T& HashTable<T>::GetElement(const std::string& key)
{
	if (IsEmpty()) throw "HashTableEmptyExemption";

	size_t index = HashFunction(key);

	Element<T>* returnVal = nullptr;

	try
	{
		Element<T> elem(T(), key);

		returnVal = &lists[index].GetNode(elem);
	}
	catch (const char* msg)
	{
		throw "HashTableNoSuchKeyExistsExemption";
	}

	return returnVal->val;
}

template<typename T>
inline T HashTable<T>::GetElement(const std::string& key) const
{
	if (IsEmpty()) throw "HashTableEmptyExemption";

	size_t index = HashFunction(key);

	Element<T>* returnVal = nullptr;

	try
	{
		Element<T> elem(T(), key);

		returnVal = &lists[index].GetNode(elem);
	}
	catch (const char* msg)
	{
		throw "HashTableNoSuchKeyExistsExemption";
	}

	return returnVal->val;
}



template<typename T>
inline int HashTable<T>::GetRoadLength(const std::string& key) const
{
	if (IsEmpty()) throw "HashTableEmptyExemption";

	size_t index = HashFunction(key);

	int returnRoad = 1;

	try
	{
		Element<T> elem(T(), key);

		returnRoad += lists[index].GetRoadLength(elem);
	}
	catch (const char* msg)
	{
		throw "HashTableNoSuchKeyExistsExemption";
	}

	return returnRoad;
}



template<typename T>
inline size_t HashTable<T>::GetSize() const
{
	return SIZE;
}

template<typename T>
inline size_t HashTable<T>::GetCount() const
{
	return COUNT;
}





template<typename T>
inline void HashTable<T>::DeleteHashTable()
{
	for (size_t i = 0; i < SIZE; i++)
	{
		lists[i].DeleteList();
	}
	
	COUNT = 0;
}

template<typename T>
inline bool HashTable<T>::IsEmpty() const
{
	return COUNT == 0;
}



template<typename T>
inline size_t HashTable<T>::GetIndex(const std::string& key) const
{
	return HashFunction(key);
}



template<typename T>
inline size_t HashTable<T>::HashFunction(const std::string& key) const
{
	return FNV::Hash(key) % SIZE;
}
