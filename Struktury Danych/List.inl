



template<typename T>
inline List<T>::List() :
	head(nullptr),
	tail(nullptr)
{}

template<typename T>
inline List<T>::List(const List<T>& other) :
	head(nullptr),
	tail(nullptr)
{
	node<T>* currentNode = other.head;

	while (currentNode != nullptr)
	{
		PushBack(currentNode->val);
		currentNode = currentNode->next;
	}
}

template<typename T>
inline List<T>::~List()
{
	DeleteList();
}



template<typename T>
inline void List<T>::PushFront(const T& val)
{
	node<T>* newNode = new node<T>();
	newNode->val = val;
	newNode->next = head;
	head = newNode;

	if (head->next == nullptr) tail = newNode;
}

template<typename T>
inline void List<T>::PushBack(const T& val)
{
	if (IsEmpty())
	{
		head = new node<T>();
		head->val = val;
		tail = head;
		return;
	}

	node<T>* newNode = new node<T>();
	newNode->val = val;
	tail->next = newNode;
	tail = newNode;
}



template<typename T>
inline T List<T>::Front() const
{
	if (IsEmpty()) throw "ListEmptyExemption";
	return head->val;
}

template<typename T>
inline T List<T>::Back() const
{
	if (IsEmpty()) throw "ListEmptyExemption";
	return tail->val;
}



template<typename T>
inline T List<T>::PopFront()
{
	if (IsEmpty()) throw "ListEmptyExemption";

	node<T>* firstNode = head;
	head = head->next;

	T returnVal = firstNode->val;
	delete firstNode;

	if (IsEmpty()) tail = nullptr;

	return returnVal;
}

template<typename T>
inline T List<T>::PopBack()
{
	if (IsEmpty()) throw "ListEmptyExemption";

	T returnVal = tail->val;

	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;

		return returnVal;
	}

	node<T>* currentNode = head;
	while (currentNode->next != tail)
	{
		currentNode = currentNode->next;
	}

	delete tail;
	tail = currentNode;
	currentNode->next = nullptr;

	return returnVal;
}



template<typename T>
inline T List<T>::RemoveNode(const T& val)
{
	if (IsEmpty()) throw "ListEmptyExemption";

	if (head->val == val)
	{
		return PopFront();
	}

	node<T>* currentNode = head;
	while (currentNode->next != nullptr)
	{
		if (currentNode->next->val == val)
		{
			T returnVal = currentNode->next->val;

			node<T>* nextNode = currentNode->next->next;
			delete currentNode->next;
			currentNode->next = nextNode;

			return returnVal;
		}

		currentNode = currentNode->next;
	}

	throw "ListNoSuchValueExemption";
}

template<typename T>
inline T& List<T>::GetNode(const T& val)
{
	if (IsEmpty()) throw "ListEmptyExemption";

	node<T>* currentNode = head;
	while (currentNode != nullptr)
	{
		if (currentNode->val == val)
		{
			return currentNode->val;
		}

		currentNode = currentNode->next;
	}

	throw "ListNoSuchValueExemption";
}

template<typename T>
inline T List<T>::GetNode(const T& val) const
{
	if (IsEmpty()) throw "ListEmptyExemption";

	node<T>* currentNode = head;
	while (currentNode != nullptr)
	{
		if (currentNode->val == val)
		{
			return currentNode->val;
		}

		currentNode = currentNode->next;
	}

	throw "ListNoSuchValueExemption";
}



template<typename T>
inline int List<T>::GetRoadLength(const T& val) const
{
	if (IsEmpty()) throw "ListEmptyExemption";

	int road = 1;

	node<T>* currentNode = head;
	while (currentNode != nullptr)
	{
		if (currentNode->val == val)
		{
			return road;
		}

		currentNode = currentNode->next;
		road++;
	}

	throw "ListNoSuchValueExemption";
}



template<typename T>
inline size_t List<T>::Size() const
{
	size_t size = 0;

	node<T>* currentNode = head;
	while (currentNode != nullptr)
	{
		size++;
		currentNode = currentNode->next;
	}

	return size;
}



template<typename T>
inline void List<T>::DeleteList()
{
	while (head != nullptr)
	{
		node<T>* currentNode = head;
		head = head->next;
		delete currentNode;
	}

	tail = nullptr;
}

template<typename T>
inline bool List<T>::IsEmpty() const
{
	return head == nullptr;
}