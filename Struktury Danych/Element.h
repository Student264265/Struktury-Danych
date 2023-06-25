#pragma once

#include <iostream>



template<typename T>
struct Element
{
	T val;
	std::string key;

	Element(const T& v = T(), const std::string& k = "") :
		val(v),
		key(k)
	{}

	Element<T>& operator=(const Element<T>& right)
	{
		if (this == &right) return *this;

		val = right.val;
		key = right.key;

		return *this;
	}

	bool operator==(const Element<T>& right)
	{
		return key == right.key;
	}
};

