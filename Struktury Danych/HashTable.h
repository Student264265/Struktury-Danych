#pragma once

#include <iostream>
#include "List.h"
#include "Element.h"



template<typename T>
class HashTable
{
public:
	HashTable(size_t size);
	HashTable(const HashTable<T>& other, size_t newSize);
	~HashTable();

	void InsertElement(const T& val, const std::string& key);
	T RemoveElement(const std::string& key);

	T& GetElement(const std::string& key);
	T GetElement(const std::string& key) const;

	int GetRoadLength(const std::string& key) const;

	size_t GetSize() const;
	size_t GetCount() const;

	void DeleteHashTable();
	bool IsEmpty() const;

	size_t GetIndex(const std::string& key) const;

private:
	const size_t SIZE;
	size_t COUNT;
	List<Element<T>>* lists;

	size_t HashFunction(const std::string& key) const;
};






namespace FNV
{
	static constexpr size_t Prime = 0x00000100000001B3;
	static constexpr size_t Offset_Basis = 0xCBF29CE484222325;

	static size_t Hash(const std::string& key)
	{
		size_t hash = Offset_Basis;
		size_t length = key.length();

		for (size_t i = 0; i < length; i++)
		{
			hash ^= key[i];
			hash *= Prime;
		}

		return hash;
	}
}



#include "HashTable.inl"
