#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
/*/////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: linked_list.h
	Template(s): Node and LinkedList

	Purpose: Node is a data container, LinkedList is a datastructure of nodes
*//////////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////
	Node holds data and some pointers to the next & previous node
*/////////////////////////////////////////////////////////////////
template <class T>
class LinkedList;

template <class T>
struct Node
{
friend class LinkedList<T>;
private:
	Node<T> * m_next;
	Node<T> * m_prev;
	T m_data;
};


template <class T>
class LinkedList
{
private:
	Node<T> * m_head;
	Node<T> * m_current;
	Node<T> * m_tail;
	bool Find(const Node<T> & n) const;
public:
	LinkedList();
	LinkedList(const T data);
	~LinkedList();

	void SetData(T data);
	const T GetData() const;

	void NextNode();
	void PreviousNode();

	void Insert(const T in);
	bool Delete(Node<T> * out);

	void Purge();
	void Display() const;
};
//default ctor
template <class T>
LinkedList<T>::LinkedList(): m_head(nullptr), m_tail(nullptr), m_current(nullptr)
{}
//one arg ctor, takes in data and assigns m_next and m_prev as nullptr
template <class T>
LinkedList<T>::LinkedList(const T data): m_head(new Node<T>(data)), m_tail(m_head), m_current(m_head)
{
	m_head->m_next(nullptr);
	m_head->m_prev(nullptr);
}

//default dtor, calls purge on exit to free memory
template <class T>
LinkedList<T>::~LinkedList()
{
	Purge();
}

/*//////////////////////////////////////////////////////
	SetData sets/overwrites the data of the current node
*///////////////////////////////////////////////////////
template<class T>
void LinkedList<T>::SetData(T data)
{
	m_current->m_data = data;
}

/*/////////////////////////////////////////////////
	GetData returns a constant version of the data
*//////////////////////////////////////////////////
template<class T>
const T LinkedList<T>::GetData() const
{
	return m_current->m_data;
}

/*///////////////////////////////////////////////////////////////////////////////////////
	Next node checks the next node and then sets the current pointer to the next pointer. 
*////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void LinkedList<T>::NextNode()
{
	if (m_current->m_next != nullptr)
	{
		m_current = m_current->m_next;
	}
	else
	{
		m_current = m_head;
	}
}

/*////////////////////////////////////////////////////////////////
	Previous Node checks the previous node and then sets the
	current pointer as the previous node
*/////////////////////////////////////////////////////////////////
template<class T>
void LinkedList<T>::PreviousNode()
{
	if (m_current->m_prev != nullptr)
	{
		m_current = m_current->m_prev;
	}
	else
	{
		m_current = m_tail;
	}
}

/*//////////////////////////////////////////////////////////////////////////////////
	Find returns true if a given node is found (typically used in delete or purge)
		returns false if the node is not found
*///////////////////////////////////////////////////////////////////////////////////
template <class T>
bool LinkedList<T>::Find(const Node<T> & n) const
{
	bool found = false;
	Node<T> * travel = m_head;
	if (m_current->m_data == n.m_data)
	{
		found = true;
	}
	while (!found && travel->m_next != nullptr)
	{
		if (n.m_data == travel->m_data)
		{
			found = true;
		}
		else
		{
			travel = travel->m_next;
		}
	}
	return found;
}

/*///////////////////////////////////////////////////////////////////////
	Insert is a append style insert, only inserts at the end of the list
*////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::Insert(const T in)
{
	m_tail->m_next = new Node<T>(in);
	m_tail->m_next->m_prev = m_tail;
	m_tail = m_tail->m_next;
}

/*////////////////////////////////////////////////////////
	Delete searches for the node to delete, and then does
	returns true or false if it was deleted or not
*/////////////////////////////////////////////////////////
template <class T>
bool LinkedList<T>::Delete(Node<T> * out)
{
	bool found = false;

	Node<T> * travel = m_head;

	while (travel != nullptr && travel->m_data != out->m_data)
	{
		travel = travel->m_next;
	}
	if (travel != nullptr)
	{
		found = true;
		if (travel != m_head && travel != m_tail)
		{
			travel->m_next->m_prev = travel->m_prev;
			travel->m_prev->m_next = travel->m_next;
		}
		else
		{
			m_head = nullptr;
			m_tail = nullptr;
		}
		delete travel;
	}

	return found;
}

/*////////////////////////////////////////////
	Purge calls delete until the list is empty
*/////////////////////////////////////////////
template <class T>
void LinkedList<T>::Purge()
{
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		travel = travel->m_next;
		travel != nullptr ? Delete(travel->m_prev) : Delete(m_head);
	}
}

/*/////////////////////////////////////////////////////////////////
	Display displays each piece of data one by one in the console
*//////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::Display() const
{
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		std::cout << travel->m_data << std::endl;
		travel = travel->m_next;
	}
}
#endif // !LINKED_LIST_H;